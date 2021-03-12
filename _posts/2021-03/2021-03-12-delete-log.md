---
layout:         page
title:          "使用PHP和SHELL脚本删除日志"
date:           2021-03-12 23:00:00 +0400
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "PHP SHELL 日志 "
tags:
    - blog
categories:     ['php']
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


#### 思路
一般来说，日志文件都是按照日期来命名的，例如这样: ```21_03_01.log```。

每一个日志文件只记录当天某个功能的日志信息，这种做法方便于定为错误。

通过日志文件的属性——最后修改时间，可以得知日志文件记录的是哪一天的日志，距离现在过去多少天了。

当每天的日志量不多，可以考虑保存最近30天的日志量，保存再多也没有意义。

当每日的日志量很多的话，出于存储空间的考虑，可以考虑保存最近7天的日志量。

#### 使用PHP删除日志文件
需要删除日志文件的时候，通过web端手动调用接口 或者 通过 CLI 的方式，自动定时的调用接口，删除日志文件。

```php
//删除日志文件
public function delLogs($day=30)
{
    if($day < 8)
    {
        echo "保留不少于一个星期的日志文件";
        die;
    } 
    $logDir = realpath(LOG_PATH);   
    $this->delLogs2($logDir,$day);
}

public function delLogs2($logDir,$day)
{
    $dh = opendir($logDir);
    if($dh){
        while($file = readdir($dh))
        {
            if($file == '.' || $file == '..')
                continue;

            $filePath = $logDir.'/'.$file;
            if(is_file($filePath))
            {
                if(filemtime($filePath) < strtotime("-{$day} days"))
                {
                    echo "file={$filePath}";
                    unlink($filePath);
                }
            }
            else
                $this->delLogs2($filePath,$day);
        }
        closedir($dh);
    }else{
        echo "目录错误：{$logDir}";
    }
}
```

#### 使用SHELL脚本删除日志文件

使用 ```find``` 命令，查找日志目录下的名字格式为 ```"*.log"``` ，最后修改时间为20天以前的文件，把找到的文件删除掉。

把命令写入 ```delLogs.sh``` 文件，通过终端命令```sh delLogs.sh```执行。

```bash
#!/bin/bash
echo start delete log 20 days ago...
find /app/Logs/ -mtime +20 -name "*.log" -exec  rm -rf {} \;
echo end delete log...
```
