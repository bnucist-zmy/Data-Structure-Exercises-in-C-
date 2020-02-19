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
    //���Բ��Һ�������A���ϲ���Ԫ��3
    testnode=Contains(A,3);
    printf("���ҵ�Ԫ��Ϊ%d\n",testnode->data);
    //���Բ��뺯��,��B���ϲ���Ԫ��6
    addMember(B,6);
    //����ɾ������
    delMember(A,3);
    //���Խ������������
    Merge(A,B,C);
    Intersection(A,B,D);
    Complement(A,B,E);
    printf("����Ϊ��\n");
    printSet(D);
    printf("����Ϊ��\n");
    printSet(C);
    printf("�Ϊ��\n");
    printSet(E);
    return 0;
}
