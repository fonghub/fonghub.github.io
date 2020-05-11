---
layout:         page
title:          "理解电子邮件的收发过程"
date:           2020-05-11 21:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
---



##### 一、电子邮件的收发过程
模拟用户A在邮件客户端上使用QQ邮箱，发送邮件给用户B的163邮箱的过程[<sup>1</sup>](#reference)。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1geot5tg58zj30vm0gi0u6.jpg" alt="邮件的收发过程" width="{{ page.width}}" align="bottom" />
<center>邮件的收发过程</center>


1. 用户A在邮件客户端上写好邮件，发出去后，邮件先到达QQ邮箱的SMTP服务器；

2. QQ邮箱的SMTP服务器根据收件地址判断，收件地址与发件地址是否属于同一个邮箱服务商：

    1. 同属于一个邮箱服务商，QQ邮箱的SMTP服务器会把邮件保存到QQ邮箱的内部存储空间

    2. 属于不同邮箱服务商，QQ邮箱的SMTP服务器把邮件转发给163邮箱的SMTP服务器

3. 163邮箱的SMTP服务器收到邮件后，也会像第2步骤一样判断是否同属于一个邮箱服务商，最后保存到163邮箱的内部存储空间；

4. 现在的邮件客户端都有定时自动收取邮件的功能，用户也可以手动收取邮件。邮件客户端向163邮箱的POP3服务器发起收取邮件的请求后，POP3服务器从163邮箱的内部存储空间接收邮件，然后返回给邮件客户端。

##### 二、3种邮件协议
电子邮件的收发过程中，第1步发送邮件和第2.2步转发邮件使用的是SMTP协议；第4步收取邮件使用的是POP3协议。

**SMTP**[<sup>2</sup>](#reference)是Simple Mail Transfer Protocol的简称，即简单邮件传输协议。它定义了邮件客户端软件和SMTP邮件服务器之间，以及两台SMTP邮件服务器之间的通信规则。SMTP协议属于TCP/IP 协议簇，它帮助每台计算机在发送或中转信件时找到下一个目的地。SMTP服务器是遵循SMTP协议的发送邮件服务器，用来发送邮件的。

**POP3**是Post Office Protocol 3的简称，即邮局协议的第3个版本，它定义了邮件客户端软件和POP3邮件服务器的通信规则。POP3服务器是遵循POP3协议的服务器，用来接收电子邮件的。


**IMAP**全称是Internet Mail Access Protocol，即互联网邮件访问协议，它是跟POP3类似的邮件访问标准协议之一，可以看作是POP协议的扩展。

>IMAP和POP3的区别
>
>POP3允许邮件客户端下载服务器上的邮件，但是在邮件客户端的操作（如：移动邮件、标记已读等），是不会反馈到服务器上的。
>但是IMAP就不同了，邮件客户端的操作都会反馈到服务器上，对邮件进行的操作（如：移动邮件、标记已读等），服务器上的邮件也会做相应的动作。也就是说，IMAP是“双向”的。
>同时，IMAP可以只下载邮件的主题，只有当真正需要的时候，才会下载邮件的所有内容。


<div id="reference"></div>

##### 参考
[1] [邮件实现详解（一）------邮件发送的基本过程与概念](https://www.cnblogs.com/ysocean/p/7652934.html)

[2] [rfc821](http://www.cnpaf.net/rfc/rfc821.txt)