#include <iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<algorithm>
using namespace std;
typedef struct basic_node  //�������ݽ��
{
    string major_pollutant;
    int pollutant_index;
    string pollutant_level;
    string air_condition;
    int year;
    int month;
    int day;
}BASIC_node;
typedef struct city_node     //���н��
{
    string city_identifier;
    string city_name;
    int data_number;
    basic_node data[365];
}CITY_node;
typedef struct city_list     //�����б�
{
    int city_num;
    city_node* my_city_list;

}CITY_LIST;
typedef struct average_air_condition_node   //ƽ����Ⱦָ�����
{
    string cityname;
    float average_pollution_index;
}Air_condition_node;
bool cmp(const average_air_condition_node& a,const average_air_condition_node& b)   //��Ϊsort�ص�����������cmp
{
    return a.average_pollution_index<b.average_pollution_index;
}
ostream& operator<<(ostream& out,const basic_node& node)    //���������<<
{
    out<<node.major_pollutant<<"  "<<node.pollutant_index<<"  "<<node.pollutant_level<<" "<<node.air_condition<<" "<<node.year<<"-"<<node.month<<"-"<<node.day<<endl;
    return out;
}

void create_city_list(CITY_LIST& mylist,string filepath)   //�����ݴ��������б�
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
void common_query(CITY_LIST& mylist)    //��ͨ��ѯ
{
    string city_name;
    string city_identifier;
    int choice,temp_index1,temp_index2;
    int target_city_number;
    cout<<"������������ƺͳ��д���:"<<endl;
    cin>>city_name>>city_identifier;
    for(int i=0;i<mylist.city_num;i++)
        if(mylist.my_city_list[i].city_name==city_name)
            {target_city_number=i;break;}
    cout<<"������������ѡ���ܣ�1.��ѯĳ�� 2.��ѯĳ�� 3.��ѯĳ�� 4.��ѯĳ���� 5.��ѯȫ�� "<<endl;
    cin>>choice;
    switch(choice)
    {
    case 1:
        cout<<"������Ҫ��ѯ�ڼ���Ŀ�������״����";
        int day;
        cin>>day;
        temp_index1=mylist.my_city_list[target_city_number].data_number-day;
        cout<<"2006��"<<city_name<<"�е�"<<day<<"���������״��Ϊ��"<<endl;
        cout<<mylist.my_city_list[target_city_number].city_identifier<<"  "<<mylist.my_city_list[target_city_number].city_name<<" ";
        cout<<mylist.my_city_list[target_city_number].data[temp_index1];
        break;
    case 2:
        cout<<"������Ҫ��ѯ�ڼ��ܵĿ�������״����";
        int week;
        cin>>week;
        temp_index2=mylist.my_city_list[target_city_number].data_number-(week-1)*7-1;
        cout<<"2006��"<<city_name<<"�е�"<<week<<"�ܿ�������״��Ϊ��"<<endl;
        for(int i=temp_index2;i>temp_index2-7;i--)
        {
            cout<<mylist.my_city_list[target_city_number].city_identifier<<"  "<<mylist.my_city_list[target_city_number].city_name<<" ";
            cout<<mylist.my_city_list[target_city_number].data[i];
        }
        break;
    case 3:
        cout<<"������Ҫ��ѯ�ڼ����µĿ�������״����";
        int month;
        cin>>month;
        cout<<"2006��"<<city_name<<"�е�"<<month<<"�¿�������״��Ϊ��"<<endl;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if(mylist.my_city_list[target_city_number].data[i].month==month)
               cout<<mylist.my_city_list[target_city_number].data[i];
        break;
    case 4:
        {cout<<"������Ҫ��ѯ�ڼ����ȵĿ�������״����";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        cout<<"2006��"<<city_name<<"�е�"<<season<<"���ȿ�������״��Ϊ��"<<endl;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if((mylist.my_city_list[target_city_number].data[i].month-start_month<=2)&&(mylist.my_city_list[target_city_number].data[i].month>=start_month))
                cout<<mylist.my_city_list[target_city_number].data[i];
        break;}
    case 5:
        cout<<"2006��"<<city_name<<"�п�������״��Ϊ��"<<endl;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            cout<<mylist.my_city_list[target_city_number].data[i];
        break;
    }
}
void statistical_queryA(CITY_LIST& mylist)    //ͳ�Ʋ�ѯA
{
    string city_name;
    string city_identifier;
    string target_air_condition;
    int choiceA,choiceB,temp_index,day_count=0;
    int target_city_number;
    cout<<"������������ƺͳ��д���:"<<endl;
    cin>>city_name>>city_identifier;
    for(int i=0;i<mylist.city_num;i++)
        if(mylist.my_city_list[i].city_name==city_name)
            {target_city_number=i;break;}
    cout<<"������������ѡ���ܣ�1.��ѯĳ�� 2.��ѯĳ�� 3.��ѯĳ���� 4.��ѯȫ�� "<<endl;
    cin>>choiceA;
    cout<<"������������ѡ��Ҫ��ѯ�Ŀ���״����1.�� 2.�� 3.��΢��Ⱦ 4.�����Ⱦ 5.����Ⱦ��"<<endl;
    cin>>choiceB;
    switch(choiceB)
    {
    case 1:
        target_air_condition="��";
        break;
    case 2:
        target_air_condition="��";
        break;
    case 3:
        target_air_condition="��΢��Ⱦ";
        break;
    case 4:
        target_air_condition="�����Ⱦ";
        break;
    case 5:
        target_air_condition="����Ⱦ";
        break;
    }
    switch(choiceA)
    {
    case 1:
        cout<<"������Ҫ��ѯ�ڼ��ܵĿ�������״����";
        int week;
        cin>>week;
        temp_index=mylist.my_city_list[target_city_number].data_number-(week-1)*7-1;
        for(int i=temp_index;i>temp_index-7;i--)
        {
            if(mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
                day_count++;
        }
        cout<<"2006��"<<city_name<<"�е�"<<week<<"�ܿ�������״��Ϊ"<<target_air_condition<<"������Ϊ"<<day_count<<"��"<<endl;
        break;
    case 2:
        cout<<"������Ҫ��ѯ�ڼ����µĿ�������״����";
        int month;
        cin>>month;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if(mylist.my_city_list[target_city_number].data[i].month==month&&mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
                day_count++;
        cout<<"2006��"<<city_name<<"�е�"<<month<<"�¿�������״��Ϊ"<<target_air_condition<<"������Ϊ"<<day_count<<"��"<<endl;
        break;
    case 3:
        {
        cout<<"������Ҫ��ѯ�ڼ����ȵĿ�������״����";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if((mylist.my_city_list[target_city_number].data[i].month-start_month<=2)&&(mylist.my_city_list[target_city_number].data[i].month>=start_month)&&mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
                day_count++;
        cout<<"2006��"<<city_name<<"�е�"<<season<<"���ȿ�������״��Ϊ"<<target_air_condition<<"������Ϊ"<<day_count<<"��"<<endl;
        break;
        }
    case 4:
        for(int i=mylist.my_city_list[target_city_number].data_number-1;i>=0;i--)
            if(mylist.my_city_list[target_city_number].data[i].air_condition==target_air_condition)
               day_count++;
        cout<<"2006��"<<city_name<<"�п�������״��Ϊ"<<target_air_condition<<"������Ϊ"<<day_count<<"��"<<endl;
        break;
    }
}
void statistical_queryB(CITY_LIST& mylist)    //ͳ�Ʋ�ѯB
{
    int choiceA,choiceB,target_day_num,temp_index;
    string target_air_condition;
    cout<<"������������ѡ���ܣ�1.��ѯĳ�� 2.��ѯĳ�� 3.��ѯĳ���� 4.��ѯȫ�� "<<endl;
    cin>>choiceA;
    cout<<"������������ѡ��Ҫ��ѯ�Ŀ���״����1.�� 2.�� 3.��΢��Ⱦ 4.�����Ⱦ 5.����Ⱦ��"<<endl;
    cin>>choiceB;
    switch(choiceB)
    {
    case 1:
        target_air_condition="��";
        break;
    case 2:
        target_air_condition="��";
        break;
    case 3:
        target_air_condition="��΢��Ⱦ";
        break;
    case 4:
        target_air_condition="�����Ⱦ";
        break;
    case 5:
        target_air_condition="����Ⱦ";
        break;
    }
    cout<<"������x����ѯ��������Ϊ"<<target_air_condition<<"x�����ϵĳ���"<<endl;
    cin>>target_day_num;
    switch(choiceA)
    {
    case 1:
        cout<<"������Ҫ��ѯ�ڼ��ܵĿ�������״����";
        int week;
        cin>>week;
        cout<<"2006���"<<week<<"�ܿ�������Ϊ"<<target_air_condition<<"��"<<target_day_num<<"�����ϵĳ����У�"<<endl;

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
        cout<<"������Ҫ��ѯ�ڼ����µĿ�������״����";
        int month;
        cin>>month;
        cout<<"2006���"<<month<<"�¿�������Ϊ"<<target_air_condition<<"��"<<target_day_num<<"�����ϵĳ����У�"<<endl;
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
        cout<<"������Ҫ��ѯ�ڼ����ȵĿ�������״����";
        int season;
        cin>>season;
        int start_month=1+(season-1)*3;
        cout<<"2006���"<<season<<"���ȿ�������Ϊ"<<target_air_condition<<"��"<<target_day_num<<"�����ϵĳ����У�"<<endl;
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
        cout<<"2006���������Ϊ"<<target_air_condition<<"��"<<target_day_num<<"�����ϵĳ����У�"<<endl;
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
void sort_query(CITY_LIST& mylist)   //�����ѯ
{
    int choiceA,topnum,temp_index;
    Air_condition_node myarray[mylist.city_num];
    cout<<"������������ѡ���ܣ�1.��ѯĳ�� 2.��ѯĳ�� 3.��ѯĳ���� 4.��ѯȫ�� "<<endl;
    cin>>choiceA;
    cout<<"������x���鿴ƽ������������ǰx���ĳ��У�"<<endl;
    cin>>topnum;
    switch(choiceA)
    {
    case 1:
        cout<<"������Ҫ��ѯ�ڼ��ܵĿ�������״����";
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
        cout<<"2006���"<<week<<"��ƽ����������ǰ"<<topnum<<"�ĳ�����:"<<endl;
        for(int i=0;i<topnum;i++)
        {
            cout<<"No."<<i+1<<" "<<myarray[i].cityname<<endl;
        }
        break;
    case 2:
        cout<<"������Ҫ��ѯ�ڼ����µĿ�������״����";
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
        cout<<"2006���"<<month<<"��ƽ����������ǰ"<<topnum<<"�ĳ�����:"<<endl;
        for(int i=0;i<topnum;i++)
        {
            cout<<"No."<<i+1<<" "<<myarray[i].cityname<<endl;
        }
        break;
    case 3:
        {
        cout<<"������Ҫ��ѯ�ڼ����ȵĿ�������״����";
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
        cout<<"2006���"<<season<<"����ƽ����������ǰ"<<topnum<<"�ĳ�����:"<<endl;
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
        cout<<"2006��ƽ����������ǰ"<<topnum<<"�ĳ�����:"<<endl;
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
        cout<<"����������ѡ����:"<<endl;
        cout<<"1.��ͨ��ѯ������������ƺͳ��д��룬�ֱ��ѯ�ó���ÿ�졢ÿ�ܡ�ÿ�¡�ÿ���Ⱥ�ȫ��Ŀ�������״��"<<endl;
        cout<<"2.ͳ�Ʋ�ѯA������������ƺͳ��д��룬�ֱ��ѯ�ó���ÿ�ܡ�ÿ�¡�ÿ���Ⱥ�ȫ��Ŀ�������Ϊ�š�������΢��Ⱦ�������Ⱦ������Ⱦ������"<<endl;
        cout<<"3.ͳ�Ʋ�ѯB������ʱ���ѯ��������״���������ܱ�š��±�š����ȱ�Ż����ţ��Լ���������Ϊ�š�������΢��Ⱦ�������Ⱦ������Ⱦ��������������Ӧ�ĳ�������"<<endl;
        cout<<"4.�����ѯ�������ܱ�š��±�š����ȱ�Ż����ţ���ѯ���п������������а�"<<endl;
        cout<<"5.�˳�"<<endl;
        cout<<"������ѡ��"<<endl;
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
