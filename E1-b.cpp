/*
Name : Abiha Fatima
S.No. : 57
Faculty No. : 19COB277
Enrollment No. : GL2987
*/
#include<bits/stdc++.h>
using namespace std;

class Graph
{
    public:
    //Function to return Breadth First Traversal of given graph.
	vector<int>bfsOfGraph(int V, vector<int> adj[], int src)
	{
	    vector<int>ans;
	    
        bool arr[V] = {0};
        queue<int>q;
        q.push(src);
        
        arr[src] = 1;
        
        while (!q.empty()) {
	        int t = q.front();
	        ans.push_back(t);
	        q.pop();
	        for (auto i : adj[t]) {
		        if (arr[i] == 0)
		        q.push(i);
		        arr[i] = 1;
        }
        }
        return ans;

	}
};

int main(){
		int V,E;
	cout<<"Enter Number of vertices:\t";
	cin>>V;
	cout<<"Enter Number of Edges:\t";
	cin>>E;

    	vector<int> adj[V];
		cout<<"Enter vertices of the graph (v1, v2) :-\n";
    	for(int i = 0; i < E; i++)
    	{
    		int u, v;
    		cin >> u >> v;
    		adj[u].push_back(v);
    	}
    	int StartingVertex;
    	cout<<"Enter starting vertex: ";
    	cin>>StartingVertex;
    	
        Graph g;
        vector<int>ans=g.bfsOfGraph(V, adj,StartingVertex);
        
        cout<<"\n\nFollowing is BFS Traversal for the above graph starting from "<<StartingVertex<<" is :- \n";
        
        for(int i=0;i<ans.size();i++){
        	cout<<ans[i]<<" ";
        }
        cout<<endl;
	
	return 0;
} 

