#include <iostream>
#include <vector>

using namespace std;

/*
 * 思路是归并排序，每当遇到 左子数组当前元素 > 右子数组当前元素 时，
 * 意味着 [左子数组当前元素 至 末尾元素] 与 [右子数组当前元素] 构成了若干个逆序对
 */

int merge_sort(int l, int r, vector<int> &nums, int tmp[]) {
  if (l >= r) return 0;  // 终止条件
  int mid = l + (r - l) / 2;
  // 得到左右子区间内的逆序对数res，并顺带将左右子区间按从小到大排序
  int res = merge_sort(l, mid, nums, tmp) + merge_sort(mid + 1, r, nums, tmp);

  for (int k = l; k <= r; k++) {
    tmp[k] = nums[k];  // 先复制未合并前的nums数组到tmp中
  }

  // 下面要将左右子区间进行归并排序，并且加上合并后新引入的逆序对
  int i = l, j = mid + 1;
  for (int k = l; k <= r; k++) {
    if (i == mid + 1) {
      while (k <= r) nums[k++] = tmp[j++];   //把右子区间剩下的元素加入nums即可
    }
    else if (j == r + 1) {
      while (k <= r) nums[k++] = tmp[i++];  //添加左子区间的元素到nums
    }
    else if (tmp[i] <= tmp[j]) { // 往nums添加一个按从小到达排列的元素，不引入逆序对
      nums[k] = tmp[i++];
    } else {  // 对应 tmp[i] > tmp[j]
      nums[k] = tmp[j++];
      // 此时tmp[i] > tmp[j]是一个逆序对
      // 但由于左子区间已经按从小到大排好序，所以可推断出tmp[i]~tmp[mid]都大于tmp[j]
      res += mid - i + 1;
    }
  }
  return res;
}

int reversePairs(vector<int> &nums) {
  int tmp[nums.size()];
  return merge_sort(0, nums.size() - 1, nums, tmp);
}

int main() {
  int tmp;
  vector<int> test;
  while (cin >> tmp) {
    test.push_back(tmp);
    if (cin.get() == '\n') break;
  }
  cout << "逆序对的数量为：" << reversePairs(test) << endl;
  system("pause");
  return 0;
}