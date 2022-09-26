
/*
Name : Abiha Fatima
S.No. : 57
Class : A3CO
Faculty No. : 19COB277
Enrollment No. : GL2987
*/

#include<bits/stdc++.h>

using namespace std;
const int max_val = 1e4 + 5;
typedef pair<long long, int> PII;
bool marked[max_val];
vector<PII>adj[max_val];

long long primsAlgo(int u){
    priority_queue<PII, vector<PII>, greater<PII> >Q;
    int v;
    long long minCost = 0;
    PII p;
    Q.push(make_pair(0, u));
    while(!Q.empty()){
        //Selecting the edge with minimum weight
        p=Q.top();

        Q.pop();

        u=p.second;

        //Checking for cycle
        if(marked[u]==true){
            continue;
        }
        minCost += p.first;
        marked[u] = true;
        for(int i=0;i<adj[u].size();i++){
            v = adj[u][i].second;
            if(marked[v]==false){
                Q.push(adj[u][i]);
                cout<<u<<" -> "<<v<<"\tweight: "<<adj[u][i].first<<endl;
            }
        }
    }
    return minCost;
}

int main(){
    int N,E,u,v;
    long long weight, minCost;
    	 // To obtain a time-based seed
    srand(time(0));
    
    //Generating random number of nodes and edges: 
    N = rand()%20+1;
    E = rand()%25+2;
    
    cout<<"Random number of nodes generated:\t"<<N<<endl;
    cout<<"Random number of edges generated:\t"<<E<<endl;

    
	cout<<"\nGenerating random nodes and edges: "<<endl;

    for(int i=0;i<E;i++){
		u = rand()%N;
		v = rand()%N;
		
		//Assigning random weights to edges: 
		weight = rand() % 15 + 1;
        cout<<"\nThe weight between "<<u<<" and "<<v<<" : "<<weight;
        
        adj[u].push_back(make_pair(weight, v));
        adj[v].push_back(make_pair(weight, u));
    }
    int startingNode;
    cout<<"\n\nEnter the starting node: ";
    cin>>startingNode;
    cout<<"\n\nThe graph is:\n";
    minCost = primsAlgo(startingNode);
    cout<<"\nThe sum of minimum weight possible of MST for the above graph is : "<<minCost<<endl;
    return 0;
}
