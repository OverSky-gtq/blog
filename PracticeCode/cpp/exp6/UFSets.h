const int DefaultSize = 10;
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
    while (parent[x] > 0)
        x = parent[x];
    return x;
}
void UFSets::Union(int Root1,int Root2) {
    parent[Root1] += parent[Root2];
    parent[Root2] = Root1;
}