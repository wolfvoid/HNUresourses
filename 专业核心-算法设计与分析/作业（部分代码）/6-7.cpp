#include <array>
#include <bits/stdc++.h>
#include <queue>
using namespace std;
int n, *p;
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

class BoardNode
{
    friend int BBArrangeBoards(int **, int, int *&);

public:
    operator int() const { return cd; }
    int len(int **, int ii);

private:
    int *x, s, cd;
};

int BoardNode::len(int **conn, int ii)
{
    int sum = 0;
    for (int i = 1, sum = 0; i <= ii; i++)
    {
        for (int j = i + 1; j <= ii; j++)
        {
            int dist = x[i] > x[j] ? x[i] - x[j] : x[j] - x[i];
            sum += conn[i][j] * dist;
        }
    }
    return sum;
}

int BBArrangeBoards(int **conn, int n, int *&bestx)
{
    int HeapSize = 10;
    MinHeap<BoardNode>
        H(HeapSize);
    BoardNode E;
    E.x = new int[n + 1];
    E.s = 0;
    E.cd = 0;
    for (int i = 1; i <= n; i++)
        E.x[i] = i;
    int bestd = INT_MAX;
    bestx = 0;
    while (E.cd < bestd)
    {
        if (E.s == n - 1)
        {
            int ld = E.len(conn, n);
            if (ld < bestd)
            {
                delete[] bestx;
                bestx = E.x;
                bestd = ld;
            }
            else
                delete[] E.x;
        }
        else
        {
            for (int i = E.s + 1; i <= n; i++)
            {
                BoardNode N;
                N.x = new int[n + 1];
                N.s = E.s + 1;
                for (int j = 1; j <= n; j++)
                    N.x[j] = E.x[j];
                N.x[N.s] = E.x[i];
                N.x[i] = E.x[N.s];
                N.cd = N.len(conn, N.s);
                if (N.cd < bestd)
                    H.Insert(N);
                else
                    delete[] N.x;
            }
        }
        delete[] E.x;
    }
    try
    {
        H.RemoveMin(E);
    }
    catch (...)
    {
        return bestd;
    }
    while (true)
    {
        delete[] E.x;
        try
        {
            H.RemoveMin(E);
        }
        catch (...)
        {
            break;
        }
    }
    return bestd;
}

template <class T>
void Make2DArray(T **&x, int rows, int cols)
{
    x = new T *[rows];
    for (int i = 0; i < rows; ++i)
    {
        x[i] = new T[cols];
    }
}

int main()
{
    cin >> n;
    p = new int[n + 1];
    int **B;
    Make2DArray(B, n + 1, n + 1);
    for (int i = 1; i <= n - 1; i++)
        for (int j = i + 1; j <= n; j++)
            cin >> B[i][j];
    cout << BBArrangeBoards(B, n, p) << endl;
    for (int i = 1; i <= n; i++)
        cout << p[i] << " ";
    cout << endl;
    return 0;
}
