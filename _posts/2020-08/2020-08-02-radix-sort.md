---
layout:         page
title:          "一种不需要比较的排序方法——基数排序"
date:           2020-08-02 13:30:00 +0800
width:          700
author:         zaofengchen
catalog:        true 
permalink:      /:year/:month/:day/:title
keywords:       "数据结构 排序算法 基数排序 "
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

基数排序是一种借助于多关键字排序的思想对单关键字排序的方法。

>基数排序也有人称桶排序，因为借助于10个桶（0~9号桶）临时存放记录。

基数排序算法通过若干次 $(loop)$ 分配和收集实现排序。$loop$ 值由最大的记录关键值的位数决定，例如待排序的表中，最大的记录关键值为100，那么 $loop$ 等于3，需要3次分配和收集才能实现有序表。

第一次分配，需要取 记录关键值的个位数 为索引值，存放到对应的桶里面，如果有相同的索引值，则按顺序存储。

第一次收集，需要按桶的索引值和桶里面记录值的顺序收集。

这样就完成了第一次分配和收集。

第二次、第三次分配收集也是按照这样的过程完成。

>一道使用基数排序解决的题 [leetcode 128h 最长连续序列](/2020/06/06/leetcode-128)

### 性能评价

时间复杂度：$O(n)$

稳定性：稳定




### 基数排序完整代码
```C
#include <stdio.h>
#include <stdlib.h>
typedef int KeyType;
typedef char InfoType[10];

typedef struct node
{
    KeyType key;
    InfoType data;
    struct node *next;
} RecType;

void DisRecType(RecType *p);
RecType* generalPNode(int* nums, int numsSize);
int getMaxNum(RecType *p);
int GetMaxLoop(int num);
int getBaseNum(int num,int numSt);
void RadixSort(RecType **p);

//  基数排序
int main()
{
    int n = 10;
    RecType *p;
    KeyType a[] = {1,4,6,8,0,2,5,7,9,3};
    p =generalPNode(a, n);

    printf("排序前：");
    DisRecType(p);

    printf("基数排序 ... \n");
    RadixSort(&p);

    printf("排序后：");
    DisRecType(p);
    return 0;
}

// 输出序列
void DisRecType(RecType *p)
{
    while (p != NULL)
    {
        printf("%d ",p->key);
        p = p->next;
    }
    printf("\n");
}

//  构造基数排序存储结构
RecType* generalPNode(int* nums, int numsSize)
{
    int i;
    RecType *p = NULL,*q = NULL,*tmp;
    for(i=0;i<numsSize;i++)
    {
        tmp = (RecType *)malloc(sizeof(RecType));
        tmp->key = nums[i];
        tmp->next = NULL;
        if(q == NULL)
        {
            q = tmp;
            p = q;
        }
        else
        {
            q->next = tmp;
            q = tmp;
        }
    }
    return p;
}

//  归并排序
void RadixSort(RecType **p)
{
    int max = getMaxNum(*p);
    int	loop = GetMaxLoop(max);

    RecType *head[10],*tail[10],*tmp;
    int i,j,k;

    for (i = 1; i <= loop; i++)
    {
        //  每次循环，先清空各个桶里的数据
        for(j = 0; j < 10; j++)
            head[j] = tail[j] = NULL;

        //  分配
        //  把链表的分配到指定的桶里
        //  由于是链式存储，所以每个桶里的实际数据是head和tail指针之间的节点
        while ((*p) != NULL)
        {
            k = getBaseNum((*p)->key,i);

            if (head[k] == NULL)
                head[k] = (*p);
            else
                tail[k]->next = (*p);

            tail[k] = (*p);
            (*p) = (*p)->next;
        }

        //  重置链表
        (*p) = NULL;     

        //  收集
        //  各个桶里的实际数据是有head和tail指针确定的
        //  所以把各个桶按顺序，按照 tail->next = head 连接起来
        //  最后把 tail->next = NULL 就完成了收集工作
        for ( j = 0; j < 10; j++)
        {
            if (head[j] != NULL)
            {
                if ((*p) == NULL)
                    (*p) = head[j];    
                else
                    tmp->next = head[j];
                tmp = tail[j];
            }
        }
        tmp->next = NULL;
    }
}

//  返回最大关键值
int getMaxNum(RecType *p)
{
    int max = 0;
    while (p != NULL)
    {
        if(p->key > max) max = p->key;
        p = p->next;
    }
    return max;
}

//  返回整数的位数
int GetMaxLoop(int num)
{
	int bits = 1;
	num /= 10;
	while (num != 0)
	{
		++bits;
		num /= 10;
	}
	return bits;
}

//  返回整数指定位序号的值
int getBaseNum(int num,int numSt)
{
    int numTimes = 1;
    int i,baseNum;
    for(i=1;i<numSt;i++)
    {
        numTimes *= 10;
    }
    baseNum = num/numTimes%10;
    return baseNum;
}
```