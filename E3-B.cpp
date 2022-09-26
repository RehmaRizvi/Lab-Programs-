/*
Name : Abiha Fatima
S.No. : 57
Faculty No. : 19COB277
Enrollment No. : GL2987
*/
#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

struct Edge {
	int src, dest, w;
};


struct Graph {

	int V, E;

	struct Edge* edge;
};

struct Graph* createGraph(int V, int E)
{
	struct Graph* graph = new Graph;
	graph->V = V;
	graph->E = E;
	graph->edge = new Edge[E];
	return graph;
}

void printArr(int distance[], int n)
{
	printf("Vertex\t\tDistance from Source\n");
	for (int i = 0; i < n; ++i)
		printf("%d \t\t %d\n", i, distance[i]);
}

void BellmanFordAlgo(struct Graph* graph, int src)
{
    int V = graph->V;
    int E = graph->E;
    int distance[V];
    int i,j;
    for (i = 0; i < V; i++)
        distance[i] = 9999999;
    distance[src] = 0;

    for (i = 1; i <= V-1; i++)
    {
        for (j = 0; j < E; j++)
        {
            int u = graph->edge[j].src;
            int v = graph->edge[j].dest;
            int w = graph->edge[j].w;
            if (distance[u] + w < distance[v])
                distance[v] = distance[u] + w;
        }
    }
    
    for (i = 0; i < E; i++)
    {
        int u = graph->edge[i].src;
        int v = graph->edge[i].dest;
        int w = graph->edge[i].w;
        if (distance[u] + w < distance[v])
            {
                cout << "Graph contains negative weight cycle" << endl;
               return;
            }
    }
    printArr(distance, V);
    return;
}

int main()
{
	int V,E; 
	srand(time(0));
	V = rand() % 10 + 1;
	E = rand() % 20 + 2;
	cout<<"total number of randomly generated nodes:\t"<<V;
	cout<<"\ntotal number of randomly generated edges:\t"<<E<<endl;
	struct Graph* graph = createGraph(V, E);
	int u,v,w;
	for(int i=0;i<E;i++){
		u = rand()%V;
		v = rand()%V+1;
		
		//Assigning random weights to edges: 
		w = rand() % 15 + (-5);
		cout<<"\nThe weight between "<<u<<" and "<<v<<" : "<<w;
			graph->edge[i].src = u;
			graph->edge[i].dest = v;
			graph->edge[i].w = w;
	}

	auto start = high_resolution_clock::now();
	int src_node;
	src_node = rand()%V;
	cout<<"\n\nrandomly generated source:\t"<<src_node<<endl;
	
	BellmanFordAlgo(graph, src_node);
	
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by Bellman ford algorithm for this graph: " << duration.count() << " microseconds" << endl;

	return 0;
}


