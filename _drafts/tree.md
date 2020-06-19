---
layout:         page
title:          "树和树结构"
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
tags:
    - blog
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




### 定义和属性
定义：具有相同特性的n个数据节点组成的一个有穷序列，节点之间存在一对多的关系

属性：
	空树：节点数为0的树称为空树
	根节点：
	前驱节点：
	后继节点：




### 抽象数据类型
```
ADT Tree
{
	数据对象：
	数据关系：
	数据操作：
}
```

### 树的表示方法
	树形表示法
	文氏图表示法
	凹入表示法
	括号表示法


### 树的遍历
	先根遍历
	后根遍历
	层次遍历


### 树的性质


### 树的存储结构