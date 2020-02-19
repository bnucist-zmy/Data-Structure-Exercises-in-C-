#include<stdio.h>
typedef int ElemType;
typedef struct node
{
    ElemType data;
    struct node* link;
}SetNode,*LinkedSet;
void initSet(LinkedSet& S)
{
    S =(SetNode*) malloc (sizeof(SetNode));
    S->link =NULL;
}
void insertRear(LinkedSet& S)
{
    SetNode *newNode, *last;
    ElemType val;
    int n;
    last= S;
    printf("请输入要输入的元素个数\n");
    scanf("%d",&n);
    printf("请输入%d个元素\n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&val);
        newNode =(SetNode*) malloc (sizeof(SetNode));
        newNode->data =val;
        last->link =newNode;
        last=newNode;

    }
    last->link =NULL;
    printf("集合创建完成\n");

}

SetNode *Contains(LinkedSet& S, ElemType x)
{
    SetNode *p =S->link;
    while(p!= NULL&&p->data <x) p=p->link;
    if(p!=NULL&&p->data ==x) return p;
    else
        return NULL;
}

bool addMember(LinkedSet& S,ElemType x)
{
    SetNode *p=S->link, *pr= S;
    while(p!=NULL&&p->data <x)
    {
        pr=p;
        p=p->link;
    }
    if(p!=NULL&&p->data== x)
    {
        printf("元素已存在于集合中，无法插入\n");
        return false;
    }
    SetNode *q= (SetNode*) malloc (sizeof(SetNode));
    q->data=x;
    q->link=p;
    pr->link=q;
    printf("元素插入成功\n");
    return true;
}

bool delMember(LinkedSet& S,ElemType x)
{
    SetNode *p= S->link, *pr=S;
    while(p!=NULL&&p->data<x)
    {
        pr=p;
        p=p->link;
    }
    if(p!=NULL&&p->data == x)
    {
        pr->link=p->link;
        free(p);
        printf("元素删除成功\n");
        return true;
    }
    else
    {
        printf("未查找到该元素，元素删除失败\n");
        return false;
    }
}

void Merge( LinkedSet& LA, LinkedSet& LB,LinkedSet& LC)
{
    SetNode *pa=LA->link,*pb= LB->link;
    SetNode *p,*pc = LC;
    while(pa!= NULL&&pb!= NULL)
    {
        pc->link =(SetNode*) malloc (sizeof(SetNode));
        pc= pc->link;
        if(pa->data <pb->data)
        {
            pc->data= pa->data;
            pa=pa->link;
        }
        else if(pa->link > pb->link)
        {
            pc->data=pb->data;
            pb=pb->link;
        }
        else
        {
            pc->data=pa->data;
            pa=pa->link;
            pb=pb->link;
        }
    }
    p=(pa!=NULL)? pa:pb;
    while(p!=NULL)
    {
        pc->link=(SetNode*) malloc (sizeof(SetNode));
        pc->link->data=p->data;
        pc=pc->link;
        p=p->link;
    }
    pc->link=NULL;
}

void Intersection(LinkedSet& LA,LinkedSet& LB,LinkedSet& LC)
{
    SetNode *pa=LA->link,*pb= LB->link;
    SetNode *pc= LC;
    while(pa!=NULL&&pb!=NULL)
    {
        if(pa->data < pb->data)
        {
            pa=pa->link;
        }
        else if(pa->data > pb->data)
        {
            pb=pb->link;
        }
        else
        {
            pc->link=(SetNode*) malloc (sizeof(SetNode));
            pc=pc->link;
            pc->data=pa->data;
            pa=pa->link;
            pb=pb->link;

        }
    }
    pc->link=NULL;
}

void Complement(LinkedSet& LA,LinkedSet& LB,LinkedSet& LC)
{
    SetNode *pa=LA->link,*pb= LB->link;
    SetNode *pc= LC,*pd;
    LinkedSet intersec;
    initSet(intersec);
    Intersection(LA,LB,intersec);

    while(pa!=NULL)
    {   int flag=0;
        pd=intersec->link;
        while(pd!=NULL)
        {
            if(pa->data==pd->data)
            {
                flag=1;
                break;
            }
            pd=pd->link;
        }
        if(flag==0)
        {
            pc->link=(SetNode*) malloc (sizeof(SetNode));
            pc=pc->link;
            pc->data=pa->data;
        }
        pa=pa->link;
    }
    pc->link=NULL;
}
void printSet(LinkedSet& S)
{
    SetNode *p=S->link;
    if(p==NULL) printf("集合为空\n");
    else
    {   printf("集合元素为：\n");
        while(p!=NULL)
        {
            printf("%d ",p->data);
            p=p->link;
        }
        printf("\n");
    }
}

