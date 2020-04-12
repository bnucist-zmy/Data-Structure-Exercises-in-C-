#include <iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef struct basic_node  //基础数据结点
{
    string major_pollutant;
    int pollutant_index;
    string pollutant_level;
    string air_condition;
    int year;
    int month;
    int day;
}BASIC_node;
typedef struct city_node     //城市结点
{
    string city_identifier;
    string city_name;
    int data_number;
    basic_node data[365];
}CITY_node;
typedef struct city_list     //城市列表
{
    int city_num;
    city_node* my_city_list;

}CITY_LIST;
typedef struct average_air_condition_node   //平均污染指数结点
{
    string cityname;
    float average_pollution_index;
}Air_condition_node;
bool cmp(const average_air_condition_node& a,const average_air_condition_node& b)   //作为sort回调函数参数的cmp
{
    return a.average_pollution_index<b.average_pollution_index;
}
ostream& operator<<(ostream& out,const basic_node& node)    //重载运算符<<
{
    out<<node.major_pollutant<<"  "<<node.pollutant_index<<"  "<<node.pollutant_level<<" "<<node.air_condition<<" "<<node.year<<"-"<<node.month<<"-"<<node.day<<endl;
    return out;
}

void create_city_list(CITY_LIST& mylist,string filepath)   //读数据创建城市列表
{
    ifstream myfile(filepath);

    if(myfile.fail())
    {
        cout<<"Error opening file";
        exit(1);
    }
    mylist.my_city_list=new city_node[100];
    string temp_city_identifier;
    string temp_city_name;
    string temp_major_pollutant;
    int temp_pollutant_index;
    string temp_pollutant_level;
    string temp_air_conditon;
    int temp_year,temp_month,temp_day;
    int i=0,data_count=0;
    myfile>>temp_city_identifier>>temp_city_name>>temp_major_pollutant>>temp_pollutant_index
    >>temp_pollutant_level>>temp_air_conditon>>temp_year>>temp_month>>temp_day;
    mylist.city_num=1;
    mylist.my_city_list[i].city_identifier=temp_city_identifier;
    mylist.my_city_list[i].city_name=temp_city_name;
    mylist.my_city_list[i].data[data_count].major_pollutant=temp_major_pollutant;
    mylist.my_city_list[i].data[data_count].pollutant_index=temp_pollutant_index;
    mylist.my_city_list[i].data[data_count].pollutant_level=temp_pollutant_level;
    mylist.my_city_list[i].data[data_count].air_condition=temp_air_conditon;
    mylist.my_city_list[i].data[data_count].year=temp_year;
    mylist.my_city_list[i].data[data_count].month=temp_month;
    mylist.my_city_list[i].data[data_count].day=temp_day;
    mylist.my_city_list[i].data_number++;
    data_count++;
    while(!myfile.eof())
    {
        myfile>>temp_city_identifier>>temp_city_name>>temp_major_pollutant>>temp_pollutant_index
        >>temp_pollutant_level>>temp_air_conditon>>temp_year>>temp_month>>temp_day;
        if(temp_city_identifier==mylist.my_city_list[i].city_identifier)
        {
            mylist.my_city_list[i].data[data_count].major_pollutant=temp_major_pollutant;
            mylist.my_city_list[i].data[data_count].pollutant_index=temp_pollutant_index;
            mylist.my_city_list[i].data[data_count].pollutant_level=temp_pollutant_level;
            mylist.my_city_list[i].data[data_count].air_condition=temp_air_conditon;
            mylist.my_city_list[i].data[data_count].year=temp_year;
            mylist.my_city_list[i].data[data_count].month=temp_month;
            mylist.my_city_list[i].data[data_count].day=temp_day;
            mylist.my_city_list[i].data_number++;
            data_count++;

        }
        else
        {
            mylist.city_num++;
            i++;
            mylist.my_city_list[i].city_identifier=temp_city_identifier;
            mylist.my_city_list[i].city_name=temp_city_name;
            data_count=0;
            mylist.my_city_list[i].data[data_count].major_pollutant=temp_major_pollutant;
            mylist.my_city_list[i].data[data_count].pollutant_index=temp_pollutant_index;
            mylist.my_city_list[i].data[data_count].pollutant_level=temp_pollutant_level;
            mylist.my_city_list[i].data[data_count].air_condition=temp_air_conditon;
            mylist.my_city_list[i].data[data_count].year=temp_year;
            mylist.my_city_list[i].data[data_count].month=temp_month;
            mylist.my_city_list[i].data[data_count].day=temp_day;
            mylist.my_city_list[i].data_number++;
            data_count++;
        }
    }
}
void common_query(CITY_LIST& mylist)    //普通查询
{
    string city_name;
    string city_identifier;
    int choice,temp_index1,temp_index2;
    int target_city_number;
    cout<<"请输入城市名称和城市代码:"<<endl;
    cin>>city_name>>city_identifier;
    for(int i=0;i<mylist.city_num;i++)
        if(mylist.my_city_list[i].city_name==city_name)
            {target_city_number=i;break;}
    cout<<"请输入数字来选择功能：1.查询某天 2.查询某周 3.查询某月 4.查询某季度 5.查询全年 "<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        cout<<"请输入要查询第几天的空气质量状况：";
        int day;
        cin>>day;
        temp_index1=mylist.my_city_list[target_city_number].data_number-day;
        cout<<"2006年"<<city_name<<"市第"<<day<<"天空气质量状况为："<<endl;
        cout<<mylist.my_city_list[target_city_number].city_identifier<<"  "<<mylist.my_city_list[target_city_number].city_name<<" ";
        cout<<mylist.my_city_list[target_city_number].data[temp_index1];
        break;
    case 2:
        cout<<"请输入要查询第几周的空气质量状况：";
        int week;
        cin>>week;
        temp_index2=mylist.my_city_list[target_city_number].data_number-(week-1)*7-1;
        cout<<"2006年"<<city_name<<"市第"<<week<<"周空气质量状况为："<<endl;
        for(int i=temp_index2;i>temp_index2-7;i--)
        {
            cout<<mylist.my_city_list[target_city_number].city_identifier<<"  "<<mylist.my_city_list[target_city_number].city_name<<" ";
            cout<<mylist.my_city_list[target_city_number].data[i];
        }
        break;
    case 3:
        cout<<"请输入要查询第几个月的空气质量状况：";
        int month;
        cin>>month;
        cout<<"2006年"<<city_name<<"市第"<<month<<"月空气质量状况为："<<endl;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if(mylist.my_city_list[target_city_number].data[i].month==month)
               cout<<mylist.my_city_list[target_city_number].data[i];
        break;
    case 4:
        {cout<<"请输入要查询第几季度的空气质量状况：";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        cout<<"2006年"<<city_name<<"市第"<<season<<"季度空气质量状况为："<<endl;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if((mylist.my_city_list[target_city_number].data[i].month-start_month<=2)&&(mylist.my_city_list[target_city_number].data[i].month>=start_month))
                cout<<mylist.my_city_list[target_city_number].data[i];
        break;}
    case 5:
        cout<<"2006年"<<city_name<<"市空气质量状况为："<<endl;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            cout<<mylist.my_city_list[target_city_number].data[i];
        break;
    }
}
void statistical_queryA(CITY_LIST& mylist)    //统计查询A
{
    string city_name;
    string city_identifier;
    string target_air_condition;
    int choiceA,choiceB,temp_index,day_count=0;
    int target_city_number;
    cout<<"请输入城市名称和城市代码:"<<endl;
    cin>>city_name>>city_identifier;
    for(int i=0;i<mylist.city_num;i++)
        if(mylist.my_city_list[i].city_name==city_name)
            {target_city_number=i;break;}
    cout<<"请输入数字来选择功能：1.查询某周 2.查询某月 3.查询某季度 4.查询全年 "<<endl;
    cin>>choiceA;
    cout<<"请输入数字来选择要查询的空气状况：1.优 2.良 3.轻微污染 4.轻度污染 5.重污染："<<endl;
    cin>>choiceB;
    switch(choiceB)
    {
    case 1:
        target_air_condition="优";
        break;
    case 2:
        target_air_condition="良";
        break;
    case 3:
        target_air_condition="轻微污染";
        break;
    case 4:
        target_air_condition="轻度污染";
        break;
    case 5:
        target_air_condition="重污染";
        break;
    }
    switch(choiceA)
    {
    case 1:
        cout<<"请输入要查询第几周的空气质量状况：";
        int week;
        cin>>week;
        temp_index=mylist.my_city_list[target_city_number].data_number-(week-1)*7-1;
        for(int i=temp_index;i>temp_index-7;i--)
        {
            if(mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
                day_count++;
        }
        cout<<"2006年"<<city_name<<"市第"<<week<<"周空气质量状况为"<<target_air_condition<<"的天数为"<<day_count<<"天"<<endl;
        break;
    case 2:
        cout<<"请输入要查询第几个月的空气质量状况：";
        int month;
        cin>>month;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if(mylist.my_city_list[target_city_number].data[i].month==month&&mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
                day_count++;
        cout<<"2006年"<<city_name<<"市第"<<month<<"月空气质量状况为"<<target_air_condition<<"的天数为"<<day_count<<"天"<<endl;
        break;
    case 3:
        {
        cout<<"请输入要查询第几季度的空气质量状况：";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if((mylist.my_city_list[target_city_number].data[i].month-start_month<=2)&&(mylist.my_city_list[target_city_number].data[i].month>=start_month)&&mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
                day_count++;
        cout<<"2006年"<<city_name<<"市第"<<season<<"季度空气质量状况为"<<target_air_condition<<"的天数为"<<day_count<<"天"<<endl;
        break;
        }
    case 4:
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if(mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
               day_count++;
        cout<<"2006年"<<city_name<<"市空气质量状况为"<<target_air_condition<<"的天数为"<<day_count<<"天"<<endl;
        break;
    }
}
void statistical_queryB(CITY_LIST& mylist)    //统计查询B
{
    int choiceA,choiceB,target_day_num,temp_index;
    string target_air_condition;
    cout<<"请输入数字来选择功能：1.查询某周 2.查询某月 3.查询某季度 4.查询全年 "<<endl;
    cin>>choiceA;
    cout<<"请输入数字来选择要查询的空气状况：1.优 2.良 3.轻微污染 4.轻度污染 5.重污染："<<endl;
    cin>>choiceB;
    switch(choiceB)
    {
    case 1:
        target_air_condition="优";
        break;
    case 2:
        target_air_condition="良";
        break;
    case 3:
        target_air_condition="轻微污染";
        break;
    case 4:
        target_air_condition="轻度污染";
        break;
    case 5:
        target_air_condition="重污染";
        break;
    }
    cout<<"请输入x，查询空气质量为"<<target_air_condition<<"x天以上的城市"<<endl;
    cin>>target_day_num;
    switch(choiceA)
    {
    case 1:
        cout<<"请输入要查询第几周的空气质量状况：";
        int week;
        cin>>week;
        cout<<"2006年第"<<week<<"周空气质量为"<<target_air_condition<<"达"<<target_day_num<<"天以上的城市有："<<endl;

        for(int i=0;i<mylist.city_num;i++)
        {
            temp_index=mylist.my_city_list[i].data_number-(week-1)*7-1;
            int day_count=0;
            for(int j=temp_index;j>temp_index-7;j--)
            {
                if(mylist.my_city_list[i].data[j].air_condition==target_air_condition)
                    day_count++;
            }
            if(day_count>target_day_num)
                cout<<mylist.my_city_list[i].city_name<<endl;
        }
        break;
    case 2:
        cout<<"请输入要查询第几个月的空气质量状况：";
        int month;
        cin>>month;
        cout<<"2006年第"<<month<<"月空气质量为"<<target_air_condition<<"达"<<target_day_num<<"天以上的城市有："<<endl;
        for(int i=0;i<mylist.city_num;i++)
        {
            int day_count=0;
            for(int j=mylist.my_city_list[i].data_number-1;j>=0;j--)
            {
                if(mylist.my_city_list[i].data[j].air_condition==target_air_condition&&mylist.my_city_list[i].data[j].month==month)
                    day_count++;
            }
            if(day_count>target_day_num)
                cout<<mylist.my_city_list[i].city_name<<endl;
        }
        break;
    case 3:
        {
        cout<<"请输入要查询第几季度的空气质量状况：";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        cout<<"2006年第"<<season<<"季度空气质量为"<<target_air_condition<<"达"<<target_day_num<<"天以上的城市有："<<endl;
        for(int i=0;i<mylist.city_num;i++)
        {
            int day_count=0;
            for(int j=mylist.my_city_list[i].data_number-1;j>=0;j--)
            {
                if(mylist.my_city_list[i].data[j].air_condition==target_air_condition&&mylist.my_city_list[i].data[j].month>=start_month&&(mylist.my_city_list[i].data[j].month-start_month<=2))
                    day_count++;
            }
            if(day_count>target_day_num)
                cout<<mylist.my_city_list[i].city_name<<endl;
        }
        break;
        }
    case 4:
        cout<<"2006年空气质量为"<<target_air_condition<<"达"<<target_day_num<<"天以上的城市有："<<endl;
        for(int i=0;i<mylist.city_num;i++)
        {
            int day_count=0;
             for(int j=mylist.my_city_list[i].data_number-1;j>=0;j--)
             {
                 if(mylist.my_city_list[i].data[j].air_condition==target_air_condition)
                    day_count++;
             }
             if(day_count>target_day_num)
                cout<<mylist.my_city_list[i].city_name<<endl;
        }
        break;
    }
}
void sort_query(CITY_LIST& mylist)   //排序查询
{
    int choiceA,topnum,temp_index;
    Air_condition_node myarray[mylist.city_num];
    cout<<"请输入数字来选择功能：1.查询某周 2.查询某月 3.查询某季度 4.查询全年 "<<endl;
    cin>>choiceA;
    cout<<"请输入x，查看平均空气质量排前x名的城市："<<endl;
    cin>>topnum;
    switch(choiceA)
    {
    case 1:
        cout<<"请输入要查询第几周的空气质量状况：";
        int week;
        cin>>week;
        for(int i=0;i<mylist.city_num;i++)
        {
            temp_index=mylist.my_city_list[i].data_number-(week-1)*7-1;
            float total_pollution_index=0;
            for(int j=temp_index;j>temp_index-7;j--)
            {
                total_pollution_index+=mylist.my_city_list[i].data[j].pollutant_index;
            }
            myarray[i].cityname=mylist.my_city_list[i].city_name;
            myarray[i].average_pollution_index=total_pollution_index/7;
        }
        sort(myarray,myarray+mylist.city_num,cmp);
        cout<<"2006年第"<<week<<"周平均空气质量前"<<topnum<<"的城市是:"<<endl;
        for(int i=0;i<topnum;i++)
        {
            cout<<"No."<<i+1<<" "<<myarray[i].cityname<<endl;
        }
        break;
    case 2:
        cout<<"请输入要查询第几个月的空气质量状况：";
        int month;
        cin>>month;
        for(int i=0;i<mylist.city_num;i++)
        {
            float total_pollution_index=0;
            int denominator=0;
            for(int j=mylist.my_city_list[i].data_number-1;j>=0;j--)
            {
                if(mylist.my_city_list[i].data[j].month==month)
                    {
                        total_pollution_index+=mylist.my_city_list[i].data[j].pollutant_index;
                        denominator++;
                    }
            }
            myarray[i].cityname=mylist.my_city_list[i].city_name;
            myarray[i].average_pollution_index=total_pollution_index/denominator;
        }
        sort(myarray,myarray+mylist.city_num,cmp);
        cout<<"2006年第"<<month<<"月平均空气质量前"<<topnum<<"的城市是:"<<endl;
        for(int i=0;i<topnum;i++)
        {
            cout<<"No."<<i+1<<" "<<myarray[i].cityname<<endl;
        }
        break;
    case 3:
        {
        cout<<"请输入要查询第几季度的空气质量状况：";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        for(int i=0;i<mylist.city_num;i++)
        {
            float total_pollution_index=0;
            int denominator=0;
            for(int j=mylist.my_city_list[i].data_number-1;j>=0;j--)
            {
                if(mylist.my_city_list[i].data[j].month>=start_month&&(mylist.my_city_list[i].data[j].month-start_month<=2))
                    {
                        total_pollution_index+=mylist.my_city_list[i].data[j].pollutant_index;
                        denominator++;
                    }
            }
            myarray[i].cityname=mylist.my_city_list[i].city_name;
            myarray[i].average_pollution_index=total_pollution_index/denominator;
        }
        sort(myarray,myarray+mylist.city_num,cmp);
        cout<<"2006年第"<<season<<"季度平均空气质量前"<<topnum<<"的城市是:"<<endl;
        for(int i=0;i<topnum;i++)
        {
            cout<<"No."<<i+1<<" "<<myarray[i].cityname<<endl;
        }
        break;
        }
    case 4:
        for(int i=0;i<mylist.city_num;i++)
        {
             float total_pollution_index=0;
             for(int j=mylist.my_city_list[i].data_number-1;j>=0;j--)
             {
                 total_pollution_index+=mylist.my_city_list[i].data[j].pollutant_index;
             }
            myarray[i].cityname=mylist.my_city_list[i].city_name;
            myarray[i].average_pollution_index=total_pollution_index/mylist.my_city_list[i].data_number;
        }
        sort(myarray,myarray+mylist.city_num,cmp);
        cout<<"2006年平均空气质量前"<<topnum<<"的城市是:"<<endl;
        for(int i=0;i<topnum;i++)
        {
            cout<<"No."<<i+1<<" "<<myarray[i].cityname<<endl;
        }
        break;
    }

}
int main()
{
    CITY_LIST mylist;
    create_city_list(mylist,"data.txt");
    int choice;
    while(1)
    {
        cout<<"请输入数字选择功能:"<<endl;
        cout<<"1.普通查询：输入城市名称和城市代码，分别查询该城市每天、每周、每月、每季度和全年的空气质量状况"<<endl;
        cout<<"2.统计查询A：输入城市名称和城市代码，分别查询该城市每周、每月、每季度和全年的空气质量为优、良、轻微污染、轻度污染、重污染的天数"<<endl;
        cout<<"3.统计查询B：根据时间查询空气质量状况：输入周编号、月编号、季度编号或年编号，以及空气质量为优、良、轻微污染、轻度污染、重污染的天数，查找相应的城市名称"<<endl;
        cout<<"4.排序查询：输入周编号、月编号、季度编号或年编号，查询城市空气质量的排行榜"<<endl;
        cout<<"5.退出"<<endl;
        cout<<"请输入选择："<<endl;
        cin>>choice;
        switch(choice)
        {
        case 1:
            common_query(mylist);
            break;
        case 2:
            statistical_queryA(mylist);
            break;
        case 3:
            statistical_queryB(mylist);
            break;
        case 4:
            sort_query(mylist);
            break;
        case 5:
            return 0;
        }
        cout<<endl;
    }
    return 0;
}
