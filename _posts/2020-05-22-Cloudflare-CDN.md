---
layout:         page
title:          "使用Cloudflare的免费CDN"
date:           2020-05-22 20:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
---

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1hltvqxxj30ab03s3yd.jpg" width="400" align="bottom" />


Cloudflare是一家以向客户提供基于反向代理的内容分发网络（Content Delivery Network, CDN）及分布式域名解析服务（Distributed Domain Name Server）为主要业务的美国IT企业。

在 [Cloudflare](http://www.cloudflare.com/zh-cn/network/china/) 注册一个账号，通过简单几步设置，就可以免费使用CDN了。

#### 添加站点

到域名的 [控制面板](https://dash.cloudflare.com) 页面的右上角，点击**添加站点**，输入域名。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1h76s8frj30iw0epq2y.jpg" alt="截图使用163.com域名" width="{{ page.width}}" align="bottom" />
<center>截图使用163.com域名</center>


#### 选择免费计划

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1h9ffjzij30on0htq3f.jpg" alt="免费计划" width="{{ page.width}}" align="bottom" />
<center>免费计划</center>


#### 同步DNS记录

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1ha7f0wvj30q30bcq2t.jpg" alt="自动扫描域名的DNS记录" width="{{ page.width}}" align="bottom" />
<center>自动扫描域名的DNS记录</center>

<br>
<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1haqbyqkj30p20pfwfj.jpg" alt="显示同步过来的DNS记录" width="{{ page.width}}" align="bottom" />
<center>显示同步过来的DNS记录</center>


<br>
此处同步过来的DNS记录为已经在域名提供商后台的设置信息，如果没有的话，可以在这里添加DNS记录。添加完成点击下一步。

#### 更改名称服务器

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1hbbvdc1j30jh0phdgp.jpg" alt="Cloudflare名称服务器" width="{{ page.width}}" align="bottom" />
<center>Cloudflare名称服务器</center>
<br>
到域名提供商的后台（比如阿里云）更改名称服务器，更改名称服务器需要一定时间才能完成，通过dig命令查看更改结果。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1hbukiiij30yx0d2aa6.jpg" alt="更改名称服务器" width="{{ page.width}}" align="bottom" />
<center>更改名称服务器</center>


#### 使用dig命令检验
```
dig ns domain
```
<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1hd9y7q2j30hg08y0sm.jpg" alt="dig命令结果" width="{{ page.width}}" align="bottom" />
<center>dig命令结果</center>

ANSWER SECTION 结果显示，域名有两条名称服务器记录，分别对应上面的名称服务器1 和 名称服务器2，说明名称服务器已经更改生效。

#### 从Cloudflare删除站点

最后如果不想使用Cloudflare了，到域名的 [控制面板](https://dash.cloudflare.com) 页面，右下角的 **高级操作** ，选择 **从Cloudflare中删除站点**。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gf1hca40dej30gj05r743.jpg" alt="删除站点" width="{{ page.width}}" align="bottom" />
<center>删除站点</center>
