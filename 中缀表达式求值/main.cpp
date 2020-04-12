#include <stdio.h>
#include <stdlib.h>
#define stkSize 30

typedef struct
{
    double elem[stkSize];
    int top;
}DataStack;
typedef struct
{
    char elem[stkSize];
    int top;
}OperatorStack;

void initDataStack(DataStack& D);
void initOperatorStack(OperatorStack& O);
bool DataPush(DataStack& D,double x);
bool DataPop(DataStack& D,double& x);
bool OperatorPush(OperatorStack& O,char ch);
bool OperatorPop(OperatorStack& O,char& ch);
int isp(char op);
int icp(char op);
double calculate(char op,double x1,double x2);

int main()
{
    char expression[stkSize];
    //新建字符数组
    double x1,x2,result,finalresult;
    //x1,x2存放退栈时的两个数字
    char ch,ope,ch1;
    //ch读取字符，ope存放退栈时的操作符，ch1为当前OPTR栈栈顶操作符
    int i=0;
    DataStack OPND;
    OperatorStack OPTR;
    initDataStack(OPND);
    initOperatorStack(OPTR);
    //栈的初始化
    printf("请输入表达式（任意位数数字）,一定以#结束：");
    gets(expression);
    OperatorPush(OPTR,'#');
    //先在OPTR中压入一个#
    ch=expression[i];
    //开始求值
    while(ch!='#'||OPTR.elem[OPTR.top]!='#')
    {
        if(ch>='0'&&ch<='9')
        {   if(expression[i+1]>='0'&&expression[i+1]<='9')
            {
                double newnum=(ch-'0')*10+(expression[i+1]-'0');
                int nextposi=i+2;
                while(expression[nextposi]>='0'&&expression[nextposi]<='9')
                {
                    newnum=newnum*10+(expression[nextposi]-'0');
                    nextposi++;
                }
                DataPush(OPND,newnum);
                i=nextposi;
                ch=expression[i];
            }
            else
                {DataPush(OPND,1.0*(ch-'0'));
                ch=expression[++i];
                }
        }
        else
        {   ch1=OPTR.elem[OPTR.top];
            if(icp(ch)>isp(ch1))
            {
                OperatorPush(OPTR,ch);
                ch=expression[++i];
            }
            else if(icp(ch)<isp(ch1))
            {
                DataPop(OPND,x2);
                DataPop(OPND,x1);
                OperatorPop(OPTR,ope);
                result=calculate(ope,x1,x2);
                DataPush(OPND,result);

            }
            else if(icp(ch)==isp(ch1)&&ch==')')
            {
                OperatorPop(OPTR,ope);
                ch=expression[++i];
            }

        }
    }
    finalresult=OPND.elem[OPND.top];
    printf("\n结果是:%.2lf",finalresult);
    return 0;
}

void initDataStack(DataStack& D)
{
    D.top=-1;
}

void initOperatorStack(OperatorStack& O)
{
    O.top=-1;
}
bool DataPush(DataStack& D,double x)
{
    D.elem[++D.top]=x;
    return true;
}
bool DataPop(DataStack& D,double& x)
{
    if(D.top==-1)
    {
        printf("栈为空，无法退栈\n");
        return false;
    }
    x=D.elem[D.top--];
    return true;
}
bool OperatorPush(OperatorStack& O,char ch)
{
    O.elem[++O.top]=ch;
    return true;
}
bool OperatorPop(OperatorStack& O,char& ch)
{
    if(O.top==-1)
    {
        printf("栈为空，无法退栈\n");
        return false;
    }
    ch=O.elem[O.top--];
    return true;
}

int isp(char op)
{
    switch(op)
    {
        case '#': return 0;break;
        case '(': return 1;break;
        case '*': return 5;break;
        case '/': return 5;break;
        case '+': return 3;break;
        case '-': return 3;break;
        case ')': return 6;break;
    }
}
int icp(char op)
{
    switch(op)
    {
        case '#': return 0;break;
        case '(': return 6;break;
        case '*': return 4;break;
        case '/': return 4;break;
        case '+': return 2;break;
        case '-': return 2;break;
        case ')': return 1;break;
    }
}

double calculate(char op,double x1,double x2)
{
    switch(op)
    {
        case '+': return x1+x2;break;
        case '-': return x1-x2;break;
        case '*': return x1*x2;break;
        case '/': return x1/x2;break;
    }
}
