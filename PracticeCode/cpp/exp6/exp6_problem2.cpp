#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int DefaultSize = 10;
class UFSets {    //并查集声明
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

struct Edge {
    int head,tail;  //边上的两点
    int cost;   //权值
    Edge(int v1,int v2,int weight = 1) :head(v1), tail(v2), cost(weight) {}
    bool operator<(Edge& e){return cost<e.cost;}
};
int Kruskal(vector<Edge>& G,int n) {
    int edges = G.size();
    sort(G.begin(),G.end());   //将边按权值升序排列
    int u,v,count = 1;   //记录生成树的边数
    int total_cost = 0;  //最小生成树 权值累加器
    int *visited = new int[n]();   //访问数组
    UFSets F(n);
    for (int i=0; count<n&&i<edges; ++i) {
        u = F.Find(G[i].head);
        v = F.Find(G[i].tail);
        if (u != v) {     //若不在同一个连通分量，则加入这条边
            F.Union(u,v);
            total_cost += G[i].cost;  //累加权值
            count++;
            visited[u] = 1;
            visited[v] = 1;
        }
    }
    for(int i = 0; i<n; ++i) {
        if(visited[i] == 0) {    //若有顶点未访问则生成失败
            cout<<"impossible"<<endl;
            return -1;
        }
    }
    return total_cost;
}
int main()
{
    const int num_vertices = 6;
    vector<Edge> test1,test2;
    test1.push_back(Edge(0,1,6));
    test1.push_back(Edge(0,3,1));
    test1.push_back(Edge(0,2,5));
    test1.push_back(Edge(1,3,5));
    test1.push_back(Edge(2,3,4));
    test1.push_back(Edge(1,4,3));
    test1.push_back(Edge(2,5,2));
    test1.push_back(Edge(3,4,6));
    test1.push_back(Edge(3,5,4));
    test1.push_back(Edge(4,5,6));
    cout<<Kruskal(test1,num_vertices)<<endl;

    //test2.push_back(Edge(0,1,6));
    test2.push_back(Edge(0,3,1));
    test2.push_back(Edge(0,2,5));
    //test2.push_back(Edge(1,3,5));
    test2.push_back(Edge(2,3,4));
    //test2.push_back(Edge(1,4,3));
    test2.push_back(Edge(2,5,2));
    test2.push_back(Edge(3,4,6));
    test2.push_back(Edge(3,5,4));
    test2.push_back(Edge(4,5,6));
    Kruskal(test2,num_vertices);

    system("pause");
}