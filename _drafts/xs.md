---
layout:         page
title:          "线性表的实现"
date:           2020-06-05 21:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
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

#### 线性表的定义和属性
定义：线性表是具有相同特性的数据元素的一个有序序列。按存储结构的不同，可分为顺序表和链表。
>使用逻辑结构二元组表示：
>
>$B=(D,R)$
>
>$D=\{d_i | d_i \in ElemType , 1 <= i <= n,n>=0\}$
>
>$R=\{<r_{j-1},r_j> | 1<=j<=m,m>=0\}$

线性表的几个属性：

- 空表：当$n=0$时，表示线性表是一个空表，即表中不包含任何元素
- 前驱：$a_{i-1}$是$a_i$的前驱，$2 <= i <= n$
- 后继：$a_{i+1}$是$a_i$的后继，$1 <= i <= n - 1$
- 表头元素：表中第一个元素$a_1$
- 表尾元素：最后一个元素$a_n$


#### 线性表的抽象数据类型
```C
ADT List
{
数据对象：
    D = {ai | ai ∈ ElemType, i=1,2,…,n, n>=0 }              // ElemType为类型标识符
数据关系：
    R = {<ai-1, ai> | ai-1, ai ∈ D, i=2,3,…,n }
数据操作：
    (1) tabSeq * InitList();	                            // 初始化一个空的线性表
    (2) void CreateList(tabSeq *L, ElemType a[], int n);	// 创建线性表
    (3) Bool ListEmpty(tabSeq *L);	                        // 判断线性表是否为空
    (4) int ListLength(tabSeq *L);	                        // 返回线性表的长度
    (5) void DispList(tabSeq *L);	                        // 输出线性表元素
    (6) Bool GetElem(tabSeq *L,int i,ElemType *e);	        // 返回指定序号的元素
    (7) int LocateElem(tabSeq *L, ElemType e);	            // 返回指定元素的序号
    (8) Bool ListInsert(tabSeq *L,int i,ElemType e);	    // 在指定序号位置插入元素
    (9) Bool ListDelete(tabSeq *L,int i,ElemType *e);	    // 在指定序号位置删除元素
}
```

#### 顺序表实现代码
>线性表是基于逻辑结构的，而顺序表是基于存储结构的。

顺序表的存储结构是指把顺序表中的所有元素存储到一块连续的存储空间，我们可以认为是一个数组。于是定义顺序表的存储结构定义为：
```C
#define MaxSize 150
typedef int ElemType;
typedef struct
{
    ElemType data[MaxSize];
    int length;
} tabSeq;
```
把顺序表中的元素依次存储到数据data，并且更新长度length。接下来具体实现抽象数据类型里定义的抽象方法。
```C
//  初始化一个空的线性表
tabSeq * InitList();
// 创建线性表
void CreateList(tabSeq *L, ElemType a[], int n);
// 判断线性表是否为空
Bool ListEmpty(tabSeq *L);
// 返回线性表的长度
int ListLength(tabSeq *L);
// 输出线性表元素
void DispList(tabSeq *L);
//  返回指定序号的元素
Bool GetElem(tabSeq *L,int i,ElemType *e);
//  返回指定元素的序号
int LocateElem(tabSeq *L, ElemType e);
//  在指定序号位置插入元素
Bool ListInsert(tabSeq *L,int i,ElemType e);
//  在指定序号位置删除元素
Bool ListDelete(tabSeq *L,int i,ElemType *e);
```

顺序表代码：
```C
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 150
#define true 1
#define false 0

typedef int ElemType;
typedef int Bool;

typedef struct
{
    ElemType data[MaxSize];
    int length;
} tabSeq;


//  初始化一个空的线性表
tabSeq * InitList();
// 创建线性表
void CreateList(tabSeq *L, ElemType a[], int n);
// 判断线性表是否为空
Bool ListEmpty(tabSeq *L);
// 返回线性表的长度
int ListLength(tabSeq *L);
// 输出线性表元素
void DispList(tabSeq *L);
//  返回指定序号的元素
Bool GetElem(tabSeq *L,int i,ElemType *e);
//  返回指定元素的序号
int LocateElem(tabSeq *L, ElemType e);
//  在指定序号位置插入元素
Bool ListInsert(tabSeq *L,int i,ElemType e);
//  在指定序号位置删除元素
Bool ListDelete(tabSeq *L,int i,ElemType *e);

int main()
{
    tabSeq *T;
    T = InitList();
    ElemType x[6] = {1,2,3,4,5,6};
    if (ListEmpty(T)) printf("null\n");
    else printf("not null\n");
    CreateList(T,x,6);
    printf("CreateList\n");
    if (ListEmpty(T)) printf("null\n");
    else printf("not null\n");
    printf("length of list=%d\n",ListLength(T));
    DispList(T);
    int num;
    if(GetElem(T,3,&num)) printf("num = %d\n",num);
    else printf("false\n");
    printf("index of 6  = %d\n",LocateElem(T,6));
    ListInsert(T,1,0);
    DispList(T);
    if(ListDelete(T,1,&num)) printf("num = %d\n",num);
    else printf("false\n");
    DispList(T);
    return 0;
}

Bool ListDelete(tabSeq *L,int i,ElemType *e)
{
    i--;
    if (i<0 || i>L->length-1) return false;
    *e = L->data[i];
    for(int j=i;j<L->length;j++)
        L->data[j] = L->data[j+1];

    L->length--;
    return true;
}

Bool ListInsert(tabSeq *L,int i,ElemType e)
{
    i--;
    if (i<0 || i>L->length) return false;
    for(int j=L->length;j>i;j--)
        L->data[j] = L->data[j-1];

    L->data[i] = e;
    L->length++;
    return true;
}

int LocateElem(tabSeq *L, ElemType e)
{
    if (ListEmpty(L)) return -1;
    for(int i=0;i<L->length;i++)
        if(L->data[i] == e) return i+1;

    return -1;
}

Bool GetElem(tabSeq *L,int i,ElemType *e)
{
    i--;
    if (i<0 || i>L->length-1) return false;
    *e = L->data[i];
    return true;
}

void DispList(tabSeq *L)
{
    printf("output elem: ");
    for(int i=0;i<L->length;i++)
        printf("%d\t",L->data[i]);

    printf("\n");
}

int ListLength(tabSeq *L)
{
    return L->length;
}

Bool ListEmpty(tabSeq *L)
{
    return L->length>0?false:true;
}

void CreateList(tabSeq *L, ElemType a[], int n)
{
    for(int i=0;i<n;i++)
        L->data[i] = a[i];
    
    L->length = n;
}

tabSeq* InitList()
{
    tabSeq *tmp = (tabSeq *)malloc(sizeof(tabSeq));
    tmp->length = 0;
    return tmp;
}
```

#### 链表实现代码
