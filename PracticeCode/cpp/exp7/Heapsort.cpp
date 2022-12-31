#include <iostream>
using namespace std;

// 将位于arr数组中索引为k的元素向下调整，使得arr仍然保持最大堆的性质
void siftDown(int *arr, int k, int len) {
  arr[0] = arr[k];
  for (int i = 2 * k; i <= len; i *= 2) {
    if (i < len && arr[i] < arr[i + 1])
      ++i;
    if (arr[i] <= arr[0]) break;
    else {
      arr[k] = arr[i];
      k = i;
    }
  }
  arr[k] = arr[0];
}

// 将arr数组构建成一个最大堆
void BuildMaxHeap(int *arr, int len) {
  for (int i = len / 2; i > 0; --i) {
    siftDown(arr, i, len);
  }
}

// 将数组arr按照升序排列
void heap_sort(int *arr, int len) {
  BuildMaxHeap(arr, len);
  for (int i = len; i > 0; --i) {
    int temp = arr[i];
    arr[i] = arr[1];
    arr[1] = temp;
    siftDown(arr, 1, i - 1);
  }
}

int main()
{
  int arr[9] = {5,1,3,6,7,2,4,8,9};
  heap_sort(arr,9);

  bool flag = false;
  for (const int i:arr) {
    if (!flag) flag = true;
    else cout<<i<<" ";
  }
  system("pause");
}
