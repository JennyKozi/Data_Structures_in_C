#include "graph.h"

#define TRUE 1
#define FALSE 0

// Undirected Graph

typedef int ListItem;
typedef struct edge *Listptr;

typedef struct edge {
	ListItem endpoint;
	struct edge *nextedge;
} Edge;

typedef struct graph {
	int n;  // Number of vertices in the graph
	Listptr firstedge[MAXVERTEX];
} Graph;

// Lists: Functions
void Create_List(Listptr *);
int IsEmpty_List(Listptr);
int InsertAtStart_List(Listptr *, ListItem);
int InsertAfter_List(Listptr, ListItem);
int Insert_List(Listptr *, ListItem);
void Print_List(Listptr);
void Free_List(Listptr *);

// Graphs: Functions
void PrintElement(Vertex);
int Shortest_BFS(Graphptr, Vertex);
void ConnectedComp_BFS(Graphptr);
int SearchVertex(Vertex, Vertex, Vertex *, int);
int Rec(Vertex **, int *, Vertex, Vertex, int, int);

// Other Functions
void Selection_Sort(int *, int);
void Swap(int *, int *);
