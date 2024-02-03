#define MAXVERTEX 20

typedef int Vertex;
typedef struct graph *Graphptr;

Graphptr Initialize(char *);
void InsertEdge(Graphptr, Vertex, Vertex);
void ShowGraph(Graphptr);
void BreadthFirstSearch(Graphptr, Vertex);
int IsConnected(Graphptr);
void ShortestPaths(Graphptr, Vertex);
void ConnectedComponents(Graphptr);
void Free_Graph(Graphptr);
