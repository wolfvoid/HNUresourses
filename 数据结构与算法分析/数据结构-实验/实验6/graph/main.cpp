#include "grlist.h"
#include "Graph_test.h"
#include<iomanip>
Graph *createGraph(int vert_num);

int main()
{
    Graph* G;
    int vert_num;                     // ͼ�Ķ���������Ŵ�0��ʼ
    int m;                            // ���Ի���ת�˵��˵Ķ��� 
    cin >> vert_num >> m;
    G = createGraph(vert_num);
    int fr_vert, to_vert,wt;
    for (int i=0;i<m;i++) 
    {
    	cin >> fr_vert >> to_vert >> wt ;
        G->setEdge(fr_vert-1, to_vert-1, wt);
        G->setEdge(to_vert-1, fr_vert-1, wt);
    }
    int start,end;
    cin>>start>>end;
    start--;
    end--;
    
    option *it = new option(G);
    for (int v = 0; v < G->n(); v++)
        G->setMark(v, UNVISITED);  // Initialize mark bits
    long double D[G->n()];
      // Dijkstra�����·(��0���������������)
    for (int i = 0; i < G->n(); i++) // Initialize
        D[i] = INFINITY;
    D[start] = 1;
    long double ans=it->Dijkstra1(D, start, end);
	cout<<setprecision(8)<<fixed<<ans*100-5e-9;
    return 0;
}

Graph *createGraph(int vert_num)
{
    Graph *g;
        g = new Graphl(vert_num);
    return g;
}

