---
layout:         page
title:          "线性查找和折半查找"
date:           2020-07-19 12:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
keywords:       "数据结构 查找 "
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

### 顺序表查找

**查找思路**

例如 $[1,3,5,7,9,4,6,8,2]$ 为查找表的关键字数组，目标是找到关键字 $k=9$ 的记录。

从表的一端开始，顺序扫描线性表，依次将扫描到的关键字和给定值 $k$ 相比较，若当前扫描到的关键字与 $k$ 相等，则查找成功；若扫描结束后，仍未找到关键字等于 $k$ 的记录，则查找失败。


**性能评价**

[平均查找长度](/2020/07/17/search-introduction#平均查找长度aslaverage-search-length) 公式：
$ASL = \displaystyle \sum^{n}_{i=1}{p_i * c_i}$

$p_i = \frac{1}{n}$ 

$c_i$ 为关键字在数组中的位置序号， $c_i$ 的累加和为: $1+2+3+...+n = \frac{n*(n+1)}{2}$

所以：$ASL = \displaystyle \sum^{n}_{i=1}{p_i * c_i}=\frac{n+1}{2}$

所以顺序查找的时间复杂度为： $O(n)$ 。


**代码**

```C
#include <stdio.h>
#define MAXL 100
typedef int KeyType;
typedef char InfoType[10];
typedef struct
{
    KeyType key;
    InfoType data; 
} NodeType;
typedef NodeType SeqList[MAXL];

int SeqSearch(SeqList R,int n,KeyType k);
int main()
{
    int i,n=10;
    int result;
    SeqList R;
    KeyType a[] = {2,3,1,8,5,4,9,0,7,6},x=9;
    for ( i = 0; i < n; i++)
        R[i].key = a[i];

    result = SeqSearch(R,10,x);

    if (result > 0)
        printf("序列中第%d个是%d\n",result,x);
    else
        printf("未找到！\n");

    return 0;
}
//顺序查找
//逐个匹配，找到返回逻辑下标，未找到返回0
int SeqSearch(SeqList R,int n,KeyType k)
{
    int i;
    while (i < n && R[i].key != k)
        i++;

    if (i >= n)
        return 0;
    else
        return i+1;
}
```

### 折半查找


**前提条件**

线性表中的节点，按关键字值的递增或递减顺序排列。例如： $[2,3,10,15,20,25,28,29,30,35,40]$ 。


**查找思路**

首先用要查找的关键字 $k$（例如 $k=20$ ）与中间位置的节点的关键字比较，若比较结果相等则查找完成；若不相等，再根据 $k$ 与该中间节点关键字的比较大小确定下一步查找哪个子表。递归进行下去，直到找到满足条件的节点或者该线性表中没有这样的节点。


**性能评价**


<img src="http://tvax2.sinaimg.cn/large/7d4c6366gy1ggyeoffzxtj20nb0cbmxt.jpg" width="{{ page.width}}" align="bottom" />
<center>图1</center>

将折半查找过程用二叉树来描述(如图1)，把当前查找区间的中间位置上的记录作为根；左子表和右子表中的记录分别作为根的左、右子树。

成功的折半查找过程，恰好是走了一条从根到被查记录的路径，比较次数恰为该记录在树中的层数 $h$ 。

$ASL_{succ} = \displaystyle \sum^{n}_{i=1}{p_i * c_i}=\frac{1+2 * 2+3 * 4+4 * 4}{11}=3$ 

若查找失败，则其比较过程是一条从根到某个外部节点的路径，所需的比较次数是该路径上内部节点的总数 $h-1$ 。

$ASL_{unsucc} = \displaystyle \sum^{n}_{i=1}{p_i * c_i}=\frac {3 * 4+4 * 8}{11}=3.67$


<img src="http://tva3.sinaimg.cn/large/7d4c6366gy1ggyloldyloj20kz09nmxk.jpg" width="{{ page.width}}" align="bottom" />
<center>图2</center>

假设折半查找的二叉树是满二叉树(如图2)，根据满二叉树的性质有：
- 节点总数 $n=2^h-1$
- 树的高度 $h=log_2(n+1)$
- 第 $i$ 层上的记录个数 $2^{i-1}$

$ASL_{bn} = \displaystyle \sum^{n}_{i=1}{p_i * c_i}$

因为第 $i$ 层上的 **某个节点** 的平均查找长度为 $\frac {1}{n} * i$ 

所以第 $i$ 层上的 **所有节点** 的平均查找长度为 $\frac {1}{n} * i * 2^{i-1}$

所以满二叉树的平均查找长度为每一层平均查找长度的累加为 $\frac{1}{n} \displaystyle  \sum^{h}_{i=1}{2^{i-1}*i}$

因为 $\displaystyle  \sum^{h}_{i=1}{2^{i-1} * i} =1+(h-1) * 2^h$

所以 $ASL_{bn}=\frac{1}{n} * [1+(h-1) * 2^h]$

$=\frac{1}{n} * [1+(log_2(n+1)-1) * (n+1)]$

约等于 $log_2(n+1)-1$

所以满二叉树的折半查找的时间复杂度为 $O(log_2n)$


**代码**

```C
#include <stdio.h>
#define MAXL 100
typedef int KeyType;
typedef char InfoType[10];
typedef struct
{
    KeyType key;
    InfoType data; 
} NodeType;
typedef NodeType SeqList[MAXL];

int BinSearch_r(SeqList R,int low,int high,KeyType k);
int main()
{
    int i,n=11;
    int result;
    SeqList R;
    KeyType a[] = {2,3,10,15,20,25,28,29,30,35,40},x=20;
    for ( i = 0; i < n; i++)
        R[i].key = a[i];

    result = BinSearch_r(R,0,n-1,x);

    if (result > 0)
        printf("序列中第%d个是%d\n",result,x);
    else
        printf("未找到！\n");

    return 0;
}
//折半查找，递归方式
//前提条件是待查找的序列是有序的
int BinSearch_r(SeqList R,int low,int high,KeyType k)
{
    int mid;
    if (low <= high)
    {
        mid = (low+high)/2;
        if (R[mid].key == k)
            return mid+1;

        if(R[mid].key > k)
            return BinSearch_r(R,low,mid-1,k);
        else
            return BinSearch_r(R,mid+1,high,k);
    }else return 0;
    
}
```
