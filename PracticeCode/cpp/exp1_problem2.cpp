#include <iostream>
using namespace std;
bool isEqual(int* a,int n,int* b,int m) //�ж����������Ƿ����
{
    if(n != m)
        return false;
    for(int i = 0;i < n; ++i)
    {
        if(a[i] != b[i])
            return false;
    }
    return true;
}
bool isLess(int* a,int n,int* b,int m)  //�жϵ�һ�������Ƿ�С�ڵڶ�������
{
    if(a[0] != b[0]) return false;

    int i;
    for(i = 1;i<(n<m?n:m);++i){ //��һ�����
        if(a[i] != b[i])
        {
            break;
        }  
    }
    for(int j = i;j<(n<m?n:m);++j){
        if(a[j] < b[j])
        {
            return true;
        }
    }
    if(n<m)  //�ڶ������
    {
        bool isEqual = true;
        for(int i = 0;i < n; ++i)
        {
            if(a[i] != b[i])
                isEqual = false;
        }
        if(isEqual)
            return true;
    }
    return false;
}
void print(int *a,int n,int *b,int m)
{
    cout<<"��������a:";
    for(int i = 0;i<n;++i)
    {
        cout<<a[i]<<"  ";
    }
    cout<<endl<<"��������b:";
    for(int i = 0;i<m;++i)
    {
        cout<<b[i]<<"  ";
    }
    cout<<endl;
}
int main()
{
    int a[5] = {1,2,3,4,5};
    int b[5] = {1,2,3,4,5};
    cout<<"1.��֤�еȺ�����"<<endl;
    print(a,5,b,5);
    cout<<"�жϽ����"<<isEqual(a,5,b,5)<<endl;

    cout<<endl<<"2.��֤��С�������һ��"<<endl;
    int c[6] = {1,2,3,4,5,6};
    print(a,5,c,6);
    cout<<"�жϽ����"<<isLess(a,5,c,6)<<endl;

    cout<<endl<<"3.��֤��С�����������"<<endl;
    int d[5] = {0,2,5,5,4};
    print(d,5,c,6);
    cout<<"�жϽ����"<<isLess(d,5,c,6);

    
    system("pause");
    return 0;
}