// A simple representation of graph using STL 
#include<vector> 
#include<iostream>
#include <queue> 
#include<list>
#define V 31
using namespace std;
// To add an edge 
/*
void add_edge(vector <pair<int, int> > adj[], int u,	int v, int wt){
	adj[u].push_back(make_pair(v, wt));
	adj[v].push_back(make_pair(u, wt));
}
*/
void add_edge(vector<int> adj[], int src, int dest) {
	adj[src].push_back(dest);
	adj[dest].push_back(src);
}
bool BFS(vector<int> adj[], int src, int dest, int v,
	int pred[], int dist[])
{
	// a queue to maintain queue of vertices whose 
	// adjacency list is to be scanned as per normal 
	// DFS algorithm 
	list<int> queue;

	// boolean array visited[] which stores the 
	// information whether ith vertex is reached 
	// at least once in the Breadth first search 
	bool visited[V];

	// initially all vertices are unvisited 
	// so v[i] for all i is false 
	// and as no path is yet constructed 
	// dist[i] for all i set to infinity 
	for (int i = 0; i < v; i++) {
		visited[i] = false;
		dist[i] = INT_MAX;
		pred[i] = -1;
	}

	// now source is first to be visited and 
	// distance from source to itself should be 0 
	visited[src] = true;
	dist[src] = 0;
	queue.push_back(src);

	// standard BFS algorithm 
	while (!queue.empty()) {
		int u = queue.front();
		queue.pop_front();
		for (int i = 0; i < adj[u].size(); i++) {
			if (visited[adj[u][i]] == false) {
				visited[adj[u][i]] = true;
				dist[adj[u][i]] = dist[u] + 1;
				pred[adj[u][i]] = u;
				queue.push_back(adj[u][i]);

				// We stop BFS when we find 
				// destination. 
				if (adj[u][i] == dest)
					return true;
			}
		}
	}

	return false;
}

// utility function to print the shortest distance  
// between source vertex and destination vertex 
 void printShortestDistance(vector<int> adj[], int s,int dest, int v, vector<int> &tmp)
{
	// predecessor[i] array stores predecessor of 
	// i and distance array stores distance of i 
	// from s 
	int pred[V], dist[V];

	if (BFS(adj, s, dest, v, pred, dist) == false)
	{
		//cout << "Given source and destination"
			//<< " are not connected";
		return;
	}

	// vector path stores the shortest path 
	vector<int> path;
	int crawl = dest;
	path.push_back(crawl);
	while (pred[crawl] != -1) {
		path.push_back(pred[crawl]);
		crawl = pred[crawl];
	}

	// distance from source is in distance array 
	//cout << "Shortest path length is : "
		//<< dist[dest];

	// printing path from source to destination 
	//cout << "\nPath is::\n";
	//for (int i = path.size() - 1; i >= 0; i--)
		//cout << path[i] << " ";
	//tmp.push_back(30);
	tmp = path;

	
}
int main() {
	vector<int> adj[V];
	vector<int> tmp;
	int map[7][7] = {
		{0,30,0,0,0,29,0},
		{28,27,36,0,0,25,24},
		{23,22,0,0,0,21,20},
		{19,18,17,0,16,15,14},
		{13,12,0,0,0,11,10},
		{9,8,7,0,6,5,4},
		{0,3,0,2,0,1,0},
	};
	add_edge(adj, 1, 2 );
	add_edge(adj, 2,3);
	add_edge(adj, 3,8);
	add_edge(adj, 8,12);
	add_edge(adj, 12,18);
	add_edge(adj, 18,22);
	add_edge(adj, 22,27);
	add_edge(adj, 27,30);
	add_edge(adj, 30,29);
	add_edge(adj, 29,25);
	add_edge(adj, 25,21);
	add_edge(adj, 21,15);
	add_edge(adj, 15,11);
	add_edge(adj, 11,5);
	add_edge(adj, 5,1);
	add_edge(adj, 8,9);
	add_edge(adj, 8,7 );
	add_edge(adj, 12,13);
	add_edge(adj, 18,19);
	add_edge(adj, 18,17);
	add_edge(adj, 22,23);
	add_edge(adj, 27,28);
	add_edge(adj, 27,26);
	add_edge(adj, 30,29);
	add_edge(adj, 25,24);
	add_edge(adj, 21,20);
	add_edge(adj, 15,14);
	add_edge(adj, 15,16);
	add_edge(adj, 11,10);
	add_edge(adj, 5,6);
	add_edge(adj, 5, 4);
	add_edge(adj, 12,11);
	add_edge(adj, 22,21);
	//shortestPath(adj, 31, 3,1);
	//u-1,r-2,d-3,l-4
	int i,source = 9, dest = 11,bd=4;
	//bd: bot direction;
	int dir;// next bot direction
	printShortestDistance(adj, dest, source, V,tmp);
	cout << "nodes: ";
	for (i = 0; i < tmp.size() ; i++) {
				cout << tmp[i]<<"->";
	}
	cout << "\n";
	cout << "called functions: ";
	for (i = 0; i < tmp.size()-1; i++) {
		if ((tmp[i + 1] - tmp[i]) > 1) { dir=1; }
		else if ((tmp[i + 1] - tmp[i]) < -1) { dir=3; }
		else if ((tmp[i + 1] - tmp[i]) == 1) { dir=4; }
		else if ((tmp[i + 1] - tmp[i]) == -1) { dir=2; }
		if ((dir - bd) >= 1) {
			for (int k = 0; k < (dir - bd); k++) {
				cout << "right()-> ";
			}
			bd = dir;
		}
		else if ((dir - bd) == 0) {
			//nothing
		}else{
			for (int k = 0; k < (bd-dir); k++) {
				cout << "left()-> ";
			}
			bd = dir;
		}
		cout << "forward_oneNode()-> ";
		/*
		if ((tmp[i + 1] - tmp[i]) > 1) { cout << "up->"; }
		else if ((tmp[i + 1] - tmp[i]) < -1) { cout << "down->"; }
		else if ((tmp[i + 1] - tmp[i]) == 1) { cout << "left->"; }
		else if ((tmp[i + 1] - tmp[i]) == -1) { cout << "right->"; }
		*/
	}
	return 0;
}
