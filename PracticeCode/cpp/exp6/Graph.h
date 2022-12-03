typedef struct Adjacent_node {
    int dest;  //此邻接(目标)顶点在顶点表中的下标,不能直接使用顶点类，否则会死循环
    int cost;  //顶点与此邻接顶点形成的边上的权值
    Adjacent_node *next;   //下一个邻接顶点
    Adjacent_node(int destination = -1, int weight = 1) :dest(destination), cost(weight), next(nullptr) {}
} Edge;   //主流命名是“Edge”

struct Vertex {
    int data;    //顶点数据域
    Adjacent_node *first;   //随便一个邻接结点作为边链表头结点
    Vertex() { data = 0;  first = new Adjacent_node(); }
};

class Graph{
  public:
    Graph(int num){
        num_vertices = num;
        num_edges= 0; 
        vertexTable = new Vertex[num_vertices];
    }
    ~Graph(){ delete[]vertexTable; }
    bool insertEdge(int v1,int v2,int cost = 1);
  private:
    int num_edges,num_vertices;  //顶点数量、边数量
    Vertex *vertexTable;   //顶点表
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
        return true;
    }
    else
        return false;
}