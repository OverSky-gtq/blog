#include <iostream>

using namespace std;
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int res;
void DFS(TreeNode *cur, int &k) { //倒序的中序遍历，从大到小，每遍历一个结点k就减1，为0时求得
  if (cur == nullptr) return;
  DFS(cur->right, k);
  if (k == 0) return;
  if (--k == 0) res = cur->val;
  DFS(cur->left, k);
}
int kthLargest(TreeNode *root, int k) {
  DFS(root, k);
  return res;
}

int main() {
  TreeNode *root = new TreeNode(2);
  root->left = new TreeNode(1);
  root->right = new TreeNode(4);
  root->right->left = new TreeNode(3);
  root->right->right = new TreeNode(5);
  cout << "请输入k值：";
  int k = 0;
  cin >> k;

  cout << endl << "第" << k << "大的值为" << kthLargest(root, k) << endl;
  system("pause");
  return 0;
}