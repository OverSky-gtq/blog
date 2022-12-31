#include <iostream>

using namespace std;
struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
bool DFS(TreeNode* node, TreeNode*& prev) {
  if (node == nullptr) return true;

  if (!DFS(node->left, prev)) return false;

  if (prev != nullptr && node->val <= prev->val) return false;
  prev = node;

  return DFS(node->right, prev);
}
// 在遍历的过程中维护了一个指向前驱节点的指针prev。
// 在访问每个节点时，比较当前节点的值与前驱节点的值，
// 如果当前节点的值小于等于前驱节点的值，则说明不是二叉搜索树，否则更新prev的值为当前节点
bool isBST(TreeNode* root) {
  TreeNode* prev = nullptr;
  return DFS(root, prev);
}
int main() {
  TreeNode* root = new TreeNode(2);
  // TreeNode* root = new TreeNode(5);
  root->left = new TreeNode(1);
  root->right = new TreeNode(4);
  root->right->left = new TreeNode(3);
  root->right->right = new TreeNode(5);

  if (isBST(root)) {
    cout << "是" << endl;
  } else {
    cout << "否" << endl;
  }
  system("pause");
  return 0;
}
