#include <iostream>
#include <queue>
using namespace std;
#define INF 0x3fffffff  //定义无穷大
typedef struct Adjacent_node {
    int dest;  //此邻接(目标)顶点在顶点表中的下标,不能直接使用顶点类，否则会死循环
    int cost;  //顶点与此邻接顶点形成的边上的权?
    Adjacent_node* next;   //下一个邻接顶点
    Adjacent_node(int destination = -1, int weight = 1) :dest(destination), cost(weight), next(nullptr) {}
} Edge;   //主流命名是“Edge�?

struct Vertex {
    int data;    //顶点数据�?
    Adjacent_node* first;   //随便一个邻接结点作为边链表头结�?
    Vertex() { data = 0;  first = new Adjacent_node(); }
};

class Graph {
public:
    Graph(int num) {
        num_vertices = num;
        num_edges = 0;
        vertexTable = new Vertex[num_vertices];
    }
    ~Graph() { delete[]vertexTable; }
    bool insertEdge(int v1, int v2, int cost = 1);
    int getFirstNeighbor(int v);
    int getNextNeighbor(int v, int w);
    int num_edges, num_vertices;  //顶点数量、边数量
private:
    Vertex* vertexTable;   //顶点�?
};
int Graph::getFirstNeighbor(int v) {
    auto p = vertexTable[v].first;
    return p->dest < 0 ? -1 : p->dest;
}
int Graph::getNextNeighbor(int v, int w) {
    auto p = vertexTable[v].first;
    while (p != nullptr && p->dest != w) {
        p = p->next;
    }
    if (p != nullptr && p->next != nullptr) {
        return p->next->dest;
    }
    return -1;
}
bool Graph::insertEdge(int v1, int v2, int cost) {
    if (v1 >= 0 && v2 >= 0 && v1 <= num_vertices && v2 <= num_vertices) {
        auto p = vertexTable[v1].first;
        if (p->dest < 0) {
            p->dest = v2;
        }
        else {
            while (p->next != nullptr) {
                p = p->next;
            }
            p->next = new Adjacent_node(v2);
        }
        ++num_edges;
        return true;
    }
    else
        return false;
}
void BFS_minDistance(Graph &G, int u) {
    int *d = new int[G.num_vertices];
    bool *visited = new bool[G.num_vertices];
    queue<int> Q;
    for (int i = 0; i < G.num_vertices; ++i) {   //初始化距离数组和访问数组
        d[i] = INF;
    }
    for (int i = 0; i < G.num_vertices; ++i) {
        visited[i] = false;
    }
    d[u] = 0;
    visited[u] = true;
    Q.push(u);
    cout << u;
    while (!Q.empty()) {
        u = Q.front();
        Q.pop();
        for (int w = G.getFirstNeighbor(u); w >= 0; w = G.getNextNeighbor(u, w)) {
            if (!visited[w]) {
                d[w] = d[u] + 1;
                visited[w] = true;
                Q.push(w);
            }
        }

    }
    for (int i = 0; i < G.num_vertices; ++i) {
        cout <<"到"<<i<<"的最短距离为"<<d[i]<<endl;
    }
}
int main()
{
    int n = 8;
    Graph test(n);
    test.insertEdge(1, 0);
    test.insertEdge(0, 4);
    test.insertEdge(1, 4);
    test.insertEdge(1, 2);
    test.insertEdge(2, 5);
    test.insertEdge(2, 3);
    test.insertEdge(2, 7);
    test.insertEdge(3, 7);
    test.insertEdge(7, 6);

    BFS_minDistance(test, 1);
    system("pause");
}