#include "grlist.h"
#include "grmat.h"
#include "Graph_test.h"
Graph *createGraph(int graph_type, int vert_num);

void PreVisit(int v)
{
    cout << "PreVisit vertex " << v << "\n";
}

void PostVisit(int v)
{
    cout << "PostVisit vertex " << v << "\n";
}

void Visiting(int v)
{
    cout << "Visiting vertex " << v << "\n";
}

int main()
{
    int choice;
    cin >> choice;                   // 选择操作

    Graph* G;
    int vert_num;                     // 图的顶点数，编号从0开始
    cin >> vert_num;

    int graph_type = 2;               // graph_type=1, 采用临接链表表示图   graph_type=0, 采用临接矩阵表示图
    while(graph_type != 0 && graph_type != 1)
        cin >> graph_type;

    G = createGraph(graph_type, vert_num);

    char graph_dir = '0';             // graph_dir='D'为有向图 graph_dir='U'为无向图

    while(graph_dir != 'D' && graph_dir != 'U')
        cin >> graph_dir;



    int fr_vert, to_vert, wt;
    while(cin >> fr_vert >> to_vert >> wt)
    {
        G->setEdge(fr_vert, to_vert, wt);
        if (graph_dir == 'U')
            G->setEdge(to_vert, fr_vert, wt);
    }

    option *it = new option(G);
    for (int v = 0; v < G->n(); v++)
        G->setMark(v, UNVISITED);  // Initialize mark bits

    int D[G->n()];

    switch(choice)
    {
    case 1:    //求所有节点的入度和出度
        for(int i = 0; i < G->n(); i++)
            cout << G->getInDegree(i) << " ";
        cout << endl;

        for(int i = 0; i < G->n(); i++)
            cout << G->getOutDegree(i) << " ";
        cout << endl;
        break;
    case 2:   // 深度优先搜索
        for (int v = 0; v < G->n(); v++)
        {
            if (G->getMark(v) == UNVISITED)
                it->DFS(v, PreVisit, PostVisit, Visiting);
        }
        break;
    case 3:    //广度优先搜索
        for (int v = 0; v < G->n(); v++)
        {
            if (G->getMark(v) == UNVISITED)
                it->BFS(v, PreVisit, PostVisit, Visiting);
        }
        break;

    case 4:   // Dijkstra求最短路(从0点出发至其他各点)

        for (int i = 0; i < G->n(); i++) // Initialize
            D[i] = INFINITY;
        D[0] = 0;

        it->Dijkstra1(D, 0);

        for(int k = 0; k < G->n(); k++)
        {

            if (D[k] != INFINITY)
                cout << D[k] << " ";
            else
                cout << "Infinity" << " ";
        }
        cout << endl;
        break;

    case 5:   // prim算法求最小支撑树(从0点出发至其他各点)

        for (int i = 0; i < G->n(); i++) // Initialize
            D[i] = INFINITY;
        D[0] = 0;

        it->Prim(D, 0);

        for(int k = 0; k < G->n(); k++)
            cout << D[k] << " ";
        cout << endl;
        break;
    }
    return 0;
}

Graph *createGraph(int graph_type, int vert_num)
{
    Graph *g;
    if (graph_type)
        g = new Graphl(vert_num);
    else
        g = new Graphm(vert_num);

    return g;
}

