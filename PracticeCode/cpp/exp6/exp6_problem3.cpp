#include <iostream>
#include <stack>
using namespace std;
typedef struct Adjacent_node {
    int dest;  //此邻接(目标)顶点在顶点表中的下标,不能直接使用顶点类，否则会死循环
    int cost;  //顶点与此邻接顶点形成的边上的权值
    Adjacent_node* next;   //下一个邻接顶点
    Adjacent_node(int destination = -1, int weight = 1) :dest(destination), cost(weight), next(nullptr) {}
} Edge;   //主流命名是“Edge”

struct Vertex {
    int data;    //顶点数据域
    Adjacent_node* first;   //随便一个邻接结点作为边链表头结点
    Vertex() { data = 0;  first = new Adjacent_node(); }
};
class Graph {
public:
    Graph(int num) {
        num_vertices = num;
        num_edges = 0;
        vertexTable = new Vertex[num_vertices]();
        indegree = new int[num_vertices]();
    }
    ~Graph() { delete[]vertexTable; }
    bool insertEdge(int v1, int v2, int cost = 1);

    int num_edges, num_vertices;  //顶点数量、边数量
    int* indegree;  //记录每个顶点的入度
    Vertex* vertexTable;   //顶点表
};
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
        ++indegree[v2];
        return true;
    }
    else
        return false;
}


bool Topologicalsort(Graph &G) {
    stack<int> S;
    for (int i = 0; i < G.num_vertices; ++i) {
        if (G.indegree[i] == 0) {
            S.push(i);
        }
    }
    int count = 0;
    while (!S.empty()) {
        int i = S.top();
        S.pop();
        cout << i << " ";
        ++count;
        for (auto p = G.vertexTable[i].first; p != nullptr; p = p->next) {
            int v = p->dest;
            if (!(--G.indegree[v])) {
                S.push(v);
            }
        }
    }
    if (count < G.num_vertices) {
        return false;
    }
    else {
        return true;
    }
}
int main()
{
    int n = 5;
    Graph subject(n);
    subject.insertEdge(0, 1);
    subject.insertEdge(1, 3);
    subject.insertEdge(2, 3);
    subject.insertEdge(2, 4);
    subject.insertEdge(3, 4);
    
    Topologicalsort(subject);
    system("pause");
}