#include <iostream>
#include <vector>
using namespace std;
const int DefaultSize = 26;
class UFSets {
  public:
    UFSets(int sz = DefaultSize) {
        size = sz; 
        parent = new int[size]; 
        for (int i = 0; i<size; ++i) {
            parent[i] = -1;
        }
    };
    ~UFSets(){delete[]parent;}
    void Union(int Root1,int Root2);
    int Find(int x);
  private:
    int *parent;
    int size;
};
int UFSets::Find(int x) {
    while (parent[x] >= 0)
        x = parent[x];
    return x;
}
void UFSets::Union(int Root1,int Root2) {
    parent[Find(Root2)] = Find(Root1);
}

bool equationsPossible(vector<string>& equations) {
        UFSets uf;
        for (const string& str: equations) {  //相等的变量名并在一起
            if (str[1] == '=') {
                int index1 = str[0] - 'a';   //将字符变量名映射为对应的数字
                int index2 = str[3] - 'a';
                uf.Union(index1, index2);
            }
        }
        for (const string& str: equations) {
            if (str[1] == '!') {
                int index1 = str[0] - 'a';  //将字符变量名映射为对应的数字
                int index2 = str[3] - 'a';
                if (uf.Find(index1) == uf.Find(index2)) {  //若不等的两个变量在一个子集合，则矛盾
                    return false;
                }
            }
        }
        return true;
}
int main()
{
    vector<string> equation;
    equation.push_back("a==b");
    equation.push_back("b==c");
<<<<<<< HEAD
    //equation.push_back("a!=b");
=======
    equation.push_back("a!=b");
>>>>>>> 822dd3b (updata)
    if(equationsPossible(equation)) {
        cout<<"存在"<<endl;
    }
    else {
         cout<<"不存在"<<endl;
    }
    system("pause");
}