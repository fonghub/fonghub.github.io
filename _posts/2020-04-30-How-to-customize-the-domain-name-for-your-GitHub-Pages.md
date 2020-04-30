---
layout:         page
title:          "如何为你的GitHub Pages自定义域名"
date:           2020-04-30 21:17:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
---



##### 一、前提条件

1.已经搭建了GitHub Pages站点

2.已经购买了域名(国内的话要实名认证)

##### 二、域名解析

到域名提供商的后台，为域名添加解析，此处以阿里云为例。

添加两条CNAME记录，主机记录分别是「www」和「@」，如下图：

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gec4zzksilj30tw0bwwf5.jpg" alt="域名解析" width="{{ page.width}}" align="bottom" />
<center>域名解析</center>



>主机记录「www」和「@」的区别是解析的域名的形式，以域名chenzaofeng.xyz为例：
>
>主机记录「www」对应 www.chenzaofeng.xyz域名
>
>主机记录「@」对应 chenzaofeng.xyz域名
>
>一般「www」和「@」都是一起出现



##### 三、到GitHub仓库配置域名

回到GitHub Pages的仓库，到Settings选项卡下面，找到GitHub Pages块（如下图），在Custom domain下面的输入框里填入域名，保存就完成了。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gec53jgdwtj30mt0ib3zd.jpg" alt="配置域名" width="{{ page.width}}" align="bottom" />
<center>配置域名</center>



此时到Code选项卡下面，会发现多了个CNAME文件,这个文件的内容就是刚刚填写的域名。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gec53xw159j30t108rdg6.jpg
" alt="CNAME文件" width="{{ page.width}}" align="bottom" />
<center>CNAME文件</center>

等待10分钟后就可以使用自定义的域名访问GitHub Pages站点了。

##### 四、补充
在第二步解析域名的时候，一开始我添加的是两条A记录，等到第三步配置好之后，就收到了GitHub的提示邮件，建议我使用CNAME记录，于是才修改了回来，感兴趣的可以尝试一下。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gec5473ky1j30lo07maar.jpg" alt="推荐使用CNAME记录" width="{{ page.width}}" align="bottom" />
<center>推荐使用CNAME记录</center>

关于CNAME记录和A记录，不用在意名字什么意思，只要知道A记录指向的是一个IPV4地址，CNAME记录指向的是另一个域名就好了。