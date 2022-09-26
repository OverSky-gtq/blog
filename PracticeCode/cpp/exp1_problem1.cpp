#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int BinSearch(int nums[],int n,int t)
{
	bool seq = 1;  
	if(nums[0]>nums[1] && n>=2)  //判断数组排序方式并用seq存储
		seq = 0;

    int begin = 0;
    int end = n - 1;
    while(begin <= end)
	{
        int mid = (end + begin)/2;
        if(!(nums[mid]<t ^ seq)){  //利用与seq同或，区分升序和降序的情况
            begin = mid + 1;
        }
        else if(!(nums[mid]>t ^ seq)){
            end = mid - 1;
        }
        else
            return mid;   //若找到则返回位置
    }
    return begin;   //若找不到则返回插入位置
}
int main()
{
	srand(time(0));
	const int n = 10;
	int arr[n] = {0};
	cout<<"随机生成测试数组："<<endl;
	for(int i = 0; i < n; ++i)
	{
		arr[i] = rand()%100;
		cout<<arr[i]<<'\t';
	}
	cout<<endl;

	cout<<"请选择升序(1)还是降序(2)"<<endl;
	int flag = 1;
	cin>>flag;
	std::sort(arr,arr+n);
	if(flag == 2)
		std::reverse(arr,arr+n);
		
	cout<<"最终测试数组如下："<<endl;
	for(int i = 0; i < n; ++i)
	{
		cout<<arr[i]<<'\t';
	}


	cout<<endl<<"请输入目标数字:"<<endl;
	int target;
	cin>>target;
	
	cout<<endl<<"返回结果为：";
	cout<<BinSearch(arr,n,target);
	system("pause");
	return 0;
}