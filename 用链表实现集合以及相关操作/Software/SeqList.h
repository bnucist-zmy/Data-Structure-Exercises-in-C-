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
    printf("������Ҫ�����Ԫ�ظ���\n");
    scanf("%d",&n);
    printf("������%d��Ԫ��\n",n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&val);
        newNode =(SetNode*) malloc (sizeof(SetNode));
        newNode->data =val;
        last->link =newNode;
        last=newNode;

    }
    last->link =NULL;
    printf("���ϴ������\n");

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
        printf("Ԫ���Ѵ����ڼ����У��޷�����\n");
        return false;
    }
    SetNode *q= (SetNode*) malloc (sizeof(SetNode));
    q->data=x;
    q->link=p;
    pr->link=q;
    printf("Ԫ�ز���ɹ�\n");
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
        printf("Ԫ��ɾ���ɹ�\n");
        return true;
    }
    else
    {
        printf("δ���ҵ���Ԫ�أ�Ԫ��ɾ��ʧ��\n");
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
    if(p==NULL) printf("����Ϊ��\n");
    else
    {   printf("����Ԫ��Ϊ��\n");
        while(p!=NULL)
        {
            printf("%d ",p->data);
            p=p->link;
        }
        printf("\n");
    }
}

