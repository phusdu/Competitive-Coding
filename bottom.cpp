// BOTTOM

// We will use the following (standard) definitions from graph theory. Let V be a non-empty and finite set, its elements being called vertices (or nodes).
// Let E be a subset of the Cartesian product V×V, its elements being called edges. Then G=(V,E) is called a directed graph.

// Let n be a positive integer, and let p=(e1,…,en) be a sequence of length n of edges ei∈E such that ei=(vi,vi+1)for a sequence of vertices (v1,…,vn+1). 
// Then p is called a path from vertex v1 to vertex vn+1 in G and we say that vn+1 is reachable from v1, writing (v1→vn+1).

// Here are some new definitions. A node v in a graph G=(V,E) is called a sink, if for every node w in G that is reachable from v, v is also reachable from w. 
// The bottom of a graph is the subset of all nodes that are sinks, i.e., bottom(G)={v∈V∣∀w∈V:(v→w)⇒(w→v)}. You have to calculate the bottom of certain graphs.

// Input Specification

// The input contains several test cases, each of which corresponds to a directed graph G. Each test case starts with an integer number v, denoting the number 
// of vertices of G=(V,E) where the vertices will be identified by the integer numbers in the set V={1,…,v}. You may assume that 1≤v≤5000. That is followed by a 
// non-negative integer e and, thereafter, e pairs of vertex identifiers v1,w1,…,ve,we with the meaning that (vi,wi)∈E. There are no edges other than specified 
// by these pairs. The last test case is followed by a zero.

// Output Specification

// For each test case output the bottom of the specified graph on a single line. To this end, print the numbers of all nodes that are sinks in sorted order separated 
// by a single space character. If the bottom is empty, print an empty line.

// Sample Input

// 3 3
// 1 3 2 3 3 1
// 2 1
// 1 2
// 0

// Sample Output

// 1 3
// 2



#include<bits/stdc++.h>
using namespace std;

void dfs(vector<int> *edges, int currVertex, bool *visited, stack<int> &finishedVertices) 
{
	visited[currVertex] = true;

	for(int i = 0; i < edges[currVertex].size(); i++) 
	{
		int adjacent = edges[currVertex][i];
		if(!visited[adjacent]) 
		{
			dfs(edges, adjacent, visited, finishedVertices);
		}
	}

	finishedVertices.push(currVertex);
}

void dfs2(vector<int> *edges, int currVertex, bool *visited, unordered_set<int>* component) 
{
	visited[currVertex] = true;
	component->insert(currVertex);

	for(int i = 0; i < edges[currVertex].size(); i++) 
	{
		int adjacent = edges[currVertex][i];
		if(!visited[adjacent]) 
		{
			dfs2(edges, adjacent, visited, component);
		}
	}
}

unordered_set<unordered_set<int>*>* getStronglyConnectedComponents(vector<int> *edges, vector<int> *edgesT, int n) 
{
	bool *visited = new bool[n]();
	stack<int> finishedVertices;

	for(int i = 0; i < n; i++) 
	{
		if(!visited[i]) 
		{
			dfs(edges, i, visited, finishedVertices);
		}
	}

	delete [] visited;
	visited = new bool[n]();

	unordered_set<unordered_set<int>*>* output = new unordered_set<unordered_set<int>*>();

	while(!finishedVertices.empty()) 
	{
		int element = finishedVertices.top();
		finishedVertices.pop();

		if(visited[element]) 
		{
			continue;
		}
		unordered_set<int>* component = new unordered_set<int>();

		dfs2(edgesT, element, visited, component);
		output->insert(component);	
	}
	delete [] visited;

	return output	;
}

bool outGoingEdge(vector<int> *edges, unordered_set<int>* component) {

	unordered_set<int> :: iterator it = component->begin();
	while(it != component->end()) {
		int v = *it;
		for(int i = 0; i < edges[v].size(); i++) {
			int adjacent = edges[v][i];
			if(component->find(adjacent) == component->end()) {
				return true;
			}
		}

		it++;
	}

	return false;
}


int main() {

	int n;
	while (true) {

		cin >> n ;
		if(n == 0) {
			break;
		}

		vector<int> *edges = new vector<int>[n];
		vector<int> *edgesT = new vector<int>[n];

		int e;
		cin >> e;
		for(int i = 0; i < e; i++) {
			int f, s;
			cin >> f >> s;

			edges[f-1].push_back(s-1);
			edgesT[s-1].push_back(f-1);
		}

		unordered_set<unordered_set<int>*>* components = getStronglyConnectedComponents(edges, edgesT, n);

		unordered_set<unordered_set<int>*> :: iterator it = components->begin();
		vector<int> ans;
		while(it != components->end()) {

			unordered_set<int>* component = *it;
			if(!outGoingEdge(edges, component)) {

				unordered_set<int> :: iterator it2 = component->begin();
				while(it2 != component->end()) {
				
					ans.push_back(*it2 + 1);

					it2++;
				}
			}

			delete component;
			it++;
		}

		sort(ans.begin(), ans.end());
		for(int i = 0; i < ans.size(); i++) {
			cout << ans[i] << " " ;
		}
		cout << endl;

		delete [] edges;
	}

	return 0;
}