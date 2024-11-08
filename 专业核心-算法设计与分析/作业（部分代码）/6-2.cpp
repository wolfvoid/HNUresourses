#include <fstream>
#include <iostream>
using namespace std;

template <class Type>
class MinHeap // 最小堆类；
{
public:
    MinHeap(Type a[], int n);   // 带两参数的构造函数，在此程序中没有应用；
    MinHeap(int ms);            // 构造函数重载，只初始化堆的大小，对堆中结点不初始化；另外，堆元素的存储是以数组
    ~MinHeap();                 // 形式，且无父、子指针，访问父亲结点，利用数组标号进行；
    bool Insert(const Type &x); // 插入堆中一个元素；
    bool RemoveMin(Type &x);    // 删除堆顶最小结点；
    void MakeEmpty();           // 使堆为空
    bool IsEmpty();
    bool IsFull();
    int Size();

protected:
    void FilterDown(const int start, const int endOfHeap); // 自顶向下构造堆
    void FilterUp(const int start);                        // 自底向上构造堆
private:
    Type *heap;
    int maxSize;
    const int defaultSize;
    int currentSize; // 堆当前结点个数大小
};

template <class Type>
MinHeap<Type>::MinHeap(int ms) : defaultSize(100)
{
    maxSize = (ms > defaultSize) ? ms : defaultSize;
    heap = new Type[maxSize];
    currentSize = 0;
}

template <class Type>
MinHeap<Type>::MinHeap(Type a[], int n) : defaultSize(100)
{
    maxSize = (n > defaultSize) ? n : defaultSize;
    heap = new Type[maxSize];
    currentSize = n;
    for (int i = 0; i < n; i++)
        heap[i] = a[i];
    int curPos = (currentSize - 2) / 2;
    while (curPos >= 0)
    {
        FilterDown(curPos, currentSize - 1);
        curPos--;
    }
}

template <class Type>
MinHeap<Type>::~MinHeap()
{
    delete[] heap;
}

template <class Type>
void MinHeap<Type>::FilterDown(const int start, const int endOfHeap)
{
    int i = start, j = i * 2 + 1;
    Type temp = heap[i];
    while (j <= endOfHeap)
    {
        if (j < endOfHeap && heap[j] > heap[j + 1])
            j++;
        if (temp < heap[j])
            break;
        else
        {
            heap[i] = heap[j];
            i = j;
            j = 2 * i + 1;
        }
    }
    heap[i] = temp;
}

template <class Type>
void MinHeap<Type>::FilterUp(const int start)
{
    int i = start, j = (i - 1) / 2;
    Type temp = heap[i];
    while (i > 0)
    {
        if (temp >= heap[j])
            break;
        else
        {
            heap[i] = heap[j];
            i = j;
            j = (i - 1) / 2;
        }
    }
    heap[i] = temp;
}

template <class Type>
bool MinHeap<Type>::RemoveMin(Type &x)
{
    if (IsEmpty())
    {
        cerr << "Heap empty!" << endl;
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    FilterDown(0, currentSize - 1);
    return true;
}

template <class Type>
bool MinHeap<Type>::Insert(const Type &x)
{
    if (IsFull())
    {
        cerr << "Heap Full!" << endl;
        return false;
    }
    heap[currentSize] = x;
    FilterUp(currentSize);
    currentSize++;
    return true;
}

template <class Type>
bool MinHeap<Type>::IsEmpty()
{
    return currentSize == 0;
}

template <class Type>
bool MinHeap<Type>::IsFull()
{
    return currentSize == maxSize;
}

template <class Type>
void MinHeap<Type>::MakeEmpty()
{
    currentSize = 0;
}

template <class Type>
int MinHeap<Type>::Size()
{
    return currentSize;
}

// 最小堆结点
class HeapNode // 堆结点类；
{
    friend class DealNode;

public:
    operator int() const { return cn; }

private:
    int i,  // i标示堆中结点号
        cn, // cn标示当前加入的覆盖顶点中权重之和
        *x, // x数组标示那些顶点加入了覆盖顶点的行列
        *c; // c数组标示X中的覆盖顶点中所有的邻接顶点
};

// VC类用来对堆中结点内部的的操作
class DealNode
{
    friend int MinCover(int **, int[], int);

private:
    void BBVC();
    bool cover(HeapNode E);
    void AddLiveNode(MinHeap<HeapNode> &H, HeapNode E, int cn, int i, bool ch);
    int **a, n, *w, *bestx, bestn;
};

void DealNode::BBVC()
{
    // 建立初始空堆
    MinHeap<HeapNode> H(1000);
    HeapNode E;
    E.x = new int[n + 1];
    E.c = new int[n + 1];
    for (int j = 1; j <= n; j++)
    {
        E.x[j] = E.c[j] = 0;
    }

    int i = 1, cn = 0;
    while (true)
    {
        if (i > n)
        {
            if (cover(E))
            {
                for (int j = 1; j <= n; j++)
                    bestx[j] = E.x[j];
                bestn = cn;
                break;
            }
        }
        else
        {
            if (!cover(E))
                AddLiveNode(H, E, cn, i, true); // 加入结点标号为i 的结点到顶点覆盖集中，并把更新后的结点再插入堆中
            AddLiveNode(H, E, cn, i, false);    // 不把结点标号为 i 的结点加入到顶点覆盖集中，并把更新后的结点插入堆中
        }
        if (H.IsEmpty())
            break;
        H.RemoveMin(E); // 取堆顶点赋给E
        cn = E.cn;
        i = E.i + 1;
    }
}

// 检测图是否被覆盖
bool DealNode::cover(HeapNode E)
{
    for (int j = 1; j <= n; j++)
    {
        if (E.x[j] == 0 && E.c[j] == 0) // 存在任意一条边的两个顶点都为0的情况下，为未覆盖情况
            return false;               // X[j]记录覆盖顶点，c[j]记录与覆盖顶点相连的顶点 0表征未覆盖，1表征已覆盖
    }
    return true;
}

void DealNode::AddLiveNode(MinHeap<HeapNode> &H, HeapNode E, int cn, int i, bool ch)
{
    HeapNode N;
    N.x = new int[n + 1];
    N.c = new int[n + 1];
    for (int j = 1; j <= n; j++)
    {
        N.x[j] = E.x[j];
        N.c[j] = E.c[j];
    }
    N.x[i] = ch ? 1 : 0;

    if (ch)
    {
        N.cn = cn + w[i]; // 记录i顶点是否加入覆盖的行列中；
        for (int j = 1; j <= n; j++)
            if (a[i][j] > 0) // 如果i,j相邻，刚把j顶点加入覆盖邻接顶点集中；
                N.c[j]++;
    }
    else
    {
        N.cn = cn;
    }
    N.i = i;
    H.Insert(N); // 插入堆中
}

int MinCover(int **a, int v[], int n)
{
    DealNode Y;
    Y.w = new int[n + 1];
    for (int j = 1; j <= n; j++)
    {
        Y.w[j] = v[j]; // 初始化DealNode类对象Y;
    }
    Y.a = a;
    Y.n = n;
    Y.bestx = v; // 将地址赋予bestx，
    Y.BBVC();
    return Y.bestn; // bestn是最后的最小顶点覆盖集权重；
}

int main()
{
    int startV, endV;       // 一条边的起始节点，终止节点
    int vertexNum, edgeNum; // 顶点数，边数
    int i;

    cin >> vertexNum >> edgeNum;

    int **a; // 图的邻接矩阵表示，1表示有边
    a = new int *[vertexNum + 1];

    for (int k = 0; k <= vertexNum; k++)
        a[k] = new int[vertexNum + 1];
    for (int i = 0; i <= vertexNum; i++)
        for (int j = 0; j <= vertexNum; j++)
            a[i][i] = 0;

    int *p; // 顶点的权值数组
    p = new int[vertexNum + 1];
    for (i = 1; i <= vertexNum; i++)
        cin >> p[i];

    for (i = 1; i <= edgeNum; i++)
    {
        cin >> startV >> endV;
        a[startV][endV] = 1;
        a[endV][startV] = 1;
    }

    int minVertex = MinCover(a, p, vertexNum);
    cout << minVertex << endl;
    for (i = 1; i <= vertexNum; i++)
    {
        cout << p[i] << " ";
    }
    cout << endl;

    return 0;
}
