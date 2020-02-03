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
    if(!L.data) {printf("存储分配失败！\n"); exit(1);}
    L.maxsize = initSize;
    L.nowsize=0;
}

int Length(SeqList& L)
{
    printf("此时顺序表中已占用长度为：%d,最大长度为%d\n",L.nowsize,L.maxsize);
    return L.nowsize;
}

bool isEmpty(SeqList& L)
{
    if(L.nowsize==0)
    {
        printf("表当前为空\n");
        return true;
    }
    else
    {
        printf("此表当前非空\n");
        return false;
    }
}

bool isFull(SeqList& L)
{
    if(L.nowsize==L.maxsize)
    {
        printf("此表已满\n");
        return true;
    }
    else
    {
        printf("此表非满\n");
        return false;
    }
}

bool createList(SeqList& L, DataType A[],int n)
{
    if(n>initSize)
    {
        printf("数组长度大于顺序表初始长度，自动以数组长度创建顺序表。\n");
        L.data= (DataType*) malloc (n*sizeof(DataType));
        if(!L.data)
        {
            printf("创建失败\n");
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
            printf("创建失败\n");
            return false;
        }
        for(int i=0;i<n;i++) L.data[i]=A[i];
        L.maxsize= initSize;
        L.nowsize=n;
        printf("顺序表创建成功，最大长度为%d,已用长度为%d.\n",initSize,n);
        return true;
    }
}

int Search(SeqList& L, DataType x)
{
    for(int i=0;i<L.nowsize;i++)
    {
        if(L.data[i]==x)
        {
            printf("所查元素位于%d位置\n",i+1);
            return i+1;
        }
    }
    printf("元素未找到\n");
    return -1;
}

int Locate(SeqList& L,int i)
{
    if(i>0&&i <=L.nowsize)
    {   printf("元素位于%d\n",i-1);
        return i-1;}
    else
    {
        printf("参数i不合理，定位失败\n");
        return -1;
    }

}

bool Insert(SeqList& L,int i,DataType x)
{
    if(L.nowsize==L.maxsize)
    {
        printf("表满，无法插入，请扩充之后再进行插入操作\n");
        return false;
    }
    if(i<=0||i>L.nowsize+1)
    {
        printf("插入位置i不合理，请重新调用函数\n");
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
        printf("表空，无法删除\n");
        return false;
    }
    if(i<=0||i>L.nowsize)
    {
        printf("删除位置i不合理，请重新调用函数\n");
        return false;
    }
    x=L.data[i-1];
    printf("删除元素为%d\n",x);
    for(int j=i;j<L.nowsize;j++) L.data[j-1] = L.data[j];
    L.nowsize--;
    return true;
}

void printList(SeqList& L)
{   printf("此时顺序表中元素为：\n");
    for(int i=0;i<L.nowsize-1;i++) printf("%d, ",L.data[i]);
    printf("%d\n",L.data[L.nowsize-1]);
}

bool copylist(SeqList& L,SeqList& B)
{
    if( (B.maxsize-B.nowsize)<L.nowsize)
    {
        printf("目标顺序表空间不足，无法拷贝，请扩充空间\n");
        return false;
    }
    for(int i=0;i<L.nowsize;i++) B.data[B.nowsize+i]=L.data[i];
    B.nowsize=B.nowsize+L.nowsize;
    printf("复制完成\n");
    return true;
}

bool extend(SeqList& L)
{
    DataType *datatem;
    int n;
    printf("请输入要扩充顺序表至多少长度：\n");
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
        printf("顺序表为空\n");
        return result;
    }
    for(int i=0;i<L.nowsize;i++)
        result=result+L.data[i];
    return result;

}
