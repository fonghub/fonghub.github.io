---
layout:         page
title:          "RabbitMQ入门"
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
tags:
    - blog
---

### RabbitMQ简介
AMQP，即Advanced Message Queuing Protocol，高级消息队列协议，是应用层协议的一个开放标准，为面向消息的中间件设计。消息中间件主要用于组件之间的解耦，消息的发送者无需知道消息使用者的存在，反之亦然。
AMQP的主要特征是面向消息、队列、路由（包括点对点和发布/订阅）,可靠、安全。

RabbitMQ是一个开源的AMQP实现，服务器端用Erlang语言编写，支持多种客户端，如：Python、Ruby、.NET、Java、JMS、C、PHP、ActionScript等。用于在分布式系统中存储转发消息，在易用性、扩展性、高可用性等方面表现不俗。

### 安装RabbitMQ
rabbitmq 的安装参考 [windows10环境下的RabbitMQ安装步骤（图文）](https://blog.csdn.net/weixin_39735923/article/details/79288578)

### 手动收发消息
RabbitMQ安装好后，接着测试收发消息。
#### Add a user
<img src="http://tvax3.sinaimg.cn/large/7d4c6366gy1ggh4kwv049j20yt09y74f.jpg" alt="User" width="{{ page.width}}" align="bottom" />

#### Add a new virtual host
<img src="http://tvax3.sinaimg.cn/large/7d4c6366gy1ggh4nhxbevj20yt09jt90.jpg" alt="vhost" width="{{ page.width}}" align="bottom" />

#### Add a new exchange
<img src="http://tvax3.sinaimg.cn/large/7d4c6366gy1ggh4nw55uvj20yd08jglm.jpg" alt="exchange" width="{{ page.width}}" align="bottom" />


#### Add a new queue
<img src="http://tva3.sinaimg.cn/large/7d4c6366gy1ggh4od56x6j20yt08fq32.jpg" alt="queue" width="{{ page.width}}" align="bottom" />

#### Bindings
<img src="http://tva1.sinaimg.cn/large/7d4c6366gy1ggh4ou20p0j20yt0c80sx.jpg" alt="binding" width="{{ page.width}}" align="bottom" />

#### Publish message
<img src="http://tvax4.sinaimg.cn/large/7d4c6366gy1gghaxc3ovuj20yt0e3jrl.jpg" alt="sen" width="{{ page.width}}" align="bottom" />

#### Get messages
<img src="http://tvax2.sinaimg.cn/large/7d4c6366gy1gghaxp650uj20y80ckq34.jpg" alt="rec" width="{{ page.width}}" align="bottom" />


>使用队列里的发送消息功能，消息会被以队列名为routing key发送到默认的交换机，默认交换机隐形的绑定到每一个队列，使用队列名作为routing key，所以消息实际上又从交换机转发到队列

### 系统架构

<img src="http://tva3.sinaimg.cn/large/7d4c6366gy1ggh4yfepdyj210c0nsn4b.jpg" alt="架构" width="{{ page.width}}" align="bottom" />

RabbitMQ常用的Exchange Type有fanout、direct、topic、headers四种。
Direct：    Exchange将消息转发给完全匹配ROUTING_KEY的Queue
fanout：    忽略ROUTING_KEY，Exchange把消息转发给所有绑定的Queue
topic：     以ROUTING_KEY为模式，Exchange将消息转发给与模式匹配的Queue
headers：   消息体的header匹配