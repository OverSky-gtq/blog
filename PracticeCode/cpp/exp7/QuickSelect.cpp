#include <iostream>
using namespace std;

// 快速选择算法求数列中第k小的数
int quickSelect(int arr[], int start, int end, int k) {
  if (start == end) return arr[start];
  int pivot_pos = (start + end) / 2;
  int left = start, right = end;
  // 循环比较数组的元素，并交换位置
  while (left <= right) {
    while (left <= right && arr[left] < arr[pivot_pos]) left++;    // 从左边开始扫描，找到第一个比arr[pivot_pos]大的数
    while (left <= right && arr[right] > arr[pivot_pos]) right--;    // 从右边开始扫描，找到第一个比arr[pivot_pos]小的数
    // 如果找到了一对比arr[pivot_pos]大小的数，则交换它们的位置
    if (left <= right) {
      int temp = arr[left];
      arr[left] = arr[right];
      arr[right] = temp;
      left++;
      right--;
    }
  }
  // 计算数组中比arr[pivot_pos]小的数的个数,与k作比较
  int count = right - start + 1;
  if (count == k) return arr[pivot_pos];
  if (count > k) return quickSelect(arr, start, right, k);
  if (count < k) return quickSelect(arr, right, end, k - count);
}
int main() 
{
  int arr[] = {6, 1, 2, 7, 9, 3, 4, 5, 10, 8};
  cout << quickSelect(arr, 0, 9, 3) << endl;
  system("pause");
  return 0;
}
