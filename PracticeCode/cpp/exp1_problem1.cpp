#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int BinSearch(int nums[],int n,int t)
{
	bool seq = 1;  
	if(nums[0]>nums[1] && n>=2)  //�ж���������ʽ����seq�洢
		seq = 0;

    int begin = 0;
    int end = n - 1;
    while(begin <= end)
	{
        int mid = (end + begin)/2;
        if(!(nums[mid]<t ^ seq)){  //������seqͬ����������ͽ�������
            begin = mid + 1;
        }
        else if(!(nums[mid]>t ^ seq)){
            end = mid - 1;
        }
        else
            return mid;   //���ҵ��򷵻�λ��
    }
    return begin;   //���Ҳ����򷵻ز���λ��
}
int main()
{
	srand(time(0));
	const int n = 10;
	int arr[n] = {0};
	cout<<"������ɲ������飺"<<endl;
	for(int i = 0; i < n; ++i)
	{
		arr[i] = rand()%100;
		cout<<arr[i]<<'\t';
	}
	cout<<endl;

	cout<<"��ѡ������(1)���ǽ���(2)"<<endl;
	int flag = 1;
	cin>>flag;
	std::sort(arr,arr+n);
	if(flag == 2)
		std::reverse(arr,arr+n);
		
	cout<<"���ղ����������£�"<<endl;
	for(int i = 0; i < n; ++i)
	{
		cout<<arr[i]<<'\t';
	}


	cout<<endl<<"������Ŀ������:"<<endl;
	int target;
	cin>>target;
	
	cout<<endl<<"���ؽ��Ϊ��";
	cout<<BinSearch(arr,n,target);
	system("pause");
	return 0;
}