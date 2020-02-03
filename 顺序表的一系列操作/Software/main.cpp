#include"SeqList.h"
using namespace std;

int main()
{   //建立两个SeqList对象test1，test2，test3用来测试，顺序表初始长度为方便测试定为5
    SeqList test1,test2,test3;
    //removelement 存放测试时被删除的元素
    int A[7],B[3],removelement;
    //average 存放平均数
    float average;
    //初始化顺序表，输入数据为A数组：1,3,5,7,9,11,13  B数组：2,4,6
    initList(test1);
    initList(test2);
    initList(test3);
    printf("请输入七个数字构建A数组\n");
    for(int i=0;i<7;i++)
        scanf("%d",&A[i]);
    printf("请输入三个数字构建B数组\n");
    for(int i=0;i<3;i++)
        scanf("%d",&B[i]);
    //通过数组创建顺序表，分为两种情况：数组长度分别为大于顺序表初始长度 A[7]，小于顺序表初始长度B[3]
    createList(test1,A,7);
    createList(test2,B,3);

    //测试判断表空、表满、求表长函数
    isEmpty(test1);
    isFull(test2);
    Length(test1);

    //测试查找、定位函数
    Search(test1,3);
    Locate(test2,5);

    //测试插入、删除函数，在test1 3位置插入元素4 ，在test2 4位置插入元素8，在test2 2位置删除元素4
    Insert(test1,3,4);
    Insert(test2,4,8);
    Remove(test2,2,removelement);
    printList(test1);
    printList(test2);

    //测试扩充、复制函数,扩充test2 至7长度，把test1复制到test3；
    extend(test2);
    Length(test2);

    copylist(test1,test3);
    extend(test3);//扩充test3至10以便复制
    copylist(test1,test3);
    printList(test3);

    //求平均值
    printList(test1);
    average=sum(test1)/test1.nowsize;
    printf("顺序表和为%d\n",sum(test1));
    printf("顺序表平均值为%f\n",average);
    return 0;
}
