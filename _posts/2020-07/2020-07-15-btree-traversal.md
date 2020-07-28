---
layout:         page
title:          "二叉树的遍历"
date:           2020-07-15 21:00:00 +0800
width:          700
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
keywords:       "树 二叉树 遍历 递归"
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

### 先序遍历（递归版）
```C
//  先序遍历 recursion
void PreOrderRcs(BTNode *b)
{
    if(b != NULL)
    {
        printf("%c",b->data);
        PreOrderRcs(b->lchild);
        PreOrderRcs(b->rchild);
    }
}
```
### 中序遍历（递归版）
```C
// 中序遍历 recursion
void InOrderRcs(BTNode *b)
{
    if(b != NULL)
    {
        InOrderRcs(b->lchild);
        printf("%c",b->data);
        InOrderRcs(b->rchild);
    }
}
```
### 后序遍历（递归版）
```C
// 后序遍历 recursion
void PostOrderRcs(BTNode *b)
{
    if(b != NULL)
    {
        PostOrderRcs(b->lchild);
        PostOrderRcs(b->rchild);
        printf("%c",b->data);
    }
}
```

### 先序遍历（非递归版）
```C

//  前序遍历 non-recursion
void PreOrderNRcs(BTNode *b)
{
    if(b != NULL)
    {
        BTNode *st[MaxSize],*tmp;
        int top = 0;
        st[top] = b;
        //先把跟节点放入栈中
        //循环从栈中取出元素
        //并访问元素的值（输出结果）
        //然后先放右子树，再放左子树
        //根据栈的特点，先取左子树，后取右子树
        while (top > -1)
        {   
            tmp = st[top--];
            printf("%c",tmp->data);
            if(tmp->rchild != NULL) st[++top] = tmp->rchild;
            if(tmp->lchild != NULL) st[++top] = tmp->lchild;
        } 
    }
    else
        printf("空树");
    
}
```
### 中序遍历（非递归版）
```C
// 中序遍历 non-recursion
void InOrderNRcs(BTNode *b)
{
    if (b != NULL)
    {
        BTNode *st[MaxSize],*tmp;
        int top = -1;
        tmp = b;

        while (top > -1 || tmp != NULL)
        {
            //  不断把左子树节点入栈，直到遇到叶子节点
            while(tmp != NULL)
            {
                top++;
                st[top] = tmp;
                tmp = tmp->lchild;
            }
            //开始出栈，并且返回右子树阶段
            //重新开始查找左子树
            if (top > -1)
            {
                tmp = st[top];
                top--;
                printf("%c",tmp->data);
                tmp = tmp->rchild;
            }
        }
    }    
    else
        printf("空树");
    
}
```
### 后序遍历（非递归版）
```C
// 后序遍历 non-recursion
void PostOrderNRcs(BTNode *b)
{
    if (b != NULL)
    {
        BTNode *st[MaxSize],*tmp;   //  tmp指针用于存储有孩子节点，默认为NULL
        int top = -1,flag;
        do
        {
            while (b != NULL)
            {
                top++;
                st[top] = b;
                b = b->lchild;
            }
            tmp = NULL;
            flag = 1;
            while (top != -1 && flag)
            {
                b = st[top];
                if(b->rchild == tmp)
                {
                    printf("%c",b->data);
                    top--;
                    tmp = b;
                }
                else
                {
                    b = b->rchild;
                    flag = 0;
                } 
            }
        } while (top != -1);            
    }
    else
        printf("空树");
    
}
```
### 层次遍历
```C
//利用循环队列实现二叉树的层次遍历
void LevelOrder(BTNode *b)
{
    BTNode *qu[MaxSize],*tmp;
    int front = -1, rear = -1;
    rear++;
    qu[rear] = b;
    while (front != rear)
    {
        front = (front + 1)%MaxSize;
        tmp = qu[front];
        printf("%c",tmp->data);
        if (tmp->lchild != NULL)
        {
            rear = (rear + 1)%MaxSize;
            qu[rear] = tmp->lchild;
        }
        if (tmp->rchild != NULL)
        {
            rear = (rear + 1)%MaxSize;
            qu[rear] = tmp->rchild;
        }
    }
}
```

### 完整代码
```C
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
typedef char ElemType;

typedef struct node
{
    ElemType data;        //数据元素
    struct node *lchild;  //指向左孩子
    struct node *rchild;  //指向右孩子
} BTNode;

BTNode *CreateBTNode(char *str);  //由str串创建二叉树
void DispBTNode(BTNode *b);       //以括号表示法输出二叉树
void PreOrderRcs(BTNode *b);      //先序遍历的 递归算法
void InOrderRcs(BTNode *b);       //中序遍历的 递归算法
void PostOrderRcs(BTNode *b);     //后序遍历的 递归算法

void PreOrderNRcs(BTNode *b);     //先序遍历的 非递归算法
void InOrderNRcs(BTNode *b);      //中序遍历的 非递归算法
void PostOrderNRcs(BTNode *b);    //后序遍历的 非递归算法

void LevelOrder(BTNode *b);       //层次遍历
void DestroyBTNode(BTNode *b);    //销毁二叉树

//  二叉树的遍历（先序遍历，中序遍历，后序遍历，层次遍历）
int main()
{
    BTNode *b;
    char cstr[] = "A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))";
    printf("  (1)创建二叉树:");
    b = CreateBTNode(cstr);
    printf("\n");
    printf("  (2)输出二叉树:");
    DispBTNode(b);
    printf("\n");

    printf("  (3)先序遍历（递归）序列:");
    PreOrderRcs(b);
    printf("\n");
    printf("  (4)中序遍历（递归）序列:");
    InOrderRcs(b);
    printf("\n");
    printf("  (5)后序遍历（递归）序列:");
    PostOrderRcs(b);
    printf("\n");

    printf("  (6)先序遍历（非递归）序列:");
    PreOrderNRcs(b);
    printf("\n");
    printf("  (7)中序遍历（非递归）序列:");
    InOrderNRcs(b);
    printf("\n");
    printf("  (8)后序遍历（非递归）序列:");
    PostOrderNRcs(b);
    printf("\n");

    printf("  (9)层次遍历序列:");
    LevelOrder(b);
    printf("\n");

    printf("  (10)释放二叉树b\n");
    DestroyBTNode(b);
    return 0;
}

BTNode *CreateBTNode(char *str)
{
    BTNode *tmp=NULL,*T=NULL,*tmpStack[MaxSize];
    int top = -1,i = 0,k;
    char ch ;

    while ((ch = str[i++]) != '\0')
    {
        switch (ch)
        {
        case '(':
            tmpStack[++top] = tmp;  //  左括号前面的节点入栈
            k = 1;  //  左括号后面跟着左子树 用 k=1 表示
            break;
        case ')':
            top--;  //  出栈
            break;
        case ',':
            k = 2;  // 右括号后面跟着右子树 用 k=2 表示
            break;
        default:
            tmp = (BTNode *)malloc(sizeof(BTNode));
            tmp->data = ch;
            tmp->lchild = tmp->rchild = NULL;
            if(T == NULL)
                T = tmp;    //  第一个节点
            else
                switch (k)
                {
                    case 1:
                        tmpStack[top]->lchild = tmp;
                        break;
                    case 2:
                        tmpStack[top]->rchild = tmp;
                        break;
                }

            break;
        }
    }
    
    return T;
}


void DispBTNode(BTNode *b)
{
    if(b != NULL)
    {
       printf("%c",b->data); 
       if(b->lchild != NULL || b->rchild != NULL)
       {    //  有左子树 或者 右子树 时，输出括号
            printf("("); 
            if(b->lchild != NULL)
                DispBTNode(b->lchild);  // 有左子树时 输出左子树
            if(b->rchild != NULL)   //  右子树时，输出逗号和右子树
            {
                printf(","); 
                DispBTNode(b->rchild);
            }
            printf(")"); 
       }
    }  
}

//  前序遍历 recursion
void PreOrderRcs(BTNode *b)
{
    if(b != NULL)
    {
        printf("%c",b->data);
        PreOrderRcs(b->lchild);
        PreOrderRcs(b->rchild);
    }
}
// 中序遍历 recursion
void InOrderRcs(BTNode *b)
{
    if(b != NULL)
    {
        InOrderRcs(b->lchild);
        printf("%c",b->data);
        InOrderRcs(b->rchild);
    }
}

// 后序遍历 recursion
void PostOrderRcs(BTNode *b)
{
    if(b != NULL)
    {
        PostOrderRcs(b->lchild);
        PostOrderRcs(b->rchild);
        printf("%c",b->data);
    }
}

//  前序遍历 non-recursion
void PreOrderNRcs(BTNode *b)
{
    if(b != NULL)
    {
        BTNode *st[MaxSize],*tmp;
        int top = 0;
        st[top] = b;
        //先把跟节点放入栈中
        //循环从栈中取出元素
        //并访问元素的值（输出结果）
        //然后先放右子树，再放左子树
        //根据栈的特点，先取左子树，后取右子树
        while (top > -1)
        {   
            tmp = st[top--];
            printf("%c",tmp->data);
            if(tmp->rchild != NULL) st[++top] = tmp->rchild;
            if(tmp->lchild != NULL) st[++top] = tmp->lchild;
        } 
    }
    else
        printf("空树");
    
}

// 中序遍历 non-recursion
void InOrderNRcs(BTNode *b)
{
    if (b != NULL)
    {
        BTNode *st[MaxSize],*tmp;
        int top = -1;
        tmp = b;

        while (top > -1 || tmp != NULL)
        {
            //  不断把左子树节点入栈，直到遇到叶子节点
            while(tmp != NULL)
            {
                top++;
                st[top] = tmp;
                tmp = tmp->lchild;
            }
            //开始出栈，并且返回右子树阶段
            //重新开始查找左子树
            if (top > -1)
            {
                tmp = st[top];
                top--;
                printf("%c",tmp->data);
                tmp = tmp->rchild;
            }
        }
    }    
    else
        printf("空树");
    
}

// 后序遍历 non-recursion
void PostOrderNRcs(BTNode *b)
{
    if (b != NULL)
    {
        BTNode *st[MaxSize],*tmp;   //  tmp指针用于存储有孩子节点，默认为NULL
        int top = -1,flag;
        do
        {
            while (b != NULL)
            {
                top++;
                st[top] = b;
                b = b->lchild;
            }
            tmp = NULL;
            flag = 1;
            while (top != -1 && flag)
            {
                b = st[top];
                if(b->rchild == tmp)
                {
                    printf("%c",b->data);
                    top--;
                    tmp = b;
                }
                else
                {
                    b = b->rchild;
                    flag = 0;
                } 
            }
        } while (top != -1);            
    }
    else
        printf("空树");
    
}


//利用循环队列实现二叉树的层次遍历
void LevelOrder(BTNode *b)
{
    BTNode *qu[MaxSize],*tmp;
    int front = -1, rear = -1;
    rear++;
    qu[rear] = b;
    while (front != rear)
    {
        front = (front + 1)%MaxSize;
        tmp = qu[front];
        printf("%c",tmp->data);
        if (tmp->lchild != NULL)
        {
            rear = (rear + 1)%MaxSize;
            qu[rear] = tmp->lchild;
        }
        if (tmp->rchild != NULL)
        {
            rear = (rear + 1)%MaxSize;
            qu[rear] = tmp->rchild;
        }
    }
}

//销毁二叉树
void DestroyBTNode(BTNode *b)
{
    if (b != NULL)
    {
        DestroyBTNode(b->lchild);
        DestroyBTNode(b->rchild);
        free(b);
    }
}
```