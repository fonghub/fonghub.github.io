---
layout:         page
title:          "查找简介"
date:           2020-07-17 21:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
keywords:       "数据结构 查找 平均查找长度"
tags:
    - blog
categories:     ['ds']
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

### 查找的定义
给定一个值 $k$ ，在含有 $n$ 个记录的表中找出关键字等于 $k$ 的记录。若找到，则查找成功，返回该记录的信息或该记录在表中的位置；否则查找失败，返回相关的指示信息 。


### 查找的对象
一组记录组成的表或文件，每个记录则由若干个数据项组成，其中必须含有一个能唯一标识该记录的数据项——叫做关键字。


### 查找的方法
基于不同的数据结构和存储结构，有不同的查找方法。有：顺序表、链表、树表、哈希表等。

### 查找的两种基本形式

静态查找(Static Search)：在查找的时候只对数据元素进行查询或检索，查找表称为静态查找表。

动态查找(Dynamic Search)：在实施查找的同时，插入查找表中不存在的记录，或从查找表中删除已存在的某个记录，查找表称为动态查找表。

### 平均查找长度ASL（Average Search Length）

查找的主要运算是关键字的比较，常把查找过程中对关键字需要执行的平均比较次数，作为衡量一个查找算法效率优劣的标准，平均比较次数，也称为平均查找长度。

$ASL = \displaystyle \sum^{n}_{i=1}{p_i * c_i}$

分别有：查找成功是的 $ASL_{succ}$ 和查找不成功时的 $ASL_{unsucc}$ 。

- $n$ 是查找表中记录的个数
- $p_i$ 表示查找第 $i$ 个记录的概率，一般认为每个记录的查找概率相等，即是 $p_i= \frac{1}{n}$ 
- $c_i$ 是找到第 $i$ 个记录所需进行的比较次数。