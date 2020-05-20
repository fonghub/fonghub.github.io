---
layout:         page
title:          "使用SMTP协议和POP3协议手动收发邮件"
date:           2020-05-20 21:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
tags:
    - blog
---

通过上一篇博文[理解电子邮件的收发过程](http://www.chenzaofeng.xyz/2020/05/11/How-to-send-and-receive-email.html)我们知道，SMTP服务器是遵循SMTP协议的发送邮件服务器，用来发送邮件的。POP3服务器是遵循POP3协议的服务器，用来接收电子邮件的。接下来就开始体验，通过终端窗口，使用SMTP协议和POP3协议来收发邮件。

#### 使用SMTP[<sup>1</sup>](#reference)协议发送邮件
邮件客户端与SMPT服务器通过指令连接，并且使用一问一答的方式来发送消息。

##### 连接
使用telnet命令与163邮箱的SMTP服务器建立连接，25表示端口号 
``` 
telnet smtp.163.com 25  
```

##### 认证
1.告诉SMTP服务器发送者的域名 
```
ehlo 163.com
```

2.选择登录认证方式，一般选择的是login
```
auth login
```

3.接着输入经过base64加密的账号
```
emFvZ*******oZW4
```

4.输入经过base64加密的密码 
```
UVRXSU**************5RQw
```


>一般的，邮箱服务商默认是不允许用户在邮件客户端软件登陆的，但如果需要，需要去后台开启，并且获得授权码，使用邮箱地址+授权码在邮件客户端登陆。

认证成功会返回 

```235 Authentication successful```


##### 输入发件人与收件人

分别输入发件人与收件人 

```
mail from:<za*****en@163.com>

rcpt to:<fe*****ng@163.com>
```

输入正确会返回 

```250 Mail OK```

##### 输入邮件数据

输入 ```data``` 命令，然后编写要发送的邮件内容。

```from``` 表示发件人，```to``` 表示收件人（可多个），```cc``` 表示抄送，```bcc``` 表示暗抄送，```subject```表示邮件标题。

接着 ```空一行```，然后输入邮件内容，最后以点 ```.``` 结束数据输入。

```
data

from:<za*****en@163.com>
to:<fe*****ng@163.com>
cc:<erdo*****ong@163.com>
bcc:<51****521@qq.com>
subject:This is a test email. Ignore it

This is the HTML message body <b>in bold bold bold!</b>

.
```

##### 断开连接

使用 ```quit``` 命令断开连接。



#### 使用POP3[<sup>2</sup>](#reference)协议接收邮件

##### 连接
使用telnet命令与163邮箱的pop3服务器建立连接，110表示端口号
```
telnet pop3.163.com 110
```

##### 认证状态
与POP3服务器成功建立连接后，POP3服务器会话此时处于认证状态，客户端需要提供账号和密码来为自己认证。


```
user za*****en

pass QTWIF*****STQC
```
> POP3认证的时候，账号密码使用原文。

##### 事务状态
客户端认证成功后，POP3服务器进入事务状态，具体操作是：POP3服务器锁住并且打开邮箱。

处于事务状态可以执行以下命令来操作邮件：

```
STAT Command ............ 查询邮箱中的统计信息
LIST Command ............ 列出邮箱中的邮件信息
RETR Command ............ 获取某封邮件的内容
DELE Command ............ 给某封邮件设置删除标记
NOOP Command ............ 检查客户端与POP3服务器的连接情况
RSET Command ............ 清除所有邮件的删除标记
```


使用 ```list``` 命令查看邮件列表，返回邮件列表序号和邮件的存储大小，单位字节。


```
list
+OK 35 11563487
1 6488
2 16067
3 88116
4 34166
5 39133
6 43443
7 3747
8 42304
9 2366
10 2100
11 85673
12 3337
13 12782
14 90477
15 10484
16 21241
17 81829
18 1591
19 3132
20 2033
21 1626
22 1601
23 3120
24 85708
25 1626
26 2143
27 97037
28 16652
29 16708
30 85513
31 4788181
32 5839338
33 23664
34 8468
35 1593
.
```


使用 ```retr msg``` 命令获取邮件内容，参数msg为邮件序号


```
retr 35
+OK 1593 octets
Received: from qq.com (unknown [113.96.223.68])
        by mx40 (Coremail) with SMTP id WsCowAAH4Dv04MRekurPAA--.17594S3;
        Wed, 20 May 2020 15:49:08 +0800 (CST)
DKIM-Signature: v=1; a=rsa-sha256; c=relaxed/relaxed; d=qq.com; s=s201512;
        t=1589960948; bh=Rg9Ilk6oCZAHksj409f6LHX6GuP72cTqrNUPvlZJqnM=;
        h=From:To:Subject:Mime-Version:Date:Message-ID;
        b=rtqnxFIs3rmz4zLMErF3Q1rjULVsgBujmpY/wzoFYYa8OKTbr4yg4oN3qP8WC0NPW
         MIPQYWPXfZ99rbe9aEWLam7D4CB+qzTuS9LY/x2D7TizGrRcjsvrwJ0xKhkCXocx2G
         GBqd7+3iRQhZQiF0SLDvr81rqZkvfDuIIh73WzEs=
From: "=?gb18030?B?Y2hlbnphb2Zlbmc=?=" <51****521@qq.com>
To: za*****en@163.com
Subject: =?gbk?B?19S2r7vYuLQ6aGVsbG8gd29ybGQ=?=
Mime-Version: 1.0
Content-Type: text/html;
        charset="gbk"
Content-Transfer-Encoding: base64
Date: Wed, 20 May 2020 15:49:07 +0800
Message-ID: <tencent_2A0A7603148F38FD5B986F86@qq.com>
X-QQ-MIME: TCMime 1.0 by Tencent
X-Mailer: QQMail 2.x
X-QQ-Mailer: QQMail 2.x
X-QQ-HolidayReply: true
X-QQ-mid: bglocal204t1589960947t3211568
X-QQ-SENDSIZE: 520
Received: from qq.com (unknown [127.0.0.1])
        by smtp.qq.com (ESMTP) with SMTP
        id ; Wed, 20 May 2020 15:49:07 +0800 (CST)
Feedback-ID: bglocal:qq.com:bgspam:bgspam8
X-CM-TRANSID:WsCowAAH4Dv04MRekurPAA--.17594S3
Authentication-Results: mx40; spf=pass smtp.mail=51****521+auto_=zaofe
        ngchen=163.com@qq.com; dkim=pass header.i=@qq.com
X-Coremail-Antispam: 1Uf129KBjDUn29KB7ZKAUJUUUUU529EdanIXcx71UUUUU7v73
        VFW2AGmfu7bjvjm3AaLaJ3UbIYCTnIWIevJa73UjIFyTuYvjxUg7UUDUUUU
Sender: 51****521+auto_=za*****en=163.com@qq.com

xPq1xNPKvP7O0tLRvq3K1bW9wcujrNC70LujoQ==
.
```


##### 更新状态 
当客户端从事务状态发出 ```quit``` 命令时，POP3会话从事务状态进入更新状态。
>如果会话因客户端以外的原因被终结，那么POP3不会进入更新状态，也不会操作（包括删除、移动等）邮箱里面的邮件


<div id="reference"></div>
#### 参考

[1] [smtp-rfc2821](https://tools.ietf.org/html/rfc2821#section-4.1)

[2] [pop3-rfc1939](https://tools.ietf.org/html/rfc1939)