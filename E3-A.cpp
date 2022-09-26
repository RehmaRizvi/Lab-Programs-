/*
Name : Abiha Fatima
S.No. : 57
Faculty No. : 19COB277
Enrollment No. : GL2987
*/
#include<bits/stdc++.h>
using namespace std;
using namespace chrono;


struct Graph
{
	int V;
	struct adjacency_list* arr;
};

struct adjacency_list_node
{
	int destination;
	int weight;
	struct adjacency_list_node* next;
};


struct adjacency_list
{

struct adjacency_list_node *head;
};

struct adjacency_list_node* newAdjListNode(
				int destination, int weight)
{
	struct adjacency_list_node* newNode =
			(struct adjacency_list_node*)
	malloc(sizeof(struct adjacency_list_node));
	newNode->destination = destination;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
}


struct Graph* createGraph(int V)
{
	struct Graph* graph = (struct Graph*)
			malloc(sizeof(struct Graph));
	graph->V = V;


	graph->arr = (struct adjacency_list*)
	malloc(V * sizeof(struct adjacency_list));

	for (int i = 0; i < V; ++i)
		graph->arr[i].head = NULL;

	return graph;
}

struct heap_node_minimum
{
	int v;
	int dist;
};

struct MinHeap
{
	int size;	
	int capacity;
	int *pos;
	struct heap_node_minimum **arr;
};


struct heap_node_minimum* newMinHeapNode(int v,
								int dist)
{
	struct heap_node_minimum* min_heap_node =
		(struct heap_node_minimum*)
	malloc(sizeof(struct heap_node_minimum));
	min_heap_node->v = v;
	min_heap_node->dist = dist;
	return min_heap_node;
}

struct MinHeap* createMinHeap(int capacity)
{
	struct MinHeap* minimum_heap =
		(struct MinHeap*)
	malloc(sizeof(struct MinHeap));
	minimum_heap->pos = (int *)malloc(
			capacity * sizeof(int));
	minimum_heap->size = 0;
	minimum_heap->capacity = capacity;
	minimum_heap->arr =
		(struct heap_node_minimum**)
				malloc(capacity *
	sizeof(struct heap_node_minimum*));
	return minimum_heap;
}


void addEdge(struct Graph* graph, int src,
				int destination, int weight)
{

	struct adjacency_list_node* newNode =
			newAdjListNode(destination, weight);
	newNode->next = graph->arr[src].head;
	graph->arr[src].head = newNode;


	newNode = newAdjListNode(src, weight);
	newNode->next = graph->arr[destination].head;
	graph->arr[destination].head = newNode;
}


void min_heap_node_swap(struct heap_node_minimum** a,
					struct heap_node_minimum** b)
{
	struct heap_node_minimum* t = *a;
	*a = *b;
	*b = t;
}

void minHeapify(struct MinHeap* minimum_heap,
								int index)
{
	int smallest, left, right;
	smallest = index;
	left = 2 * index + 1;
	right = 2 * index + 2;

	if (left < minimum_heap->size &&
		minimum_heap->arr[left]->dist <
		minimum_heap->arr[smallest]->dist )
	smallest = left;

	if (right < minimum_heap->size &&
		minimum_heap->arr[right]->dist <
		minimum_heap->arr[smallest]->dist )
	smallest = right;

	if (smallest != index)
	{
		heap_node_minimum *smallestNode =
			minimum_heap->arr[smallest];
		heap_node_minimum *idxNode =
				minimum_heap->arr[index];

		minimum_heap->pos[smallestNode->v] = index;
		minimum_heap->pos[idxNode->v] = smallest;

		min_heap_node_swap(&minimum_heap->arr[smallest],
						&minimum_heap->arr[index]);

		minHeapify(minimum_heap, smallest);
	}
}

int isEmpty(struct MinHeap* minimum_heap)
{
	return minimum_heap->size == 0;
}

struct heap_node_minimum* extractMin(struct MinHeap*
								minimum_heap)
{
	if (isEmpty(minimum_heap))
		return NULL;

	struct heap_node_minimum* root =
				minimum_heap->arr[0];


	struct heap_node_minimum* lastNode =
		minimum_heap->arr[minimum_heap->size - 1];
	minimum_heap->arr[0] = lastNode;


	minimum_heap->pos[root->v] = minimum_heap->size-1;
	minimum_heap->pos[lastNode->v] = 0;

	--minimum_heap->size;
	minHeapify(minimum_heap, 0);

	return root;
}

void decrKey(struct MinHeap* minimum_heap,
						int v, int dist)
{

	int i = minimum_heap->pos[v];

	minimum_heap->arr[i]->dist = dist;

	while (i && minimum_heap->arr[i]->dist <
		minimum_heap->arr[(i - 1) / 2]->dist)
	{

		minimum_heap->pos[minimum_heap->arr[i]->v] =
									(i-1)/2;
		minimum_heap->pos[minimum_heap->arr[
							(i-1)/2]->v] = i;
		min_heap_node_swap(&minimum_heap->arr[i],
				&minimum_heap->arr[(i - 1) / 2]);

		i = (i - 1) / 2;
	}
}

bool isInMinHeap(struct MinHeap *minimum_heap, int v)
{
if (minimum_heap->pos[v] < minimum_heap->size)
	return true;
return false;
}

void printArr(int dist[], int n)
{
	printf("\nVertex \t\tDistance from Source\n");
	for (int i = 0; i < n; ++i)
	{
		if(dist[i]==INT_MAX){
			cout<<i<<" \t\t "<<"0\n";
		}
		else{
		printf("%d \t\t %d\n", i, dist[i]);
	}
	}
}

void dijkstraAlgo(struct Graph* graph, int src)
{
	int V = graph->V;

	int dist[V];	

	struct MinHeap* minimum_heap = createMinHeap(V);

	for (int v = 0; v < V; ++v)
	{
		dist[v] = INT_MAX;
		minimum_heap->arr[v] = newMinHeapNode(v,
									dist[v]);
		minimum_heap->pos[v] = v;
	}

	minimum_heap->arr[src] =
		newMinHeapNode(src, dist[src]);
	minimum_heap->pos[src] = src;
	dist[src] = 0;
	decrKey(minimum_heap, src, dist[src]);

	minimum_heap->size = V;

	while (!isEmpty(minimum_heap))
	{

		struct heap_node_minimum* min_heap_node =
					extractMin(minimum_heap);

		int u = min_heap_node->v;

		struct adjacency_list_node* pCrawl =
					graph->arr[u].head;
		while (pCrawl != NULL)
		{
			int v = pCrawl->destination;

			if (isInMinHeap(minimum_heap, v) &&
					dist[u] != INT_MAX &&
			pCrawl->weight + dist[u] < dist[v])
			{
				dist[v] = dist[u] + pCrawl->weight;

				decrKey(minimum_heap, v, dist[v]);
			}
			pCrawl = pCrawl->next;
		}
	}

	printArr(dist, V);
}

int main()
{

	int V,E;
	srand(time(0));

	V = rand() % 10 + 1;
	E = rand() % 20 + 2;
	cout<<"total number of randomly generated nodes:\t"<<V;
	cout<<"\ntotal number of randomly generated edges:\t"<<E<<endl;
	struct Graph* graph = createGraph(V);
	int u,v,w;
	for(int i=0;i<E;i++){
		u = rand()%V;
		v = rand()%V+1;
		
		//Assigning random weights to edges: 
		w = rand() % 15 + 1;
        cout<<"\nThe weight between "<<u<<" and "<<v<<" : "<<w;
        addEdge(graph, u, v, w);
	}
	auto start = high_resolution_clock::now();
	
	int src_node = rand()%V;
	cout<<"\n\nrandomly generated source: "<<src_node<<endl;
	
	dijkstraAlgo(graph, src_node);
	
	auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "\nTime taken by dijkstra algorithm for this graph: " << duration.count() << " microseconds" << endl;

	return 0;
}


