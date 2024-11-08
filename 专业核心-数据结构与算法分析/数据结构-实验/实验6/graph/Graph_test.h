#ifndef GRAPH_TEST_H_INCLUDED
#define GRAPH_TEST_H_INCLUDED
#define INFINITY 1000000
#include "grlist.h"
#include <queue>

class option
{
private:
    Graph *G;
public:
// Start with some implementations for the abstract functions
    option(Graph *g)
    {
        G = g;
    }

    long double Dijkstra1(long double* D, int start, int end)
    {
    	int i, v, w;
        for (i = 0; i < G->n(); i++) {
            v = minVertex(D);
            G->setMark(v, VISITED);
            for (w = G->first(v); w < G->n(); w = G->next(v, w))
            {
            	long double rate=(1/(1-(long double)(G->weight(v,w))/100));
                if (D[w] > (D[v] * rate))
                    {
						D[w] = D[v] * rate;
					}
			}
        }
        return D[end];
    }

    int minVertex(long double* D)   // Find min cost vertex
    {
        int i, v = -1;
        // Initialize v to some unvisited vertex
        for (i = 0; i < G->n(); i++)
            if (G->getMark(i) == UNVISITED)
            {
                v = i;
                break;
            }
        for (i++; i < G->n(); i++) // Now find smallest D value
            if ((G->getMark(i) == UNVISITED) && (D[i] < D[v]))
                v = i;
        return v;
    }

    
};


#endif // GRAPH_TEST_H_INCLUDED

