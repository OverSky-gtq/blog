#include <vector>

class Heap {
 public:
  // 向堆中插入一个新元素
  void push(int value);
  // 返回堆中元素的数量
  int size() const;
  // 弹出堆顶元素
  void pop();
  // 返回堆顶元素的值
  int top() const;
 private:
  // 堆的内部存储使用一个 vector
  std::vector<int> data_;
};

void Heap::push(int value) {
  // 将新元素添加到堆的末尾
  data_.push_back(value);
  // 维护堆的性质：如果新元素比它的父节点大，则交换它们的位置
  int index = data_.size() - 1;
  while (index > 0 && data_[index] > data_[(index - 1) / 2]) {
    std::swap(data_[index], data_[(index - 1) / 2]);
    index = (index - 1) / 2;
  }
}
int Heap::size() const {
  return data_.size();
}
int Heap::top() const {
  // 如果堆为空，则返回一个特殊值
  if (data_.empty()) return -1;

  // 堆顶元素的位置为 0，直接返回它的值即可
  return data_[0];
}
void Heap::pop() {
  // 交换堆顶元素和堆末尾元素的位置
  int last_index = data_.size() - 1;
  std::swap(data_[0], data_[last_index]);
  // 删除堆末尾元素
  data_.pop_back();
  // 维护堆的性质：如果堆顶元素比它的子节点小，则交换它们的位置
  int index = 0;
  while (true) {
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    // 如果 index 超出了堆的范围，则退出循环
    if (left_child >= data_.size()) break;
    // 找到左右子节点中较大的那个
    int largest = index;
    if (data_[left_child] > data_[largest]) largest = left_child;
    if (right_child < data_.size() && data_[right_child] > data_[largest])
      largest = right_child;
    // 如果堆顶元素已经是最大的，则退出循环
    if (largest == index) break;
    // 否则，交换堆顶元素和它的子节点
    std::swap(data_[index], data_[largest]);
    // 更新 index 为新的堆顶元素的位置
    index = largest;
  }
}

