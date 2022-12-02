typedef struct Adjacent_node{
    int dest;  //此邻接(目标)顶点在顶点表中的下标,不能直接使用顶点类，否则会死循环
    int cost;  //顶点与此邻接顶点形成的边上的权值
    Adjacent_node *next;   //下一个邻接顶点
    Adjacent_node(int destination,int weight):dest(destination),cost(weight),next(nullptr){}
} Edge;   //主流命名是“Edge”

struct Vertex{
    int data;    //顶点数据域
    Adjacent_node *first;   //随便一个邻接结点作为边链表头结点
};

class Graph{
  public:
    Graph(int num){
        num_vertices = num; 
        num_edges= 0; 
        vertexTable = new Vertex[num_vertices];
    }
    ~Graph(){ delete[]vertexTable; }
  private:
    int num_edges,num_vertices;  //顶点数量、边数量
    Vertex *vertexTable;   //顶点表
};