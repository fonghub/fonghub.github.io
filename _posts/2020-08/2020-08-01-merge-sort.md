---
layout:         page
title:          "归并排序"
date:           2020-08-01 13:30:00 +0800
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "数据结构 排序算法 归并排序 "
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

归并排序简单的来说是把两个有序表合并成一个有序表。

一开始从规模最小的只有1个记录的两个表开始合并，使待排序表局部有序。
随着记录规模的扩大，待排序表从局部有序逐渐变成整体有序。

>每一次循环的规模都遵循2倍数扩大，从一开始的1个记录，到2、4、8、...，递增。

每一次归并排序都需要借助开辟的存储空间来保存合并后的有序表，然后再复制到原来的表上，不能在原来的表上直接操作。

<img src="https://tva1.sinaimg.cn/large/007S8ZIlgy1ghf8kk991yj30u016fjyp.jpg" width="{{ page.width}}" align="bottom" />

### 性能评价

时间复杂度：$O(nlog_2n)$

稳定性：稳定




### 归并排序完整代码
```C
#include <stdio.h>
#include <stdlib.h>
typedef int KeyType;
typedef char InfoType[10];

typedef struct
{
    KeyType key;
    InfoType data;
} RecType;

void DisRecType(RecType R[],int n);
void MergeSort(RecType R[],int n);
void MergeSortWithLength(RecType R[],int length,int n);
void Merge(RecType R[],int left,int mid,int right);

//  归并排序
int main()
{
    int n = 10;
    KeyType a[] = {1,4,6,8,0,2,5,7,9,3};
    RecType R[10];
    for (int i = 0; i < n; i++)
        R[i].key = a[i];

    printf("排序前：");
    DisRecType(R,n);

    printf("归并排序 ... \n");
    MergeSort(R,n);

    printf("排序后：");
    DisRecType(R,n);
    return 0;
}

// 输出序列
void DisRecType(RecType R[],int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ",R[i].key);

    printf("\n");
}

void MergeSort(RecType R[],int n)
{
    int length=1;
    while (length < n)
    {
        MergeSortWithLength(R,length,n);
        length *= 2;
    }
}

void MergeSortWithLength(RecType R[],int length,int n)
{
    int i = 0;                  //  第一个有序数组开始下标   
    int k = i + length - 1;     //  第一个有序数组结束下标           
    int j = i + 2*length - 1;   //  第二个有序数据结束下标
    while (j < n)
    {
        Merge(R,i,k,j);
        i = j + 1;
        k = i + length - 1;
        j = i + 2*length - 1;
    }

    //  剩下至少有 length 个记录，才需要整理排序
    if(k < n)
    {
        Merge(R,i,k,n-1);
    }
}

//  合并两个有序数组成一个有序数组
void Merge(RecType R[],int left,int mid,int right)
{
    int i = left,j = mid + 1,k=0;
    RecType *tmp = (RecType *)malloc(sizeof(RecType) * (right-left+1));
    
    while (i <= mid && j <= right)
        if(R[i].key < R[j].key)
            tmp[k++] = R[i++];
        else
            tmp[k++] = R[j++];
    
    while (i <= mid)
        tmp[k++] = R[i++];

    while (j <= right)
        tmp[k++] = R[j++];

    for (int k = 0,i = left; i<=right; i++,k++)
        R[i] = tmp[k]; 
}
```