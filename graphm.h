#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <iostream>
#include <fstream>

using namespace std;

//---------------------------------------------------------------------------
// GraphM class:  graph class (graph of nodes) for Dijkstra's algorithm 
//   includes:
//   -- allows building of a graph from data, allows clearing graph
//   -- allows finding shortest paths between nodes using Dijkstra's
//      algorithm
//   -- allows for displaying of entire graph (nodes, edges, shortest path)
//   -- allows displaying single shortest path between two nodes
//
// Implementation and assumptions:
//   -- implemented using multiple arrays:
//      - an array of NodeData that contains names of nodes
//      - a 2D array of integers that contains weight of edges
//      - a 2D array of struct TableType that represents shortest distances
//        T[x][y]
//   -- TableType contains an integer that represents distance from x to y
//      and an integer that represents the previous node in shortest path
//   -- assumes no graph data will have mnore nodes than max size variable
//   -- data must be formatted correctly for building graph
//   -- invalid integers in data(out of size range or negatives) are ignored
//---------------------------------------------------------------------------
static const int MAXSIZE = 100;                         // maximum number of
                                                        // nodes in graph

class GraphM {
    public:
        GraphM();                                       // constructor

        ~GraphM();                                      // destructor

        void buildGraph(ifstream&);                     // reads data from
                                                        // file into graph

        bool insertEdge(int from, int to, int weight);  // inserts an edge
                                                        // into graph

        bool removeEdge(int from, int to);              // removes an edge
                                                        // from graph if it
                                                        // exists

        void display(int from, int to);                 // displays shortest
                                                        // path cost and 
                                                        // actual path

        void displayAll();                              // displays all 
                                                        // shortest paths
                                                        // (cost and path)

        void findShortestPath();                        // uses Dijkstra's
                                                        // algorithm to 
                                                        // find shortest 
                                                        // paths between
                                                        // all nodes


    private:
        struct TableType {
            bool visited;                               // represents if
                                                        // findShortestPath
                                                        // has been here

            int dist;                                   // represents cost
                                                        // of shortest path

            int path;                                   // represents prev.
                                                        // node in shortest
                                                        // path
        };

        NodeData data[MAXSIZE];                         // contains names
                                                        // of nodes

        int C[MAXSIZE][MAXSIZE];                        // contains edges
                                                        // between nodes

        int size;                                       // number of nodes
                                                        // in graph

        TableType T[MAXSIZE][MAXSIZE];                  // keeps track of
                                                        // shortest path
                                                        // (cost and path)

        void printPathNum(int from, int to);            // helper for
                                                        // display and
                                                        // displayAll

        void printPathName(int from, int to);           // helper for
                                                        // display

        int findClosestNode(int source);                // helper for 
                                                        // findShortestPath
};

#endif