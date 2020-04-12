#include <stdio.h>
#include <stdlib.h>
#define N  8
int col[N],md[2*N-1],sd[2*N-1];
int q[N];
int count=0;
void QueenRecursive(int i);
void QuennNotRecursive();
int main()
{
    printf("solve of %d queens problem:\n",N);
    printf("Recursive method:\n");
    QueenRecursive(0);
    printf("%d  recursive solutions in total",count);
    QuennNotRecursive();
    return 0;
}

void QueenRecursive(int i)
{

    for(int j=0;j<N;j++)
    {
        if(col[j]==0&&md[N+i-j-1]==0&&sd[j+i]==0)
        {
            col[j]=md[N+i-j-1]=sd[i+j]=1;
            q[i]=j;
            if(i==N-1)
            {   count++;
                for(int m=0;m<N;m++)
                    printf("%d",q[m]);
                printf("\n");
            }
            else
                QueenRecursive(i+1);
            col[j]=md[N+i-j-1]=sd[i+j]=0;

        }
    }
}
void QuennNotRecursive()
{
    int num=0,Row=0,Col=0;
    static int colcopy[N],mdcopy[2*N-1],sdcopy[2*N-1];
    printf("\nNot Recursive method:\n");

    while(Row<N)
    {
        while(Col<N)
        {
            if(colcopy[Col]==0&&mdcopy[N+Row-Col-1]==0&&sdcopy[Row+Col]==0)
            {
                colcopy[Col]=mdcopy[N+Row-Col-1]=sdcopy[Row+Col]=1;
                q[Row]=Col;
                if(Row == N-1)
                {
                    num++;
                    for(int m=0;m<N;m++)
                        printf("%d",q[m]);
                    printf("\n");
                    colcopy[Col]=mdcopy[N+Row-Col-1]=sdcopy[Row+Col]=0;
                    Col++;

                }
                else
                {
                    Col=0;
                    break;
                }
            }
            else
            {
                Col++;
            }
        }
        if(Col==N)
        {
            Row--;
            if(Row<0)
                {
                    printf("%d  not recursive solutions in total\n",num);
                    return;
                }
            else
            {
                Col=q[Row];
                colcopy[Col]=mdcopy[N+Row-Col-1]=sdcopy[Row+Col]=0;
                Col++;
                continue;
            }
        }
        Row++;
    }

}
