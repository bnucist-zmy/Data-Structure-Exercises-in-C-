#include <iostream>
#include"SeqList.h"
using namespace std;

int main()
{
    LinkedSet A,B,C,D,E;
    SetNode *testnode;
    initSet(A);
    initSet(B);
    initSet(C);
    initSet(D);
    initSet(E);
    insertRear(A);
    insertRear(B);
    //测试查找函数，在A集合查找元素3
    testnode=Contains(A,3);
    printf("查找的元素为%d\n",testnode->data);
    //测试插入函数,在B集合插入元素6
    addMember(B,6);
    //测试删除函数
    delMember(A,3);
    //测试交集，并集，差集
    Merge(A,B,C);
    Intersection(A,B,D);
    Complement(A,B,E);
    printf("交集为：\n");
    printSet(D);
    printf("并集为：\n");
    printSet(C);
    printf("差集为：\n");
    printSet(E);
    return 0;
}
