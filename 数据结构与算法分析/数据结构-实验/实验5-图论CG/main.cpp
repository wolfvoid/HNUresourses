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
    cin >> choice;                   // ѡ�����

    Graph* G;
    int vert_num;                     // ͼ�Ķ���������Ŵ�0��ʼ
    cin >> vert_num;

    int graph_type = 2;               // graph_type=1, �����ٽ������ʾͼ   graph_type=0, �����ٽӾ����ʾͼ
    while(graph_type != 0 && graph_type != 1)
        cin >> graph_type;

    G = createGraph(graph_type, vert_num);

    char graph_dir = '0';             // graph_dir='D'Ϊ����ͼ graph_dir='U'Ϊ����ͼ

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
    case 1:    //�����нڵ����Ⱥͳ���
        for(int i = 0; i < G->n(); i++)
            cout << G->getInDegree(i) << " ";
        cout << endl;

        for(int i = 0; i < G->n(); i++)
            cout << G->getOutDegree(i) << " ";
        cout << endl;
        break;
    case 2:   // �����������
        for (int v = 0; v < G->n(); v++)
        {
            if (G->getMark(v) == UNVISITED)
                it->DFS(v, PreVisit, PostVisit, Visiting);
        }
        break;
    case 3:    //�����������
        for (int v = 0; v < G->n(); v++)
        {
            if (G->getMark(v) == UNVISITED)
                it->BFS(v, PreVisit, PostVisit, Visiting);
        }
        break;

    case 4:   // Dijkstra�����·(��0���������������)

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

    case 5:   // prim�㷨����С֧����(��0���������������)

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

