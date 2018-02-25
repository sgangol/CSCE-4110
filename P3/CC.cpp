/*
#  AUTHOR:     Srizan Gangol
#  COURSE:      CSCE 4110
#  ASSIGNMENT:  Assignment #2
#  DESCRIPTION: Centrality Closeness Calculator
#
#
#  Usuage:
#         $ g++ CC.cpp -o closeness
#         $ ./closeness
#         Enter filename: bcspwr04	[.mtx added automatically]
#         Enter # of Nodes: 274
#
#  ..
#  .
*/


#include <iostream>
#include <cstdio>
#include <fstream>

#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <list>

#include <cstring>
#include <sstream>
#include <algorithm>
#include <limits>

#include <time.h>

using namespace std;

// A simple neighbor struct, consisting of the target neighbor and the edge weight.
struct neighbor {
    int target;
    int weight;
    neighbor(int mTarget, int mWeight) : target(mTarget), weight(mWeight) {
    }
};

// The new adjacency list type.
typedef vector<vector<neighbor> > adjacency_list;

// Dijkstra's algorithm is used to calculate all the single source shortest paths in a weighted graph and the source's closeness.
float dijkstra_SSSP(int src, int n, stack<int> &visitStack, vector<int> &sigma, list<int> *pred, adjacency_list &adjList) {
    // Closeness counter.
    float closeness = 0;

    // Vector that holds the distances from the source.
    vector<int> dist;
    dist.resize(n, numeric_limits<int>::max());
    dist[src] = 0;
    
    // Queue used for the Dijkstra's algorithm.
    set<pair<int, int> > visitQueue;
    visitQueue.insert(make_pair(dist[src], src));

    // While there are still elements in the queue.
    while (!visitQueue.empty()) {
        // Pop the first.
        set<pair<int, int> >::iterator vPair = visitQueue.begin();
        int srcDist = vPair->first;
        int v = vPair->second;
        visitQueue.erase(vPair);
        visitStack.push(v);

        // Closeness part aggregation.
        closeness += srcDist;

        // Check the neighbors w of v.
        for (vector<neighbor>::iterator it = adjList[v].begin(); it != adjList[v].end(); it++) {
            int w = it->target;
            int newDist = srcDist + it->weight;
            // Node w found for the first time or the new distance is shorter?
            if (newDist < dist[w]) {
                visitQueue.erase(make_pair(dist[w], w));
                visitQueue.insert(make_pair(newDist, w));
                dist[w] = newDist;
                pred[w].clear();
                sigma[w] = 0;
            }
            // Is the shortest path to w via u?
            if (newDist == dist[w]) {
                pred[w].push_back(v);
                sigma[w] += sigma[v];
            }
        }
    }
    // Closeness part inversion.
    if (closeness!=0) {
        return 1.0 / closeness;
    } else {
        return 0;
    }
}

// BFS algorithm is used to calculate all the single source shortest paths in a non weighted graph and the source's closeness.
float bfs_SSSP(int src, int n, stack<int> &visitStack, vector<int> &sigma, list<int> *pred, adjacency_list &adjList) {
    // Closeness counter.
    float closeness = 0;
    
    // Vector that holds the distances from the source.
    vector<int> dist;
    dist.resize(n, -1);
    dist[src] = 0;

    // Queue used for the Bfs algorithm.
    queue<int> visitQueue;
    visitQueue.push(src);
    
    // While there are still elements in the queue.
    while (!visitQueue.empty()) {
        // Pop the first.
        int v = visitQueue.front();
        visitQueue.pop();
        visitStack.push(v);

        // Closeness part aggregation.
        closeness += dist[v];
        
        // Check the neighbors w of v.
        for (vector<neighbor>::iterator it = adjList[v].begin(); it != adjList[v].end(); it++) {
            int w = it->target;
            // Node w found for the first time?
            if (dist[w] < 0) {
                visitQueue.push(w);
                dist[w] = dist[v] + 1;
            }
            // Is the shortest path to w via u?
            if (dist[w] == dist[v] + 1) {
                pred[w].push_back(v);
                sigma[w] += sigma[v];
            }
        }

    }    
    // Closeness part inversion.
    if (closeness!=0) {
        return 1.0 / closeness;
    } else {
        return 0;
    }
}

// Prompts the user to type an input filename and returns the file pointer.
FILE * readPrompt() {
    FILE * fp;
    char str[100];
    
    // Prompt filename input.
    cout << "Enter filename: ";
    cin >> str;
    
    // Append .mtx if the user did not provide it.
    if (strstr(str, ".mtx") == NULL) {
        strcat(str, ".mtx");
    }
    
    // Open the file and return fp, if it exists, otherwise exit with error.
    fp = fopen(str, "r");
    if (fp == NULL) {
        cout << "File '" << str << "' not found.";
        exit(EXIT_FAILURE);
    } else {
        return fp;
    }
}

// Prints input file statistics just after input has finished.
void printInputStats(bool isWeigthed, int n, int e) {
    ofstream out;
    out.open ("out_graph_stats.txt");
    cout << "\n==================="
            << "\nINPUT GRAPH STATS"
			//<< "\n>Weighted: " << boolalpha << bool(isWeigthed)
            << "\n>#ofNodes: " << n
            << "\n>#ofEdges: " << e
            << "\n===================\n\n";
    out << "\n>#ofNodes: " << n
        << "\n>#ofEdges: " << e;
    out.close();
}

// Reads an input file and fills up the adjacency list as well as the edges.
void readGraph(int &n, bool &isWeigthed, adjacency_list &adjList, map<string, float> edgeList) {

    int e = 0; // Total number of edges (for statistics).
    isWeigthed = false;
	
    char * line = NULL;
    size_t len = 0;
    srand (time(NULL));
	
	
	FILE * fp = readPrompt();
	cout << "Enter # of Nodes: ";
    cin >> n;
  
    // Read the nodes and the edges, one by one, and fill up adjList and edgeBetweenness.
    int start, end, weight;
    while (getline(&line, &len, fp) != -1) {
        e++;
		 /* initialize random seed: */
		srand (time(NULL));

		

        start = atoi(strtok(line, " ")) - 1;
        end = atoi(strtok(NULL, " ")) - 1;
		//weight = atoi(strtok(NULL, " "));
		//weight = 1;
		weight = rand() % 10 + 1;
		//isWeigthed = true;
		/*
        // Check if the graph is weighted. If w<=0, the input is malformed
        if (weight > 1) {
            isWeigthed = true;
        } else if(weight<=0) {
            cout << "\nERROR!! The Graph Doesn't have weight\n";
            exit(EXIT_FAILURE);
        }
		
		*/
		
		
		adjList.reserve(n);
        //edgeList.insert(pair<string, float>(getEdgeTag(start, end), 0));
        adjList[start].push_back(neighbor(end, weight));
        adjList[end].push_back(neighbor(start, weight));
		
    }
	
    if (line) {
        free(line);
    }
    
    // Print statistics after reading.
    printInputStats(isWeigthed, n, e);
	
}

// Clears the variables or re-initializes to 0, so that they are ready for the next loop.
void resetVariables(int src, int n, list<int> *pred, vector<int> &sigma, vector<float> &delta) {
    for (int i = 0; i < n; i++) {
        pred[i].clear();
    }

    sigma.clear();
    sigma.resize(n, 0);
    sigma[src] = 1;

    delta.clear();
    delta.resize(n, 0);
}

// Prints Closeness Centrality.
void printCloseness( int n, vector<float> closeness, bool normalize) {
    float nrml = 1;
    if (normalize) {
        nrml = 1.0/(n - 1);
    } 
    ofstream out;
    out.open ("out_closeness.txt");	
	cout << "\n\n > Ten Highest Closeness Centrality\n";
	float sortedcloseness[n];
	for (int i=0; i < n; i++){
		sortedcloseness[i]=closeness[i];
	}
	sort(sortedcloseness, sortedcloseness+n, greater<float>());
	for (int i = 0; i < 10; ++i){
		for (int x = 0; x < n; ++x){
			if (closeness[x] == sortedcloseness[i]) cout << " Node " << x+1 << "  \t Closeness Centrality: " << sortedcloseness[i]/ nrml << "\n";
		}
	}
	out.close();
	char usrin;
	cout << "\n> ENTER 'Y' to print all Closeness Centrality:\t";
	cin >> usrin;
	
	if ((usrin=='Y')|(usrin=='y')){
		cout << "\n> Closeness Centrality" << endl;    
		for (int i = 0; i < n; i++) {
			cout << "Node " << i+1 << ": " << closeness[i] / nrml << endl;
			out << "Node " << i+1 << ": " << closeness[i] / nrml << endl;
		}
		cout << " ALL DONE!! \n";
	}
	
		cout << "\n Exitting Program ! \n";
	
	
    
}
int main(void) {
    int n; // Number of nodes
    bool isWeigthed; // Weighted graph check.
    adjacency_list adjList; // Adjacency list.

    // Centrality measures.
    map<string, float> edgeBetweenness;
	vector<float> closeness;
    closeness.resize(n, 0);
	
    // Input is read, and values are set to all the arguments.
    readGraph(n, isWeigthed, adjList, edgeBetweenness);
	
    list<int> pred[n]; // List of predecessors of node v.
    vector<int> sigma;
    vector<float> delta;
    stack<int> visitStack; // Stack that holds the inverse order of visited nodes.
    
    // For each node of the graph.
    for (int src = 0; src < n; src++) { 
        // Prepare the variables for the next loop.
        resetVariables(src, n, pred, sigma, delta);

        if (isWeigthed) {
            // Closeness part. Using Dijkstra because graph is weighted.
            closeness[src] = dijkstra_SSSP(src, n, visitStack, sigma, pred, adjList);
        } else {
            // Closeness part.
            closeness[src] = bfs_SSSP(src, n, visitStack, sigma, pred, adjList);
        }
    }
    
    // Printing output.
    printCloseness(n, closeness, true);

    
    return 0;
}
