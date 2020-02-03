#include <stdio.h>
#include <stdlib.h>

int main()
{   int n,i,j,max=0,left_segment_end,right_segment_end;
    printf("请输入要输入数字的个数：\n");
    scanf("%d",&n);
    int num[n+1], s[n+1];
    s[0]=0;
    printf("请输入n个数字：\n");
    for(i=1;i<=n;i++)
    {
        scanf("%d",&num[i]);
        s[i]=s[i-1]+num[i];
    }
    for(int i=0;i<n;i++)
        for(j=i+1;j<=n;j++)
        {
            if(max<(s[j]-s[i]))
            {
                max=s[j]-s[i];
                left_segment_end=i+1;
                right_segment_end=j;
            }
        }
        if(max==0)
        {
            printf("the max sum of the sublist is 0");
            return 0;
        }
        printf("the max sum of the sublist is %d,from %d to %d",max,left_segment_end,right_segment_end);
    return 0;
}
