#include<stdio.h>
#include<stdlib.h>
#define initSize 5
typedef int DataType;
typedef struct {
    DataType *data;
    int maxsize,nowsize;

}SeqList;
void initList ( SeqList & L)
{
    L.data =(DataType *)malloc(initSize*sizeof(DataType));
    if(!L.data) {printf("�洢����ʧ�ܣ�\n"); exit(1);}
    L.maxsize = initSize;
    L.nowsize=0;
}

int Length(SeqList& L)
{
    printf("��ʱ˳�������ռ�ó���Ϊ��%d,��󳤶�Ϊ%d\n",L.nowsize,L.maxsize);
    return L.nowsize;
}

bool isEmpty(SeqList& L)
{
    if(L.nowsize==0)
    {
        printf("��ǰΪ��\n");
        return true;
    }
    else
    {
        printf("�˱�ǰ�ǿ�\n");
        return false;
    }
}

bool isFull(SeqList& L)
{
    if(L.nowsize==L.maxsize)
    {
        printf("�˱�����\n");
        return true;
    }
    else
    {
        printf("�˱����\n");
        return false;
    }
}

bool createList(SeqList& L, DataType A[],int n)
{
    if(n>initSize)
    {
        printf("���鳤�ȴ���˳����ʼ���ȣ��Զ������鳤�ȴ���˳���\n");
        L.data= (DataType*) malloc (n*sizeof(DataType));
        if(!L.data)
        {
            printf("����ʧ��\n");
            return false;
        }
        for(int i=0;i<n;i++) L.data[i] = A[i];
        L.maxsize=n;
        L.nowsize=n;
        return true;
    }
    else
    {
        L.data= (DataType*) malloc(initSize*sizeof(DataType));
        if(!L.data)
        {
            printf("����ʧ��\n");
            return false;
        }
        for(int i=0;i<n;i++) L.data[i]=A[i];
        L.maxsize= initSize;
        L.nowsize=n;
        printf("˳������ɹ�����󳤶�Ϊ%d,���ó���Ϊ%d.\n",initSize,n);
        return true;
    }
}

int Search(SeqList& L, DataType x)
{
    for(int i=0;i<L.nowsize;i++)
    {
        if(L.data[i]==x)
        {
            printf("����Ԫ��λ��%dλ��\n",i+1);
            return i+1;
        }
    }
    printf("Ԫ��δ�ҵ�\n");
    return -1;
}

int Locate(SeqList& L,int i)
{
    if(i>0&&i <=L.nowsize)
    {   printf("Ԫ��λ��%d\n",i-1);
        return i-1;}
    else
    {
        printf("����i��������λʧ��\n");
        return -1;
    }

}

bool Insert(SeqList& L,int i,DataType x)
{
    if(L.nowsize==L.maxsize)
    {
        printf("�������޷����룬������֮���ٽ��в������\n");
        return false;
    }
    if(i<=0||i>L.nowsize+1)
    {
        printf("����λ��i�����������µ��ú���\n");
        return false;
    }
    for(int j= L.nowsize-1;j >= i-1;j--) L.data[j+1] = L.data[j];
    L.data[i-1] = x;
    L.nowsize++;
    return true;
}

bool Remove(SeqList& L, int i, DataType x)
{
    if(L.nowsize==0)
    {
        printf("��գ��޷�ɾ��\n");
        return false;
    }
    if(i<=0||i>L.nowsize)
    {
        printf("ɾ��λ��i�����������µ��ú���\n");
        return false;
    }
    x=L.data[i-1];
    printf("ɾ��Ԫ��Ϊ%d\n",x);
    for(int j=i;j<L.nowsize;j++) L.data[j-1] = L.data[j];
    L.nowsize--;
    return true;
}

void printList(SeqList& L)
{   printf("��ʱ˳�����Ԫ��Ϊ��\n");
    for(int i=0;i<L.nowsize-1;i++) printf("%d, ",L.data[i]);
    printf("%d\n",L.data[L.nowsize-1]);
}

bool copylist(SeqList& L,SeqList& B)
{
    if( (B.maxsize-B.nowsize)<L.nowsize)
    {
        printf("Ŀ��˳���ռ䲻�㣬�޷�������������ռ�\n");
        return false;
    }
    for(int i=0;i<L.nowsize;i++) B.data[B.nowsize+i]=L.data[i];
    B.nowsize=B.nowsize+L.nowsize;
    printf("�������\n");
    return true;
}

bool extend(SeqList& L)
{
    DataType *datatem;
    int n;
    printf("������Ҫ����˳��������ٳ��ȣ�\n");
    scanf("%d",&n);
    datatem= (DataType*) malloc (n*sizeof(DataType));
    for(int i = 0;i<L.nowsize;i++) datatem[i]=L.data[i];
    L.data= (DataType*) malloc (n*sizeof(DataType));
    if(!L.data) return false;
    L.maxsize=n;
    for(int i = 0;i<L.nowsize;i++) L.data[i]=datatem[i];
}
int sum(SeqList& L)
{
    int result=0;
    if(L.nowsize==0)
    {
        printf("˳���Ϊ��\n");
        return result;
    }
    for(int i=0;i<L.nowsize;i++)
        result=result+L.data[i];
    return result;

}
