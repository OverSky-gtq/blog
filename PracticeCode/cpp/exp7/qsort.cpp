#include <iostream>
using namespace std;
int partition(int *arr,int low,int high) {
    int pivot = arr[low];
    while (low < high) {
        while (low<high && arr[high]>pivot) {
            --high;
        }
        arr[low] = arr[high];
        while (low<high && arr[low]<pivot) {
            ++low;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}
void quick_sort(int *arr,int low,int high) {  //快速排序
    if (low < high) {
        int pivot_pos = partition(arr,low,high);  //获取第一个枢轴
        quick_sort(arr,low,pivot_pos-1);  //排左边
        quick_sort(arr,pivot_pos+1,high);  //排右边
    }
}
int main()
{
    int arr[9] = {5,1,3,6,7,2,4,8,9};
    
    quick_sort(arr,0,8);
    for (const int i:arr) {
        cout<<i<<" ";
    }
    system("pause");
}