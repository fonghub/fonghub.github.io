---
layout:         page
title:          "选择排序——直接选择排序、堆排序"
date:           2020-07-30 13:30:00 +0800
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "数据结构 排序算法 直接选择排序 堆排序 "
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

### 算法思想   

每一趟从待排序的记录中选出关键字最小的记录，顺序放在已排好序的子表的最后，直到全部记录排序完毕。 

### 两种选择排序方法

1. 直接选择排序
2. 堆排序

### 直接选择排序
**基本思想**

设有n个元素，则需要n-1次循环。
每次循环通过两两对比，找到关键值最小的记录，经过n-1次循环后则可以得到一个有序的序列。


**代码**
```C
//  选择排序
void SelectSort(RecType R[],int n)
{
    int i,j;
    RecType tmp;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            //  R[i]的关键值与R[j]的关键值逐个比较，每次把较小的赋值给R[i]
            //  存在交换多次的问题
            if(R[i].key > R[j].key)
            {
                tmp = R[i];
                R[i] = R[j];
                R[j] = tmp;
            }
        }
    }
}
```

**性能评价**

时间复杂度：$O(n^2)$

稳定性：非稳定

### 直接选择排序 优化版

**基本思想**

直接选择排序在每一次找到最小值的过程中，需要进行多次关键值比较。
若比较结果成立，则记录的位置互换（执行赋值操作）。
例如要求关键字序列：`9 8 7 6 5` 按递增顺序显示，程序的第一次遍历结果如下：

```
1>   9 8 7 6 5 
2>   8 9 7 6 5
3>   7 9 8 6 5
4>   6 9 8 7 5
5>   5 9 8 7 6
```

很明显，第一次遍历找到的最小值应该是 `5`，但是找到最小值过程中，发生了多次无用的赋值操作（第2、3、4行）。
为了减少时间复杂度，在比较的过程中，使用一个变量保存最小值的索引值，直到与最后一个元素比较后，才执行赋值操作。优化后的程序第一次遍历的结果如下：

```
1>   9 8 7 6 5 
2>   5 9 8 7 6
```

**代码**

```C
//  选择排序 优化版
void SelectSort_v2(RecType R[],int n)
{
    int i,j,k;
    RecType tmp;
    for(i=0;i<n-1;i++)
    {
        //  默认第一个元素是最小的
        k = i;      
        for(j=i+1;j<n;j++)
            if(R[k].key > R[j].key)
                k = j;
        
        //  最后做一次比较，不相等则互相交换
        if(i != k)
        {
            tmp = R[k];
            R[k] = R[i];
            R[i] = tmp;
        }
    }
}
```

**性能评价**

时间复杂度：$O(n^2)$

稳定性：非稳定

### 直接选择排序代码
```C
#include <stdio.h>

typedef int KeyType;
typedef char InfoType[10];

typedef struct
{
    KeyType key;
    InfoType data;
} RecType;

void DisRecType(RecType R[],int n);
void SelectSort(RecType R[],int n);
void SelectSort_v2(RecType R[],int n);


//  选择排序
int main()
{
    int n = 10;
    KeyType a[] = {1,4,6,8,0,2,5,7,9,3};
    RecType R[10];
    for (int i = 0; i < n; i++)
        R[i].key = a[i];

    printf("排序前：");
    DisRecType(R,n);

    printf("选择排序 ... \n");
    SelectSort(R,n);

    printf("选择排序 改进版... \n");
    SelectSort_v2(R,n);


    printf("排序后：");
    DisRecType(R,n);
}

// 输出序列
void DisRecType(RecType R[],int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ",R[i].key);

    printf("\n");
}

//  选择排序
void SelectSort(RecType R[],int n)
{
    int i,j;
    RecType tmp;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            //  R[i]的关键值与R[j]的关键值逐个比较，每次把较小的赋值给R[i]
            //  存在交换多次的问题
            if(R[i].key > R[j].key)
            {
                tmp = R[i];
                R[i] = R[j];
                R[j] = tmp;
            }
        }
    }
}

//  选择排序 改进版
void SelectSort_v2(RecType R[],int n)
{
    int i,j,k;
    RecType tmp;
    for(i=0;i<n-1;i++)
    {
        //  默认第一个元素是最小的
        k = i;      
        for(j=i+1;j<n;j++)
            if(R[k].key > R[j].key)
                k = j;
        
        //  最后做一次比较，不相等则互相交换
        if(i != k)
        {
            tmp = R[k];
            R[k] = R[i];
            R[i] = tmp;
        }
    }
}
```

### 堆排序

**完全二叉树简介**

使用待排序 关键值序列 构建一棵完全二叉树，然后从上到下，从左到右，按顺序给完全二叉树编号。

>使用顺序存储结构，所以物理编号为 $0$ 的位置为空，从物理编号为 $1$ 的位置开始保存关键值。

根据完全二叉树的性质可知：
1. 若编号为 $i$ 的节点为分支节点，则 $2i$ 为左子节点，$2i+1$ 为右子节点；
2. 若编号为 $i$ 的节点有父节点，则父节点编号为 $floor(\frac {i} {2})$ ；
2. 若完全二叉树有 $n$ 个节点，则编号最大的分支节点为 $floor(\frac {n}{2})$ ；


**堆的定义**

$n$ 个关键字序列 $K_1,K_2,...,K_n$ 称为堆，当且仅当该序列满足如下性质：
1. $K_i<=K_{2i}$ 且 $K_i<=K_{2i+1}$ 
2. 或 $K_i>=K_{2i}$ 且 $K_i>=K_{2i+1}$       
$(1<=i<=floor(\frac {n}{2}))$ 

堆可分为小根堆和大根堆：
1. 小根堆：根节点关键值 **小于等于** 左右子节点关键值的堆；
2. 大根堆：根节点关键值 **大于等于** 左右子节点关键值的堆；

**基本思想**

从编号最大的分支节点开始（编号为 $floor(\frac {n}{2})$ ），**最大堆化** 每一棵树，直到根节点结束。
此时得到一个最大堆，因为最大堆的根节点关键值最大，所以保存根节点，然后使用最有一个叶子节点赋值给根节点，继续堆化，直到最后一个节点结束。


**代码**

```C
//  堆排序
void HeapSort(RecType R[],int n)
{
    int i,j;
    RecType tmp;
    for(i=n/2;i>0;i--)
        Heapify(R,i,n);
    
    for(j=n;j>0;j--)
    {
        tmp = R[j];
        R[j] = R[1];
        R[1] = tmp;
        Heapify(R,1,j-1);
    }
}

//  最大堆化
void Heapify(RecType R[],int p,int n)
{
    int i,j;
    RecType tmp;
    tmp = R[p];
    i = p;
    j = 2 * p;

    // 有至少一个子节点
    while (j <= n)
    {
        //  有两个子节点则找到较大的那个
        if(j < n && R[j].key < R[j+1].key) j++;

        //  父节点比子节点小，则子节点“上浮”到父节点，并且继续堆化
        if(tmp.key < R[j].key)
        {
            R[i] = R[j];
            i = j;
            j = 2 * j;
        }
        else
            break;
    }
    R[i] = tmp;
}
```

**性能评价**

时间复杂度：$O(nlog_2n)$

稳定性：非稳定




### 堆排序完整代码
```C
#include <stdio.h>

typedef int KeyType;
typedef char InfoType[10];

typedef struct
{
    KeyType key;
    InfoType data;
} RecType;

void DisRecType(RecType R[],int n);
void HeapSort(RecType R[],int n);
void Heapify(RecType R[],int p,int n);


//  选择排序
int main()
{
    int n = 10;
    KeyType a[] = {1,4,6,8,0,2,5,7,9,3};
    RecType R[10];
    for (int i = 0; i < n; i++)
        R[i+1].key = a[i];

    printf("排序前：");
    DisRecType(R,n);

    printf("堆排序... \n");
    HeapSort(R,n);

    printf("排序后：");
    DisRecType(R,n);
}

// 输出序列
void DisRecType(RecType R[],int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ",R[i+1].key);

    printf("\n");
}

//  堆排序
void HeapSort(RecType R[],int n)
{
    int i,j;
    RecType tmp;
    for(i=n/2;i>0;i--)
        Heapify(R,i,n);
    
    for(j=n;j>0;j--)
    {
        tmp = R[j];
        R[j] = R[1];
        R[1] = tmp;
        Heapify(R,1,j-1);
    }
}

//  堆化
void Heapify(RecType R[],int p,int n)
{
    int i,j;
    RecType tmp;
    tmp = R[p];
    i = p;
    j = 2 * p;

    // 有至少一个子节点
    while (j <= n)
    {
        //  有两个子节点则找到较大的那个
        if(j < n && R[j].key < R[j+1].key) j++;

        //  父节点比子节点小，则子节点“上浮”到父节点，并且继续堆化
        if(tmp.key < R[j].key)
        {
            R[i] = R[j];
            i = j;
            j = 2 * j;
        }
        else
            break;
    }
    R[i] = tmp;
}
```