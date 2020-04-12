#include <iostream>
#include<stdio.h>
#include<string>
#define maxVertices 10
#define maxEdges 30
#define maxWeight 20000
using namespace std;
typedef string Type;
typedef int Weight;
typedef struct
{
    int numVertices,numEdges;
    Type VerticesList[maxVertices];
    Weight Edge[maxVertices][maxVertices];
}MGraph;
typedef struct           //时间节点定义
{
    int start_time,arrive_time,able_flag;
}time_node;
typedef struct            //时间矩阵定义
{
    int numVertices,numEdges;
    Type VerticesList[maxVertices];
    time_node time_pairs[maxVertices][maxVertices];
}Time_lists;
int GetTimeVertexPos(Time_lists&T,Type x)   //通过x的值找到时间矩阵中x的下标
{
    for(int i=0;i<T.numVertices;i++)
    {
        if(T.VerticesList[i]==x) return i;
    }
    return -1;
}
void createTime_lists(Time_lists& T,Type v[],int verticenum,Type ed[][2],int time_schedule[][2],int edgenum)   //创建时间矩阵
{
    T.numVertices=verticenum;
    T.numEdges=edgenum;
    int i,j,k;
    for(i=0;i<T.numVertices;i++)
    {
        T.VerticesList[i]=v[i];
        for(j=0;j<T.numVertices;j++)
            T.time_pairs[i][j].able_flag=0;
    }
    for(k=0;k<T.numEdges;k++)
    {
        i= GetTimeVertexPos(T,ed[k][0]);
        j= GetTimeVertexPos(T,ed[k][1]);
        T.time_pairs[i][j].start_time=time_schedule[k][0];
        T.time_pairs[i][j].arrive_time=time_schedule[k][1];
        T.time_pairs[i][j].able_flag=1;
    }
}
int GetVertexPos(MGraph& G,Type x)
{
    for(int i=0;i<G.numVertices;i++)
        if(G.VerticesList[i]==x) return i;
    return -1;
}
int numberOfVertices(MGraph& G)
{
    return G.numVertices;
}
void createMGraph(MGraph& G,Type v[],int verticenum,Type ed[][2],Weight c[],int edgenum)
{

    G.numVertices=verticenum;
    G.numEdges=edgenum;
    int i,j,k;
    for(i=0;i<G.numVertices;i++)
    {
        G.VerticesList[i]=v[i];
        for(j=0;j<G.numVertices;j++)
            G.Edge[i][j]=(i==j)?0:maxWeight;
    }
    for(k=0;k<G.numEdges;k++)
    {
        i= GetVertexPos(G,ed[k][0]);
        j= GetVertexPos(G,ed[k][1]);
        G.Edge[i][j]=c[k];
    }
}
void Shortest_Total_Time_Path(MGraph& G,Type start_city,Weight dist[],int path[],Time_lists& T)    //总时间最短的Dijkstra算法
{
    int source_index=GetVertexPos(G,start_city);
    int n=G.numVertices;int already_find[maxVertices];
    int i,j,k;
    Weight w,min_weight;
    for(i=0;i<n;i++)
    {
        dist[i]=G.Edge[source_index][i];
        already_find[i]=0;
        if(i!=source_index&&dist[i]<maxWeight) path[i]=source_index;
        else path[i]=-1;
    }
    already_find[source_index]=1;
    dist[source_index]=0;
    for(i=0;i<n-1;i++)
    {
        min_weight=maxWeight;
        int temp_index=source_index;
        for(j=0;j<n;j++)
           if(!already_find[j]&&dist[j]<min_weight) {temp_index=j;min_weight=dist[j];}
        already_find[temp_index]=1;
        int last_index=path[temp_index];
        for(k=0;k<n;k++)
        {
            int internal_time=0;
            if(T.time_pairs[temp_index][k].able_flag==1)
                {   if(T.time_pairs[temp_index][k].start_time<T.time_pairs[last_index][temp_index].arrive_time)
                        internal_time=T.time_pairs[temp_index][k].start_time+24*60-T.time_pairs[last_index][temp_index].arrive_time;
                    else
                        internal_time=T.time_pairs[temp_index][k].start_time-T.time_pairs[last_index][temp_index].arrive_time;
                }
            w=G.Edge[temp_index][k]+internal_time;
            if(!already_find[k]&&w<maxWeight&&dist[temp_index]+w<dist[k])
            {
                dist[k]=dist[temp_index]+w;
                path[k]=temp_index;
            }
        }
    }

}
void ShortestPath(MGraph& G,Type start_city,Weight dist[],int path[])    //普通的Dijkstra算法
{
    int source_index=GetVertexPos(G,start_city);
    int n=G.numVertices;int already_find[maxVertices];
    int i,j,k;
    Weight w,min_weight;
    for(i=0;i<n;i++)
    {
        dist[i]=G.Edge[source_index][i];
        already_find[i]=0;
        if(i!=source_index&&dist[i]<maxWeight) path[i]=source_index;
        else path[i]=-1;
    }
    already_find[source_index]=1;
    dist[source_index]=0;
    for(i=0;i<n-1;i++)
    {
        min_weight=maxWeight;
        int temp_index=source_index;
        for(j=0;j<n;j++)
           if(!already_find[j]&&dist[j]<min_weight) {temp_index=j;min_weight=dist[j];}
        already_find[temp_index]=1;
        for(k=0;k<n;k++)
        {
            w=G.Edge[temp_index][k];
            if(!already_find[k]&&w<maxWeight&&dist[temp_index]+w<dist[k])
            {
                dist[k]=dist[temp_index]+w;
                path[k]=temp_index;
            }
        }
    }

}
void print_least_flight_time_Path(MGraph& G,Type start_city, Weight dist[],int path[])   //输出飞行时间最少的路径
{
    int v=GetVertexPos(G,start_city);
    cout<<"从"<<G.VerticesList[v]<<"到其他城市飞行时间最短的最优航线为："<<endl;
    int i,j,k,n=numberOfVertices(G);
    int d[maxVertices];
    for(i=0;i<n;i++)
    {
        if(i!=v)
        {
            j=i; k=0;
            while(j!=v) {d[k++]=j; j=path[j];}
            d[k++]=v;
            cout<<"到"<<G.VerticesList[i]<<"的最优航线为:";
            while(k>0) cout<<G.VerticesList[d[--k]]<<" ";
            cout<<"     最短飞行时间为:"<<dist[i]<<"分钟"<<endl;
        }
    }
}


void print_least_flight_cost_Path(MGraph& G,Type start_city,Weight dist[],int path[])   //输出飞行费用最少的路径
{
    int v=GetVertexPos(G,start_city);
    cout<<"从"<<G.VerticesList[v]<<"到其他城市飞行费用最少的最优航线为:"<<endl;
    int temp_index,k;
    int n=numberOfVertices(G);
    int output_path[maxVertices];
    for(int i=0;i<n;i++)
    {
        if(i!=v)
        {
            temp_index=i;k=0;
            while(temp_index!=v) {output_path[k++]=temp_index; temp_index=path[temp_index];}
            output_path[k++]=v;
            cout<<"到"<<G.VerticesList[i]<<"的最优航线为:";
            while(k>0) cout<<G.VerticesList[output_path[--k]]<<" ";
            cout<<"    最少费用为："<<dist[i]<<endl;

        }
    }
}
void print_least_transfer_flights_Path(MGraph& G,Type start_city,Weight dist[],int path[])   //输出转机次数最少的路径
{
    int v=GetVertexPos(G,start_city);
    int n=numberOfVertices(G);
    int output_path[maxVertices];
    cout<<"从"<<G.VerticesList[v]<<"到其他城市转机次数最少的最优航线为："<<endl;
    for(int i=0;i<n;i++)
    {
        if(i!=v)
        {
            int temp_index=i; int k=0;
            while(temp_index!=v) {output_path[k++]=temp_index; temp_index=path[temp_index];}
            output_path[k++]=v;
            cout<<"到"<<G.VerticesList[i]<<"的最优航线为：";
            while(k>0) cout<<G.VerticesList[output_path[--k]]<<" ";
            cout<<"    最少转机次数为："<<dist[i]-1<<endl;
        }
    }
}

void print_least_total_flight_time_Path(MGraph& G,Type start_city, Weight dist[],int path[])   //输出总时间最少的路径
{
    int v=GetVertexPos(G,start_city);
    cout<<"从"<<G.VerticesList[v]<<"到其他城市总时间最短的最优航线为："<<endl;
    int i,j,k,n=numberOfVertices(G);
    int d[maxVertices];
    for(i=0;i<n;i++)
    {
        if(i!=v)
        {
            j=i; k=0;
            while(j!=v) {d[k++]=j; j=path[j];}
            d[k++]=v;
            cout<<"到"<<G.VerticesList[i]<<"的最优航线为:";
            while(k>0) cout<<G.VerticesList[d[--k]]<<" ";
            int hour=dist[i]/60;
            int minute=dist[i]%60;
            cout<<"   最短时间为:"<<hour<<"小时"<<minute<<"分钟="<<dist[i]<<"分钟"<<endl;
        }
    }
}

int main()
{

    //initialize basic information arrays  基本信息数组的初始化
    Type cities[8]={"北京","上海","乌鲁木齐","西安","广州","昆明","拉萨","武汉"};
    Type flight_routes[16][2]={{"北京","上海"},{"上海","北京"},{"北京","乌鲁木齐"},{"乌鲁木齐","北京"},{"北京","西安"},{"西安","北京"},{"西安","广州"},{"广州","西安"},{"拉萨","昆明"},{"昆明","拉萨"},{"拉萨","武汉"},{"武汉","拉萨"},{"乌鲁木齐","昆明"},{"昆明","乌鲁木齐"},{"武汉","广州"},{"广州","武汉"}};
    Weight flight_time[16]={65,65,115,55,95,100,140,80,85,85,90,90,165,165,100,100};
    Weight flight_cost[16]={680,680,1150,1150,930,930,1320,1320,830,830,890,890,1480,1480,810,810};
    Weight transfer_flight[16];
    Weight time_schedules[16][2]={{980,1015},{1080,1145},{480,595},{645,700},{925,1020},{755,855},{435,575},{615,695},{620,705},{755,840},{855,945},{985,1075},{570,735},{785,950},{425,525},{685,785}};
    for(int i=0;i<16;i++)
        transfer_flight[i]=1;
    //different dist arrays and path arrays  不同的dist和path数组
    Weight flight_time_dist[8];
    Weight flight_cost_dist[8];
    Weight transfer_flight_dist[8];
    Weight total_time_dist[8];

    int flight_time_path[8];
    int flight_cost_path[8];
    int transfer_flight_path[8];
    int total_time_path[8];
    //different Graphs  不同的图
    MGraph flight_time_graph;
    MGraph flight_cost_graph;
    MGraph transfer_flight_graph;
    Time_lists internal_times;

    createTime_lists(internal_times,cities,8,flight_routes,time_schedules,16);
    createMGraph(flight_time_graph,cities,8,flight_routes,flight_time,16);
    createMGraph(flight_cost_graph,cities,8,flight_routes,flight_cost,16);
    createMGraph(transfer_flight_graph,cities,8,flight_routes,transfer_flight,16);

    char whether_to_leave='N';

    while(whether_to_leave=='N')
    {
        string start_city;
        int choice;
        cout<<"请输入起始城市：";
        cin>>start_city;
        cout<<"请选择功能：1.最短飞行时间 2.最少飞行费用 3.最少转机次数 4.总时间最少 ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                ShortestPath(flight_time_graph,start_city,flight_time_dist,flight_time_path);
                print_least_flight_time_Path(flight_time_graph,start_city,flight_time_dist,flight_time_path);
                break;
            case 2:
                ShortestPath(flight_cost_graph,start_city,flight_cost_dist,flight_cost_path);
                print_least_flight_cost_Path(flight_cost_graph,start_city,flight_cost_dist,flight_cost_path);
                break;
            case 3:
                ShortestPath(transfer_flight_graph,start_city,transfer_flight_dist,transfer_flight_path);
                print_least_transfer_flights_Path(transfer_flight_graph,start_city,transfer_flight_dist,transfer_flight_path);
                break;
            case 4:
                Shortest_Total_Time_Path(flight_time_graph,start_city,total_time_dist,total_time_path,internal_times);
                print_least_total_flight_time_Path(flight_time_graph,start_city,total_time_dist,total_time_path);
                break;

        }
        cout<<"是否离开程序？（Y/N）";
        cin>>whether_to_leave;

    }
    return 0;
}
