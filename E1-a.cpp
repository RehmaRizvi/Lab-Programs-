/*
Name : Abiha Fatima
S.No. : 57
Faculty No. : 19COB277
Enrollment No. : GL2987
*/
#include<bits/stdc++.h>
using namespace std;

template<typename T>

class Graph{

    map<T, list<T> > adjList;
    public:
    Graph(){

    }
    void addEdge(T u, T v){
        adjList[u].push_back(v);
    }

    void checkVisited(T node,map<T, bool> &visited){
        //Whenever you come to node mark it visited
        visited[node] = true;
        cout<<node<<" ";

        //Try to find out a node which is the neighbour of the current node and not yet visited
        for(T neighbour: adjList[node]){
            if(!visited[neighbour]){
                checkVisited(neighbour,visited);
            }
        }
    }

    void dfs(T source){
    	//Map of boolean datatype to mark visited node as true
        map<T, bool> visited;
        //Function call to check wether the node is visited or not
        checkVisited(source,visited);
    }

};


int main() {

   // a Graph of int data type
    Graph<int> g;
    int V,E;
    cout<<"Enter number of vertices:\t";
    cin>>V;
    cout<<"Enter number of edges: \t";
    cin>>E;
    
    cout<<"Enter the vertices of the Graph (v1, v2) :-\n";
    for(int i=0;i<E;i++){
    	int v1,v2;
    	cin>>v1>>v2;
    	 g.addEdge(v1, v2);
	}
	
	int startingVertex;
	cout<<"\nEnter the Starting vertex for DFS:\t";
	cin>>startingVertex;
	cout<<"\nThe DFS traversal for the above graph starting from "<<startingVertex<<" is: \n";
    g.dfs(startingVertex);
    
    return 0;
}




