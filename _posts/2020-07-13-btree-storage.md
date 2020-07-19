---
layout:         page
title:          "二叉树的存储"
date:           2020-07-13 21:00:00 +0800
width:          350
author:         zaofengchen
catalog:        true
permalink:      /:year/:month/:day/:title
keywords:       "树 二叉树 存储"
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


### 二叉树的抽象数据类型
二叉树是有相同特性的n(n>=0)个数据节点组成的一个有穷序列，节点之间存在一对多的关系。

严格区分左子树和右子树，并且先有左子树后有右子树。

树的抽象运算方法有：构造树，遍历树，查找节点，查找左右子树等。

```C
ADT Tree
{
数据对象：
    D = {ai | ai ∈ ElemType, i=1,2,…,n, n>=0 }              // ElemType为类型标识符
数据关系：
    R = {<ai,aj> | ai, aj∈D, i=1,2,…,n, j=1,2,…,n，其中每个元素只有一个前驱节点 ，可以有零个或多个后继节点，有且仅有一个元素（根节点）没有前驱节点 }
数据操作：
    BTNode *CreateBTNode(char *str);            //由str串创建二叉树
    BTNode *FindNode(BTNode *b, ElemType x);    //返回data域为x的节点指针
    BTNode *LchildNode(BTNode *p);              //返回p节点的左孩子节点指针
    BTNode *RchildNode(BTNode *p);              //返回p节点的右孩子节点指针
    int BTNodeDepth(BTNode *b);                 //求二叉树b的深度
    void DispBTNode(BTNode *b);                 //以括号表示法输出二叉树
    void DestroyBTNode(BTNode *b);              //销毁二叉树
}
```

### 顺序存储结构

顺序存储结构把树节点保存到连续的存储空间中，借助于 **[串结构](/2020/06/17/string#顺序串)** 的运算构造二叉树。

根据 **[性质4](/2020/07/11/btree#二叉树的性质)** 可知：
- 若编号为 $i$ 的节点是分支节点，那么其左子节点编号为 $2i$ ，其右子节点编号为$2i+1$ ；
- 若编号为 $i$ 的节点不是根节点，那么其父节点编号为 $floor(i/2)$ 。

利用 **性质4** 可以很方便的找到父节点或者子节点。

顺序存储结构的优点是节省空间，缺点是描述二叉树作为参数输入比较麻烦。

```C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxSize 100
typedef char ElemType;

//借助串结构构造顺序存储结构二叉树
typedef struct
{   char data[MaxSize];         
    int length;                 
} treeSeq;

treeSeq * InitTree();
void CreateTree(treeSeq *t,char *str); //由str串创建二叉树
int FindNode(treeSeq *t,char c);       //返查找节点
char LchildNode(treeSeq *t,int index); //返回指定编号节点的左孩子节点
char RchildNode(treeSeq *t,int index); //返回指定编号节点的右孩子节点
int MaxIndex(treeSeq *t);              //返回树节点的最大编号
int TreeDepth(int index);              //根据节点的最大编号求二叉树的深度
void DispTree(treeSeq *t);             //输出二叉树
void DestroyTree(treeSeq *t);          //销毁二叉树

int main()
{
    char cstr[] = "ABCDEFG##H####I";
    treeSeq *t;
    printf("  (1)初始化，创建二叉树:");
    t = InitTree();
    CreateTree(t,cstr);
    printf("\n");
    printf("  (2)输出二叉树:");
    DispTree(t);
    printf("\n");
    printf("  (3)查找节点B:");
    int index = FindNode(t, 'B');
    if(index) 
    {
        printf("节点B的index=%d\n",index);
        printf("  (4)");
        char lp = LchildNode(t,index);
        if (lp != '\0')
            printf("左孩子为%c ", lp);
        else
            printf("无左孩子 ");

        char rp = RchildNode(t,index);
        if (rp != '\0')
            printf("右孩子为%c", rp);
        else
            printf("无右孩子 ");
    }
    else
        printf("节点B未找到！");
    
    printf("\n");
    int maxIndex = MaxIndex(t);
    int h = TreeDepth(maxIndex);
    printf("  (4)二叉树b的深度:%d\n", h);
    printf("  (5)释放二叉树t\n");
    DestroyTree(t);
    return 0;
}

//初始化空树
treeSeq * InitTree()
{
    treeSeq *tmp = (treeSeq *)malloc(sizeof(treeSeq));
    tmp->data[0] = '#';
    tmp->length = 0;
    return tmp;
}

//字符串表示法创建二叉树
void CreateTree(treeSeq *t,char cstr[])
{
    int i = 0;
    while (cstr[i] != '\0')
    {
        t->data[i+1] = cstr[i];
        i++;
    }
    t->length = i;
}

//输出二叉树
void DispTree(treeSeq *t)
{
    for(int i=1;i<t->length;i++)
    {
        printf("%c",t->data[i]);
    }
}


//查找节点
int FindNode(treeSeq *t, char c)
{
    for(int i=1;i<t->length;i++)
    {
        if(t->data[i] == c) return i;
    }
    return 0;
}

//左子树
char LchildNode(treeSeq *t,int index)
{
    if (2*index > t->length || t->data[2*index] == '#')
        return '\0';

    return t->data[2*index];
}

//右子树
char RchildNode(treeSeq *t,int index)
{
    if (2*index+1 > t->length || t->data[2*index] == '#')
        return '\0';

    return t->data[2*index+1];
}

//二叉树深度
int TreeDepth(int index)
{
    int h = 1;
    if(index < 1) return 0;
    while (index > 1)
    {
        h++;
        index = (int)floor(index/2);
    }
    return h;
}

//获取最大节点编号
int MaxIndex(treeSeq *t)
{
    for(int i=t->length;i>0;i++)
    {
        if(t->data[i] != '#') return i;
    }
}

//销毁二叉树
void DestroyTree(treeSeq *t)
{
    free(t);
}
```

### 链式存储结构

一个树节点包括有一个值域和两个分别指向左子树和右子树的指针，链式存储结构定义为：
```C
typedef struct node
{
    ElemType data;         //数据元素
    struct node *lchild;   //指向左孩子
    struct node *rchild;   //指向右孩子
} BTNode;
```

代码实现：
```C
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
typedef char ElemType;

typedef struct node
{
    ElemType data;         //数据元素
    struct node *lchild;   //指向左孩子
    struct node *rchild;   //指向右孩子
} BTNode;

BTNode *CreateBTNode(char *str);         //由str串创建二叉树
BTNode *FindNode(BTNode *b, ElemType x); //返回data域为x的节点指针
BTNode *LchildNode(BTNode *p);           //返回p节点的左孩子节点指针
BTNode *RchildNode(BTNode *p);           //返回p节点的右孩子节点指针
int BTNodeDepth(BTNode *b);              //求二叉树b的深度
void DispBTNode(BTNode *b);              //以括号表示法输出二叉树
void DestroyBTNode(BTNode *b);           //销毁二叉树

int main()
{
    BTNode *b, *p, *lp, *rp;
    printf("  (1)创建二叉树:");
    b = CreateBTNode("A(B(D,E(H(J,K(L,M(,N))))),C(F,G(,I)))");
    printf("\n");
    printf("  (2)输出二叉树:");
    DispBTNode(b);
    printf("\n");
    printf("  (3)查找H节点:");
    p = FindNode(b, 'H');
    if (p != NULL)
    {
        lp = LchildNode(p);
        if (lp != NULL)
            printf("左孩子为%c ", lp->data);
        else
            printf("无左孩子 ");
        rp = RchildNode(p);
        if (rp != NULL)
            printf("右孩子为%c", rp->data);
        else
            printf("无右孩子 ");
    }
    else
        printf(" 未找到！");
    printf("\n");
    printf("  (4)二叉树b的深度:%d\n", BTNodeDepth(b));
    printf("  (5)释放二叉树b\n");
    DestroyBTNode(b);
    return 0;
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

//二叉树深度
int BTNodeDepth(BTNode *b)
{
    int lchilddep, rchilddep;
    if (b == NULL)
        return 0;
    else
    {
        lchilddep = BTNodeDepth(b->lchild);
        rchilddep = BTNodeDepth(b->rchild);
        return (lchilddep > rchilddep) ? (lchilddep + 1) : (rchilddep + 1);
    }
}

//左子树
BTNode *LchildNode(BTNode *p)
{
    if (p == NULL)
        return NULL;
    return p->lchild;
}

//右子树
BTNode *RchildNode(BTNode *p)
{
    if (p == NULL)
        return NULL;
    return p->rchild;
}

//括号表示法创建二叉树
BTNode *CreateBTNode(char *str)
{
    BTNode *st[MaxSize], *p = NULL,*b = NULL;
    int top = -1, k, j = 0;
    char ch = str[j];
    while (ch != '\0')
    {
        switch (ch)
        {
        case '(':
            top++;
            st[top] = p;
            k = 1;
            break;
        case ')':
            top--;
            break;
        case ',':
            k = 2;
            break;
        default:
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = ch;
            p->lchild = p->rchild = NULL;
            //第一个元素为根节点，
            if (b == NULL)
                b = p;
            else
            {
                switch (k)
                {
                case 1:
                    st[top]->lchild = p;
                    break;
                case 2:
                    st[top]->rchild = p;
                    break;
                }
            }
            break;
        }
        ch = str[++j];
    }

    return b;
}

//括号表示法输出二叉树
void DispBTNode(BTNode *b)
{
    if(b != NULL)
    {
       printf("%c",b->data); 
       if(b->lchild != NULL || b->rchild != NULL)
       {
            printf("("); 
            if(b->lchild != NULL)
                DispBTNode(b->lchild);
            if(b->rchild != NULL)
            {
                printf(","); 
                DispBTNode(b->rchild);
            }
            printf(")"); 
       }
    }
}

//查找节点
BTNode *FindNode(BTNode *b, ElemType x)
{
    BTNode *p;
    if (b == NULL)
        return NULL;
    else if (b->data == x)
        return b;
    else
    {
        p = FindNode(b->lchild, x);
        if (p != NULL)
            return p;
        else
            return FindNode(b->rchild, x);
    }
}
```
