---
layout:         page
title:          "MySQL的RANGE分区管理与预警"
date:           2020-12-23 22:30:00 +0400
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "MySQL 分区 预警 "
tags:
    - blog
categories:     ['mysql']
---

<!-- 渲染公式 -->
<script src="{{ site.url }}/static/js/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>
<script type="text/x-mathjax-config">
    MathJax.Hub.Config({
        tex2jax: {
        skipTags: ['script', 'noscript', 'style', 'textarea', 'pre'],
        inlineMath: [['$','$']]
        }
    });
</script>
<!-- 渲染公式 -->


MySQL有四种分区类型，分别是RANGE分区、LIST分区、HASH分区和KEY分区。其中数RANGE分区使用最为普遍。

RANGE分区基于一个给定的分区键和分区值，把一个大的数据表分成多个连续且不重复的分区表。物理层面上是把一个大文件分割成多个小的文件。

#### 数据表分区的两种方式

方式一，创建表的同时，设置表分区
```sql
CREATE TABLE tablename(col1,col2,col3,...)
PARTITION BY RANGE(col_key)
(
    PARTITION p1 VALUES LESS THAN (value1),
    PARTITION p2 VALUES LESS THAN (value2),
    PARTITION p3 VALUES LESS THAN (value3),
    PARTITION p_maxvalue VALUES LESS THAN (MAXVALUE)
);
```

方式二，对已创建的表分区
```sql
ALTER TABLE tablename PARTITION BY RANGE(col_key) 
(
    PARTITION p1 VALUES LESS THAN (value1),
    PARTITION p2 VALUES LESS THAN (value2),
    PARTITION p3 VALUES LESS THAN (value3),
    PARTITION p_maxvalue VALUES LESS THAN (MAXVALUE)
);
```

分区的时候，最好设置一个最大分区 ```p_maxvalue```
```sql
PARTITION p_maxvalue VALUES LESS THAN (MAXVALUE)
``` 
存放意料之外的数据。例如：

- 当出现错误数据，大于所有分区值时，会存放到 ```p_maxvalue``` 分区
- 当来不及增加分区时，数据会存放到 ```p_maxvalue``` 分区，且对前面的分区无影响

总之，设置 ```p_maxvalue``` 分区并不是为了存放数据，而是在出现意外的时候，程序不至于报错。

#### 显示已分区的数据表
```sql
SELECT
	TABLE_NAME tname,                   -- 数据表名
	TABLE_ROWS trow                     -- 数据行数
FROM
	information_schema.`TABLES`
WHERE
	TABLE_SCHEMA = {$dbName}
AND CREATE_OPTIONS LIKE '%partitioned%';
```

<img src="http://tva1.sinaimg.cn/large/7d4c6366gy1glxvwlv028j20zu09j0sw.jpg" width="{{ page.width}}" align="bottom" />
<center>显示分区的数据表</center>

#### 显示某个表的分区列表
```sql
SELECT
	PARTITION_ORDINAL_POSITION onum,    -- 分区序号
	PARTITION_NAME pname,               -- 分区名字
	PARTITION_METHOD pmethod,           -- 分区方式
	PARTITION_EXPRESSION pkey,          -- 分区键
	PARTITION_DESCRIPTION pvalue,       -- 分区值
	TABLE_ROWS trows                    -- 数据行数
FROM
	information_schema.`PARTITIONS`
WHERE
	TABLE_SCHEMA = {$dbName}
AND TABLE_NAME = {$tname};
```

<img src="http://tvax4.sinaimg.cn/large/7d4c6366gy1glxw1kt2cnj20q60l074y.jpg" width="{{ page.width}}" align="bottom" />
<center>分区列表</center>

#### 删除分区
当历史数据归档后，分区的数据行数为0，此时该分区已经无用，为了减少系统的文件数，可以把它删除掉。

<img src="http://tvax2.sinaimg.cn/large/7d4c6366gy1glxwhqxvfej20q00kvdgh.jpg" width="{{ page.width}}" align="bottom" />
<center>数据归档的分区</center>


```sql
ALTER TABLE {$dbName}.{$tname} DROP PARTITION {$pname};
```
>使用 DROP PARTITION 删除分区的同时，也会删除分区里的数据


#### 取消分区

```sql
ALTER TABLE {$dbName}.{$tname} REMOVE PARTITIONING;
```
>取消分区对表数据无影响

#### 增加分区
增加分区之前，需要删除最大分区 ```p_maxvalue```。
因为分区是连续递增的，所以需要把最大分区 ```p_maxvalue``` 删除，再增加新的分区。

```sql
ALTER TABLE {$dbName}.{$tname} ADD PARTITION 
(
    PARTITION {$pname} VALUES LESS THAN (value1)
);
```

#### 拆分分区
当来不及增加分区时，数据会存放到 ```p_maxvalue``` 分区。当发现 ```p_maxvalue``` 分区有数据时，应该尽快创建新分区，并把数据迁移到新分区上。

```sql
ALTER TABLE {$dbName}.{$tname} REORGANIZE PARTITION p_maxvalue INTO 
(
	PARTITION p_20210301 VALUES less than (1614528000),
	PARTITION p_maxvalue VALUES less than (MAXVALUE)
);
```
此时数据保存到了 ```p_20210301``` 分区，通过
```sql
EXPLAIN SELECT ....;
```
可以看到 ```partitions``` 字段的值为 ```p_20210301``` ,表示查询的内容在 ```p_20210301``` 分区。

此时若发现查询并未使用到索引，则需要优化一下分区。

执行语句：
```sql
ALTER TABLE {$dbName}.{$tname} REBUILD PARTITION p_maxvalue,p_20210301;         -- 重建分区
ALTER TABLE {$dbName}.{$tname} ANALYZE PARTITION p_maxvalue,p_20210301;         -- 分析分区
```
或
```sql
ALTER TABLE {$dbName}.{$tname} OPTIMIZE PARTITION p_maxvalue,p_20210301;;
```
再次执行查询语句
```sql
EXPLAIN SELECT ....;
```
发现已经使用了索引。

>REORGANIZE PARTITION 也可以用于重命名分区，重命名分区后也需要执行一下优化分区语句。


#### 分区预警
以下分区预警思路针对RANGE分区类型，基于时间的连续分区。

使用分区预警的好处有：
- 可以提前知晓备用的分区不足，不用逐个表检查
- 可以不用一下子准备多个备用分区，减少分区数量

分区预警的思路如下代码：
```php
    // 分区预警，预警值默认60天
    public static function warningPartition($warningDays=60)
    {
        // 获取所有的数据库
        $dbNames = self::get_all_db();
        $result = [];
        foreach($dbNames as $dbName)
        {
            // 获取指定数据库的分区表列表
            $sqlTable = "SELECT TABLE_NAME tname,TABLE_ROWS trow FROM information_schema.`TABLES` WHERE TABLE_SCHEMA='{$dbName}' AND CREATE_OPTIONS LIKE '%partitioned%'";
            $listTable = self::querySql($sqlTable);
            foreach($listTable as $table)
            {
                // 获取指定数据库，指定表的除p_maxvalue外的最大分区的值
                $sqlPartition = "SELECT PARTITION_NAME pname,PARTITION_DESCRIPTION pvalue FROM information_schema.`PARTITIONS` WHERE TABLE_SCHEMA='{$dbName}' AND TABLE_NAME='{$table}' AND PARTITION_NAME != 'p_maxvalue' ORDER BY PARTITION_DESCRIPTION DESC LIMIT 1";
                $listPartition = self::querySql($sqlPartition);
                $pvalue = $listPartition[0]['pvalue'];

                // 最大分区的值小于阈值，则保存预警信息
                if($pvalue - time() < $warningDays * 86400)
                    $result[] = "数据表：{$dbName}.{$table}，最新分区：{$listPartition[0]['pname']} - {$listPartition[0]['pvalue']}，预警阈值：{$warningDays}天";  
            }
        }
        return $result;
    }
```
分区预警程序 + [Telegram机器人](/2021/04/07/telegram)可以实时的收到预警信息。
