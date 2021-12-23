#include "graphl.h"

using namespace std;

//----------------------------------------------------------------------------
// constructor
// Initialization of graph is done when graph is built
GraphL::GraphL() {

}

//----------------------------------------------------------------------------
// destructor
// Calls helper function makeEmpty()
GraphL::~GraphL() {
    makeEmpty();
}

void GraphL::makeEmpty() {
    for(int i = 0; i < MAXNODES; i++) {
        // get rid of list memory
        adjList[i].edges.clear();
    }
}

//----------------------------------------------------------------------------
// buildGraph
// Reads data from a .txt file that contains size, node names, and the edges
// between nodes
void GraphL::buildGraph(ifstream& infile) {
    int fromNode, toNode;          // from and to node ends of edge

    makeEmpty();                   // include if dynamic memory anywhere

    infile >> size;                // read the number of nodes
    if (infile.eof()) return;      // stop reading if no more data

    // explanation to student: when you want to read a string after an int, 
    // you must purge the rest of the int line or the end-of-line char will
    // be the string read
    string s;                      // used to read to end of line holding size
    getline(infile, s);

    // read graph node information
    for (int i=1; i <= size; i++) {
        // read using setData of the NodeData class, where adjList is the
        // array of GraphNodes and data is the NodeData object of GraphNode
        adjList[i].data.setData(infile);
        adjList[i].visited = false;
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode;
        if (fromNode == 0 && toNode == 0) return;     // end of edge data

        // insert a valid edge into the adjacency list for fromNode
        if ((fromNode > 0 && toNode > 0) && 
            (fromNode <= size && toNode <= size)) {
            adjList[fromNode].edges.push_front(toNode);
        }
        
    }
}

//----------------------------------------------------------------------------
// displayGraph
// Displays all nodes in the graph and the edges they have to other nodes
void GraphL::displayGraph() {
    cout << "Graph:" << endl;
    for (int i = 1; i <= size; i++) {
        // print out node number and name
        cout << "Node " << i << "       " << adjList[i].data << endl;
        // print out list of edges for that node
        list<int>::iterator curr = adjList[i].edges.begin();
        for (int j = 0; j < adjList[i].edges.size(); j++) {
            cout << "  edge" << " " << i << " ";
            cout << *curr << endl; 
            ++curr;
        }
    }
    cout << endl;
}

//----------------------------------------------------------------------------
// depthFirstSearch
// Displays the depth first ordering of nodes in the graph
// Uses a recursive helper function dfsHelper to move down in depth
void GraphL::depthFirstSearch() {
    cout << "Depth first ordering:";
    for (int i = 1; i <= size; i++) {
        if (!adjList[i].visited) {
            dfsHelper(i);
        }
    }
    cout << endl;
    cout << endl;
}

void GraphL::dfsHelper(int n) {
    adjList[n].visited = true;
    cout << " " << n;
    list<int>::iterator curr = adjList[n].edges.begin();
    for (int i = 0; i < adjList[n].edges.size(); i++) {
        if (!adjList[*curr].visited) {
            dfsHelper(*curr);
        }
        ++curr;
    }
    return;
}