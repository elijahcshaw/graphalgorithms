#ifndef GRAPHL_H
#define GRAPHL_H
#include "nodedata.h"
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

//---------------------------------------------------------------------------
// GraphL class:  graph class (graph of nodes) for depth first searching 
//   includes:
//   -- allows building of a graph from data, allows clearing graph
//   -- allows depth first search of the nodes in the graph
//   -- allows displaying graph (nodes, edges, depth first ordering)
//
// Implementation and assumptions:
//   -- implemented using an array of struct GraphNode
//   -- GraphNode contains a list of ints to represent edges
//   -- assumes no graph data will have mnore nodes than max size variable
//   -- data must be formatted correctly for building graph
//   -- invalid integers in data(out of size range or negatives) are ignored
//---------------------------------------------------------------------------
static const int MAXNODES = 100;       // maximum number of nodes that can
                                       // be in graph

struct GraphNode {
    list <int> edges;                  // ints in the list represent edges

    NodeData data;                     // name of the node

    bool visited;                      // if the boolean's been visited by
                                       // depthFirstSearch()
};

class GraphL {
    public:
        GraphL();                      // constructor

        ~GraphL();                     // destructor

        void buildGraph(ifstream&);    // reads data from file into graph

        void displayGraph();           // displays all nodes and edges

        void depthFirstSearch();       // displays depth first ordering

    private:
        GraphNode adjList[MAXNODES];   // array of nodes in the graph

        int size;                      // number of nodes in the graph

        void makeEmpty();              // clears lists of edges in 
                                       // adjList

        void dfsHelper(int);           // recursive helper for 
                                       // depthFirstSearch

};

#endif