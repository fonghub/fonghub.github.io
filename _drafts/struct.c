
#define MaxSize 50

typedef int ElemType;

typedef struct
{
    ElemType date;
    int parent;
} PTree[MaxSize];


#define MaxSize 50
typedef struct node
{
    ElemType date;
    struct node *sone[MaxSize];
} TSonNode;


typedef int ElemType;
typedef struct tnode·
{
    ElemType date;      //节点的值
    struct tnode *hp;   //指向兄弟
    struct tnode *vp;   //指向孩子节点
}TSBNode;
