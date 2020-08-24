---
layout:         page
title:          "Windows下PHP如何添加扩展"
date:           2020-08-23 11:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
categories:     ['php']
permalink:      /:year/:month/:day/:title
keywords:       "Windows PHP 扩展 "
---

Windows下，PHP添加扩展，步骤如下：
1. 找到目标扩展
2. 把扩展文件放到PHP扩展文件夹里
3. 添加扩展配置
4. 重启

下面以添加redis扩展为例。

### 确定PHP版本信息
访问 **phpinfo.php**，找到这三个字段的值：
- PHP Version
- Architecture
- Thread Safety

<img src="http://tva4.sinaimg.cn/large/7d4c6366gy1gi1x35ukyvj20q60mo0u1.jpg" width="{{ page.width}}" align="bottom" />
<center>phpinfo</center>

从上图可知，需要找支持PHP版本7.0、x86架构、线程安全的redis扩展。

### 查找扩展
到[PECL](http://pecl.php.net/)查找redis扩展，输入扩展名字，查找。

<img src="http://tva3.sinaimg.cn/large/7d4c6366gy1gi1x3ifk4dj20qq0h8t9w.jpg" width="{{ page.width}}" align="bottom" />
<center>PECL官网</center>

从查找结果列表中找到redis扩展。

<img src="http://tva4.sinaimg.cn/large/7d4c6366gy1gi1x3nmocfj20qq0gddgk.jpg" width="{{ page.width}}" align="bottom" />
<center>查找结果列表</center>

点击进入，看到有不同版本的redis扩展。
>注意要找稳定版(statble)的DLL。

<img src="http://tvax1.sinaimg.cn/large/7d4c6366gy1gi1z0970g7j20lf0o6juk.jpg" width="{{ page.width}}" align="bottom" />
<center>不同版本的redis扩展</center>


根据第一步确定的信息，可以找到目标扩展，点击下载。

<img src="http://tvax1.sinaimg.cn/large/7d4c6366gy1gi1x3rvy3qj20qq0prmz3.jpg" width="{{ page.width}}" align="bottom" />
<center>目标扩展</center>

### 安装扩展

解压缩扩展文件，把DLL扩展文件放到PHP扩展文件夹里面。

>如果不知道PHP扩展文件夹的位置，从php.ini里搜索extension_dir="..."可以找到。

在php.ini文件里添加
>extension=php_redis.dll

即可。


### 测试
重启服务器，访问 **phpinfo.php** ，如果看到有目标扩展信息，即表示安装成功。
<img src="http://tva2.sinaimg.cn/large/7d4c6366gy1gi1x40ful0j20q903ut8k.jpg" width="{{ page.width}}" align="bottom" />
<center>测试redis扩展</center>
