#include "graphm.h"

using namespace std;

//----------------------------------------------------------------------------
// constructor
GraphM::GraphM() {
    // populate djikstrya's table with base values
    for (int i = 1; i < MAXSIZE; i++) {
        for (int j = 1; j < MAXSIZE; j++) {
            // using -1 as placeholder for infinity in T
            T[i][j].dist = -1;
            T[i][j].visited = false;
            T[i][j].path = 0;
            // using -1 as placeholder for nonexistent path
            C[i][j] = -1;
        }
    }
}

//----------------------------------------------------------------------------
// destructor
GraphM::~GraphM() {
    // nohting to delete that isn't automatically cleared
}

//----------------------------------------------------------------------------
// buildGraph
// Reads data from a .txt file that contains size, node names, edges, and edge
// weight between nodes
void GraphM::buildGraph(ifstream& infile) {
    int fromNode, toNode, weight;   // from and to node ends, weight of edge

    //makeEmpty();                   // include if dynamic memory anywhere

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
        data[i].setData(infile);
    }

    // read the edge data and add to the adjacency list
    for (;;) {
        infile >> fromNode >> toNode >> weight;
        if (fromNode == 0 && toNode == 0 && weight == 0) return; 

        // insert a valid edge into the adjacency list for fromNode
        if ((fromNode > 0 && toNode > 0) && 
            (fromNode <= size && toNode <= size)) {
            insertEdge(fromNode, toNode, weight);
        }
        
    }
}

//----------------------------------------------------------------------------
// insertEdge
// inserts an edge into the adjacency matrix
bool GraphM::insertEdge(int from, int to, int weight) {
    if (C[from][to] == -1) {
        C[from][to] = weight;
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// removeEdge
// removes an edge from the adjacency matrix
// shortest paths are not updated automatically, needs to be recalled
bool GraphM::removeEdge(int from, int to) {
    // check the edge to remove exists
    if ((from > 0 && to > 0) && (from <= size && to <= size)) {
        if (C[from][to] > -1) {
        // uses -1 as placeholder for no path
        C[from][to] = -1;
        return true;
        }
    }
    
    return false;
}

//----------------------------------------------------------------------------
// findShortestPath
// finds the Dijkstra's algorithm shortest path for each node to all others
// finds the path itself as well as the cost
void GraphM::findShortestPath() {
    // reset table for proper calculation (in case something's removed)
    for (int i = 1; i < MAXSIZE; i++) {
        for (int j = 1; j < MAXSIZE; j++) {
            // using -1 as placeholder for infinity in T
            T[i][j].dist = -1;
            T[i][j].visited = false;
            T[i][j].path = 0;
            // using -1 as placeholder for nonexistent path
        }
    }
    
    
    // find from each node 
    for (int i = 1; i <= size; i++) {
        // set distance from self to zero
        T[i][i].dist = 0;
        // check edges
        for (int j = 1; j <= size; j++) {
            int v = findClosestNode(i);
            // as long as there is another node to go to
            if (v > -1) {
                T[i][v].visited = true;
                for (int w = 1; w <= size; w++) {
                    // check that w is adjacent to v
                    if ((!T[i][w].visited) && (C[v][w] > -1)) {
                        // check if this dist is shorter than source to w
                        // uses -1 as infinity
                        int currDist = T[i][v].dist + C[v][w];
                        if (currDist < T[i][w].dist || T[i][w].dist == -1) {
                            T[i][w].dist = currDist;
                            T[i][w].path = v;
                        }
                    }
                }

            }
        }
    }
}

//----------------------------------------------------------------------------
// findClosestNode
// helper function for findShortestPath
// finds node with smallest distance from parameter node (represented by int)
int GraphM::findClosestNode(int source) {
    int closestNode = -1;
    // for every possible node in the graph
    for (int j = 1; j <= size; j++) {
        if (!T[source][j].visited) {
            // if closestNode isn't set to anything to yet
            if (closestNode == -1) {
                // and j is not unknown
                if (T[source][j].dist > -1) {
                    closestNode = j;
                }
        // if closestNode has been set to a real node
            } else {
            // if this node is closer
                if ((T[source][j].dist < T[source][closestNode].dist) 
                    && (T[source][j].dist != -1)) {
                        closestNode = j;
                    
                }
            }
        }
        
    }
    return closestNode;
}

//----------------------------------------------------------------------------
// displayAll
// displays all shortest paths from one node to all others
// uses recursive helper function printPathNum
void GraphM::displayAll() {
    cout << "Description               From node  To node  Dijkstra's  Path";
    cout << endl;
    for (int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for (int j = 1; j <= size; j++) {
            
            // ignore "path" to itself
            if (j != i) {
                cout << "                             ";
                cout << i << "        " << j << "        ";
                if (T[i][j].dist > 0) {
                    cout << T[i][j].dist << "        ";
                    printPathNum(i, j);
                } else {
                    cout << "---" << "        ";
                }
            cout << endl;
            }
        }
    }
    cout << endl;
}


//----------------------------------------------------------------------------
// display
// displays a single shortest path from one node to another
// uses recursive helper functions printPathNum and printPathName
void GraphM::display(int from, int to) {
    // if nodes are within graph
    if ((from > 0 && to > 0) && (from <= size && to <= size)) {
        cout << "  ";
        cout << from << "    " << to << "    ";
        if (T[from][to].dist > 0) {
            cout << T[from][to].dist << "    ";
            printPathNum(from, to);
            cout << endl;
            printPathName(from, to);
        } else {
            cout << "---" << "        ";
        }
        
        cout << endl;
        cout << endl;
    }
}

void GraphM::printPathNum(int from, int to) {
    if (T[from][to].path != 0) {
        printPathNum(from, T[from][to].path);
        cout << to << " ";
    } else {
        cout << from << " ";
    }
    
}

void GraphM::printPathName(int from, int to) {
    if (T[from][to].path != 0) {
        printPathName(from, T[from][to].path);
        cout << data[to] << endl;
    } else {
        cout << data[from] << endl;
    }
}