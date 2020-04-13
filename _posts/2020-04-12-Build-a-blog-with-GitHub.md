---
layout:         page
title:          "如何利用GitHub快速搭建一个博客"
date:           2020-04-12 20:19:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
---

##### 一、前提条件

1.拥有一个GitHub账号

2.安装了ruby环境（版本在2.4以上）

##### 二、准备工作——安装Jekyll

1.执行命令 ```ruby -v```，查看ruby版本，是否为```2.4.0```或更高版本

2.执行 ```gem -v```,查看RubyGems检查版本

3.执行命令，安装```jekyll```和```bundler``` 

```
gem install jekyll bundler
``` 

>安装Jekyll过程如果遇到网络问题，可以多试几次。
>
>以下是[官方文档](https://www.jekyll.com.cn/docs/installation/)，根据你的操作系统选择阅读
>


<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gdr7czwkvlj30ye0u0tgq.jpg" alt="官方文档" width="{{ page.width}}" align="bottom" />
<center>官方文档</center>

##### 三、开始搭建

1.进入我的[仓库](https://github.com/zaofengchen/zaofengchen.github.io)

2.点击右上角的 Fork 将我的仓库拉倒你的账号下

3.克隆仓库到本地

```
git clone git@github.com:your_github_name/zaofengchen.github.io.git
```

4.进入博客目录

```
cd zaofengchen.github.io.git
```

5.开启服务
```
jekyll serve
```

6.访问

访问 [http://127.0.0.1:4000](http://127.0.0.1:4000) 



<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gdr3c0b6wdj31sj0u0go2.jpg" alt="首页" width="{{ page.width}}" align="bottom" />
<center>首页显示</center>
<br>
<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gdr3bzfixaj31sg0u07be.jpg" alt="首页" width="{{ page.width}}" align="bottom" />
<center>内容页显示</center>

7.测试发博文

在```_posts```目录下新建一个markdown文件，文件名以.md为后缀

例如：```2020-04-13-如何最快的搭建一个博客.md```
文件名必须使用规定的格式

编写文件，例如

```
---
layout: page
title:  "这是一篇测试博客!"
date:   2020-04-13 04:05:33 +0800
---

**登鹳雀楼** 

_唐代：王之涣_

白日依山尽，黄河入海流。

欲穷千里目，更上一层楼。
```
此时再次访问[首页](http://127.0.0.1:4000) 会出现新的博文



<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gdr64vog7zj31py0u0dj0.jpg" alt="首页" width="{{ page.width}}" align="bottom" />
<center>首页显示</center>
<br>

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1gdr650degmj31py0u0jur.jpg" alt="新的博文" width="{{ page.width}}" align="bottom" />
<center>新的博文显示</center>

8.发布到GitHub

- 为你的博客新建一个仓库，仓库名为：```your_github_name.github.io```
- 回到终端，按住 ```ctrl-c```，停止服务
- 修改博客目录名字为```your_github_name.github.io```，进入博客目录
- 执行命令
```
git init
git add .
git commit -m "init"
git remote add origin git@github.com:zaofengchen/your_github_name.github.io
git push -u origin master
```

访问 http://your_github_name.github.io 即可看到博客

至此，一个博客就搭建完成了。


