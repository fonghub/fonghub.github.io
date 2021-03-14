---
layout:         page
title:          "MySQL常用日期和时间函数"
date:           2021-03-14 20:00:00 +0400
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "MySQL 日期 时间 "
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


#### 日期/时间表示
1. 返回当前日期时间
```mysql
>   SELECT NOW();   ## 同CURRENT_TIMESTAMP(),返回一个 datetime 表达式
<.  2021-03-14 15:37:16
```
2. 返回当前日期
```mysql
>   SELECT DATE(NOW());  ## 同CURRENT_DATE() 和 CURDATE()
<.  2021-03-14
```
3. 返回当前时间
```mysql
>   SELECT TIME(NOW());  ## 同CURRENT_TIME() 和 CURTIME()
<.  15:41:19
```
4. 单独返回年/月/日/时/分/秒

```mysql
>   SELECT YEAR(NOW());
<.  2021

>   SELECT MONTH(NOW());
<.  3

>   SELECT DAY(NOW());
<.  14

>   SELECT HOUR(NOW());
<.  15

>   SELECT MINUTE(NOW());
<.  49

>   SELECT SECOND(NOW());
<.  43
```

5. 另一种方式单独返回年/月/日/时/分/秒

使用 ```EXTRACT(unit FROM date)``` 函数，```unit``` 为要返回值类型，```date``` 为日期时间表达式。

```mysql
>   SELECT EXTRACT(YEAR FROM NOW());
<.  2021
```
> unit包括：YEAR,MONTH,DAY,HOUR,MINUTE,SECOND,MICROSECOND等等。

使用 ```DATE_FORMAT(date,format)``` 函数，```date``` 为日期时间表达式，```format``` 为要返回的日期格式。
```mysql
>   SELECT DATE_FORMAT(NOW(),"%Y");
<.  2021
```
常用的日期时间格式有：

|格式|描述|
|---|---|
|%Y|4位数字年份|
|%m|2位数字月份 (00 to 12)|
|%d|2位数字日期 (01 to 31)|
|%H|小时 (00 to 23)|
|%i|分钟 (00 to 59)|
|%s|秒钟 (00 to 59)|
|%f|毫秒 (000000 to 999999)|

更多的日期时间格式查看 [Date and Time Functions](https://dev.mysql.com/doc/refman/8.0/en/date-and-time-functions.html#function_date-format) 文档。

#### 日期/时间计算

1. 加 x 年/月/日/时/分/秒
```mysql
>   SELECT NOW();
<.  2021-03-14 18:21:18
>   SELECT DATE_ADD(NOW(),INTERVAL 1 HOUR);
<.  2021-03-14 19:21:18
```
2. 减 x 年/月/日/时/分/秒
```mysql
>   SELECT NOW();
<.  2021-03-14 18:23:07
>   SELECT DATE_SUB(NOW(),INTERVAL 1 DAY);
<.  2021-03-13 18:23:07
```

3. 计算两个日期时间之差

使用 ```DATEDIFF(date1,date2)``` 函数计算两个日期相差几天。
```mysql
>   SELECT DATEDIFF(DATE_ADD(NOW(),  INTERVAL 1 DAY),CURDATE());
<.  1
```
使用 ```TIMEDIFF(time1,time2)``` 函数计算两个时间相差多少小时多少分钟多少秒钟。
```mysql
>   SELECT TIMEDIFF(DATE_ADD(CURTIME(),INTERVAL 1 HOUR),CURTIME());
<.  01:00:00
```

#### 日期时间与unix时间戳互相转换

1. 日期时间 转 时间戳
函数 ```UNIX_TIMESTAMP(datetime)``` 带一个日期时间表达式参数，当不带参数时，相当于 ```datetime=now()```。
```mysql
>   SELECT UNIX_TIMESTAMP();
<.  1615721103
>   SELECT UNIX_TIMESTAMP(DATE_ADD(NOW(),INTERVAL 1 DAY));      # 返回明天的时间戳
<.  1615807716
```

2. 时间戳 转 日期时间
函数 ```FROM_UNIXTIME(unix_timestamp,format)``` 有两个参数， ```unix_timestamp``` 参数必须，表示时间戳，```format``` 参数可选，表示日期时间格式，当 ```format``` 为空时，表示返回 ```"%Y-%m-%d %H:%i:%s"``` 格式的日期时间。
```mysql
>   SELECT FROM_UNIXTIME(1615807716);
<.  2021-03-15 19:28:36
>   SELECT FROM_UNIXTIME(1615807716,"%Y-%m-%d");
<.  2021-03-15
```