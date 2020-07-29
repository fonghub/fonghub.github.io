---
layout:         page
title:          "插入排序——直接插入排序、希尔排序"
date:           2020-07-28 13:30:00 +0800
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "数据结构 排序算法 直接插入排序 折半插入排序 希尔排序 "
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
每次将一个待排序的记录，按其关键字大小插入到前面已经排好序的子表中的适当位置，直到全部记录插入完成为止。

### 两种插入排序方法
1. 直接插入排序
2. 希尔排序

### 直接插入排序
**基本思想**

假设待排序的记录存放在数组 $R[0...n-1]$中，排序过程的某一中间时刻，$R$ 被划分成两个子区间 $R_1[0...i-1]$ 和 $R_2[i...n-1]$ ，其中$R_1$ 为有序区（默认只有第一个元素），$R_2$ 为无序区。
直接插入排序的基本操作是将当前无序区的第1个记录 $R_2[i]$ 插入到有序区 $R_1[0...i-1]$ 中适当的位置上，使 $R_1[0...i]$ 变为新的有序区。
直接插入排序每次使有序区增加1个记录，故常称为增量法。

**代码**

```C
// 直接插入排序
void InsertSort(RecType R[],int n)
{
    int i,j;
    RecType tmp;
    for ( i = 1; i < n; i++)
    {
        tmp = R[i];
        j = i - 1;
        while (j >= 0 && tmp.key < R[j].key)
        {
            R[j+1] = R[j];
            j--;
        }    
        R[j+1] = tmp;
    }
}
```

**性能评价**

时间复杂度：$O(n^2)$

稳定性：稳定

### 折半插入排序
**基本思想**

折半插入排序算法的步骤可分为三步：
1. 通过折半查找，找到 $R_2[i]$ 的位置；
2. 移动有序区 $R_1[0...i-1]$ 中的元素，给 $R_2[i]$ 空出一个位置；
3. $R_2[i]$ 赋值到正确的位置

因为 $R_2[i]$ 在有序区 $R_1[0...i-1]$ 中的位置是一定的，所以折半插入排序的元素移动次数与直接插入排序相同，不同的是找到该位置的计算量不同。

因为折半插入排序使用了折半查找，计算次数上肯定会少于使用顺序查找的直接插入排序，所以性能上有一定的优势。
>折半插入排序是直接插入排序的改进版。

**代码**

```C
// 折半插入排序
void BinInsertSort(RecType R[],int n)
{
    int i,j;
    int left,mid,right;
    RecType tmp;
    for ( i = 1; i < n; i++)
    {
        tmp = R[i];
        left = 0;
        right = i-1;
        while (left <= right)
        {
            mid = (left + right)/2;
            if(tmp.key < R[mid].key)
                right = mid - 1;
            else
                left = mid + 1;
        }

        for(j=i-1;j>=right+1;j--)
            R[j+1] = R[j];
        
        R[right+1] = tmp;
    }
}
```

**性能评价**

时间复杂度：$O(n^2)$

稳定性：不稳定

### 希尔排序
**介绍**

希尔排序（Shellsort），也称递减增量排序算法，是插入排序的一种更高效的改进版本。
>希尔排序按其设计者 Donald Shell 的名字命名，该算法由1959年公布。


**基本思想**

希尔排序通过将比较的全部元素分为几个区域来提升插入排序的性能，这样可以让一个元素可以一次性地朝最终位置前进一大步。
然后算法再取越来越小的步长进行排序，算法的最后一步就是普通的插入排序，但是到了这步，需排序的数据几乎是已排好的了（此时插入排序较快）。

步长的选择是希尔排序的重要部分。只要最终步长为1任何步长序列都可以工作。
>Donald Shell最初建议步长选择为 $\frac{n}{2}$，并且每一次循环对步长取半，直到步长达到 $1$。

**代码**
```C
// shell插入排序
void ShellSort(RecType R[],int n)
{
    int i,j,gap;
    gap = n/2;
    RecType tmp;
    while (gap > 0)
    {
        for(i=gap;i<n;i++)
        {
            tmp = R[i];
            j = i - gap;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j+gap] = R[j];
                j -= gap;
            }
            R[j+gap] = tmp;
        }
        gap /=2;
    }
}
```

**性能评价**

时间复杂度：$O(n^{1.3})$

稳定性：不稳定


### 完整代码
```C
#include <stdio.h>

typedef int KeyType;
typedef char InfoType[10];

typedef struct
{
    KeyType key;
    InfoType data;
} RecType;

void InsertSort(RecType R[],int n);
void BinInsertSort(RecType R[],int n);
void ShellSort(RecType R[],int n);
void DisRecType(RecType R[],int n);

int main()
{
    int n = 10;
    KeyType a[] = {1,4,6,8,0,2,5,7,9,3};
    RecType R[10];
    for (int i = 0; i < n; i++)
        R[i].key = a[i];
    
    printf("排序前：");
    DisRecType(R,n);

    printf("直接插入排序 ... \n");
    InsertSort(R,n);

    printf("折半插入排序 ... \n");
    BinInsertSort(R,n);

    printf("shell插入排序 ... \n");
    ShellSort(R,n);

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

// 直接插入排序
void InsertSort(RecType R[],int n)
{
    int i,j;
    RecType tmp;
    for ( i = 1; i < n; i++)
    {
        tmp = R[i];
        j = i - 1;
        while (j >= 0 && tmp.key < R[j].key)
        {
            R[j+1] = R[j];
            j--;
        }    
        R[j+1] = tmp;
    }
}

// 折半插入排序
void BinInsertSort(RecType R[],int n)
{
    int i,j;
    int left,mid,right;
    RecType tmp;
    for ( i = 1; i < n; i++)
    {
        tmp = R[i];
        left = 0;
        right = i-1;
        while (left <= right)
        {
            mid = (left + right)/2;
            if(tmp.key < R[mid].key)
                right = mid - 1;
            else
                left = mid + 1;
        }

        for(j=i-1;j>=right+1;j--)
            R[j+1] = R[j];
        
        R[right+1] = tmp;
    }
}

// shell插入排序
void ShellSort(RecType R[],int n)
{
    int i,j,gap;
    gap = n/2;
    RecType tmp;
    while (gap > 0)
    {
        for(i=gap;i<n;i++)
        {
            tmp = R[i];
            j = i - gap;
            while (j >= 0 && tmp.key < R[j].key)
            {
                R[j+gap] = R[j];
                j -= gap;
            }
            R[j+gap] = tmp;
        }
        gap /=2;
    }
}
```

