#include"SeqList.h"
using namespace std;

int main()
{   //��������SeqList����test1��test2��test3�������ԣ�˳����ʼ����Ϊ������Զ�Ϊ5
    SeqList test1,test2,test3;
    //removelement ��Ų���ʱ��ɾ����Ԫ��
    int A[7],B[3],removelement;
    //average ���ƽ����
    float average;
    //��ʼ��˳�����������ΪA���飺1,3,5,7,9,11,13  B���飺2,4,6
    initList(test1);
    initList(test2);
    initList(test3);
    printf("�������߸����ֹ���A����\n");
    for(int i=0;i<7;i++)
        scanf("%d",&A[i]);
    printf("�������������ֹ���B����\n");
    for(int i=0;i<3;i++)
        scanf("%d",&B[i]);
    //ͨ�����鴴��˳�����Ϊ������������鳤�ȷֱ�Ϊ����˳����ʼ���� A[7]��С��˳����ʼ����B[3]
    createList(test1,A,7);
    createList(test2,B,3);

    //�����жϱ�ա��������������
    isEmpty(test1);
    isFull(test2);
    Length(test1);

    //���Բ��ҡ���λ����
    Search(test1,3);
    Locate(test2,5);

    //���Բ��롢ɾ����������test1 3λ�ò���Ԫ��4 ����test2 4λ�ò���Ԫ��8����test2 2λ��ɾ��Ԫ��4
    Insert(test1,3,4);
    Insert(test2,4,8);
    Remove(test2,2,removelement);
    printList(test1);
    printList(test2);

    //�������䡢���ƺ���,����test2 ��7���ȣ���test1���Ƶ�test3��
    extend(test2);
    Length(test2);

    copylist(test1,test3);
    extend(test3);//����test3��10�Ա㸴��
    copylist(test1,test3);
    printList(test3);

    //��ƽ��ֵ
    printList(test1);
    average=sum(test1)/test1.nowsize;
    printf("˳����Ϊ%d\n",sum(test1));
    printf("˳���ƽ��ֵΪ%f\n",average);
    return 0;
}
