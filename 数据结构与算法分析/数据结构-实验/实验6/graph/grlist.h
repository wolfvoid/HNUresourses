// From the software distribution accompanying the textbook
// "A Practical Introduction to Data Structures and Algorithm Analysis,
// Third Edition (C++)" by Clifford A. Shaffer.
// Source code Copyright (C) 2007-2011 by Clifford A. Shaffer.

// Include this file to access Graph representation implemented using an
// Adjacency List
# ifndef GRLIST
# define GRLIST

#include <stdio.h>
#include <ctype.h>
#include <assert.h>
// Used by the mark array
#define UNVISITED 0
#define VISITED 1

#include "link.h"
#include "llist.h"

#include "graph.h"


// Edge class for Adjacency List graph representation
class Edge
{
    int vert,wt;
public:
    Edge()
    {
        vert = -1;
        wt = -1;
    }
    Edge(int v, int w)
    {
        vert = v;
        wt = w;
    }
    int vertex()
    {
        return vert;
    }
    int weight()
    {
        return wt;
    }

};



class Graphl : public Graph
{
private:
    List<Edge>** vertex;        // List headers
    int numVertex, numEdge;     // Number of vertices, edges
    int *mark;                  // Pointer to mark array
public:
    Graphl(int numVert)
    {
        Init(numVert);
    }

    ~Graphl()         // Destructor
    {
        delete [] mark; // Return dynamically allocated memory
        for (int i = 0; i < numVertex; i++) delete [] vertex[i];
        delete [] vertex;
    }

    void Init(int n)
    {
        int i;
        numVertex = n;
        numEdge = 0;
        mark = new int[n];  // Initialize mark array
        for (i = 0; i < numVertex; i++) mark[i] = UNVISITED;
        // Create and initialize adjacency lists
        vertex = (List<Edge>**) new List<Edge>*[numVertex];
        for (i = 0; i < numVertex; i++)
            vertex[i] = new LList<Edge>();
    }

    int n()
    {
        return numVertex;    // Number of vertices
    }
    int e()
    {
        return numEdge;    // Number of edges
    }

    int first(int v)   // Return first neighbor of "v"
    {
        if (vertex[v]->length() == 0)
            return numVertex;      // No neighbor
        vertex[v]->moveToStart();
        Edge it = vertex[v]->getValue();
        return it.vertex();
    }

    // Get v's next neighbor after w
    int next(int v, int w)
    {
        Edge it;
        if (isEdge(v, w))
        {
            if ((vertex[v]->currPos() + 1) < vertex[v]->length())
            {
                vertex[v]->next();
                it = vertex[v]->getValue();
                return it.vertex();
            }
        }
        return n(); // No neighbor
    }
    // Set edge (i, j) to "weight"
    void setEdge(int i, int j, int weight)
    {
//   Assert(weight>0, "May not set weight to 0");
        assert(weight > 0);
        Edge currEdge(j, weight);
        if (isEdge(i, j))   // Edge already exists in graph
        {
            vertex[i]->remove();
            vertex[i]->insert(currEdge);
        }
        else   // Keep neighbors sorted by vertex index
        {
            numEdge++;
            for (vertex[i]->moveToStart();
                    vertex[i]->currPos() < vertex[i]->length();
                    vertex[i]->next())
            {
                Edge temp = vertex[i]->getValue();
                if (temp.vertex() > j) break;
            }
            vertex[i]->insert(currEdge);
        }
    }

    void delEdge(int i, int j)    // Delete edge (i, j)
    {
        if (isEdge(i, j))
        {
            vertex[i]->remove();
            numEdge--;
        }
    }

    bool isEdge(int i, int j)   // Is (i,j) an edge?
    {
        Edge it;
        for (vertex[i]->moveToStart();
                vertex[i]->currPos() < vertex[i]->length();
                vertex[i]->next())              // Check whole list
        {
            Edge temp = vertex[i]->getValue();
            if (temp.vertex() == j) return true;
        }
        return false;
    }

    int weight(int i, int j)   // Return weight of (i, j)
    {
        Edge curr;
        if (isEdge(i, j))
        {
            curr = vertex[i]->getValue();
            return curr.weight();
        }
        else return 0;
    }

    int getMark(int v)
    {
        return mark[v];
    }
    void setMark(int v, int val)
    {
        mark[v] = val;
    }

};

# endif // GRLIST

