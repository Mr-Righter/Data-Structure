class UF      //定义一个并查集Union-Find
{
private:
    int* parent;
    int count;
public:
    UF(int n)
    {
        this->count = n;
        parent = new int[n];
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    ~UF()
    {
        delete[]parent;
    }
    int Find(int x)     //寻找某一节点的根结点
    {
        while (parent[x] != x)
        {
            parent[x] = parent[parent[x]];   //进行路径压缩
            x = parent[x];                   //向上迭代寻找根结点
        }
        return x;
    }
    void Union(int p, int q)    //合并两棵树
    {
        int pRoot = Find(p);
        int qRoot = Find(q);
        if (pRoot == qRoot)
            return;
        else
        {
            parent[qRoot] = pRoot;
            count--;                 //合并后连通分量减1
        }
    }
    bool connected(int p, int q)  //判断是否两个结点是否连通
    {
        if (Find(p) == Find(q))   //注意这里找的是根节点，而不是父亲节点
            return true;
        else
            return false;
    }
    int getCount()   //返回连通分量个数
    {
        return count;
    }
};
