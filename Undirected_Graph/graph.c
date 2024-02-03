#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "queue.h"
#include "types.h"

int count = 0, solution = 0;
Vertex *tree_edge;
Vertex components[MAXVERTEX][MAXVERTEX];

// Initialize graph from file
Graphptr Initialize(char *filename) {
	int i, j;
	char c;
	FILE *fp;

	Graphptr graph = malloc(sizeof(Graph));
	if (graph == NULL) {
		printf("Cannot allocate memory!\n");
		exit (1);
	}

	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("\nError opening file!\n");
		exit(1);
	}
	fscanf(fp,"%d", &graph->n);

	for (i = 0; i < graph->n; i++)
		Create_List(&graph->firstedge[i]);

	while (!feof(fp)) {
		fscanf(fp, "%d", &i);
		fscanf(fp, "%c", &c);
		fscanf(fp, "%d", &j);
		InsertEdge(graph, i, j);
		count++;  // counter for edges
	}
	fclose(fp);

	for (i = 0; i < MAXVERTEX; i++) {
		for (j = 0; j < MAXVERTEX; j++) {
			components[i][j] = -1;
		}
	}
	return graph;
}

// Add an edge
void InsertEdge(Graphptr graph, Vertex vertex1, Vertex vertex2) {
	if (vertex1 < 0 || vertex1 > graph->n || vertex2 < 0 || vertex2 > graph->n) {
		printf("\nError: index out of bounds!\n");
		exit(1);
	}
	Insert_List(&graph->firstedge[vertex1], vertex2);
	Insert_List(&graph->firstedge[vertex2], vertex1);
}

// Print graph
void ShowGraph(Graphptr graph) {
	int i;

	printf("\nGraph:\n\n");
	for (i = 0; i < graph->n; i++) {
		printf(" %d: ", i);
		Print_List(graph->firstedge[i]);
		printf("\n");
	}
}

// Print verteces by order of visit and find tree edges and cross edges
void BreadthFirstSearch(Graphptr G, Vertex start) {

	Queue Q;
	int visited[MAXVERTEX];
	int count1 = 0, count2 = 0, i, j, cond = 1;
	Vertex v, w, s;
	Edge *curedge;
	Vertex *cross_edge, *tree_edge;
	
	for (v = 0; v < G->n; v++) {
		visited[v] = FALSE;
	}

	// Allocate memory to store tree edges and cross edges
	tree_edge = malloc(2 * count * sizeof(Vertex));
	cross_edge = malloc(2 * count * sizeof(Vertex));
	if (tree_edge == NULL || cross_edge == NULL) {
		printf("Cannot allocate memory!\n");
		exit (1);
	}

	if (start == 0) {
		cond = 0;
	}

	InitializeQueue(&Q);
	printf("\nBreadth First search order is:\n");

	for (s = start; s < G->n; s++) {
		if (!visited[s]) {
			Insert(s, &Q);
			visited[s] = TRUE;
			do {
				Remove(&Q, &v);
				PrintElement(v);
				curedge = G->firstedge[v];  /* curedge is a pointer to the first edge (v,_) of V */
				while (curedge) {
					w = curedge->endpoint;  /* w is a successor of v and (v,w) is the current edge */
					if (!visited[w]) {
						Insert(w, &Q);
						visited[w] = TRUE;
						if (!SearchVertex(v, w, tree_edge, count1)) { // Store tree edges
							tree_edge[count1++] = v;
							tree_edge[count1++] = w;
						}
					}
					else if (!SearchVertex(v, w, cross_edge, count2)) {
						if (!SearchVertex(v, w, tree_edge, count1)) { // Store cross edges
							cross_edge[count2++] = v;
							cross_edge[count2++] = w;
						}
					}
					curedge=curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
				}
			} while (!Empty(&Q));
		}
		if (s == G->n - 1 && cond) { // condition to check all of the verteces if start wasn't 0
			s = -1;
			cond = 0;
		}
	}
	printf("\nTree edges:\n");
	for (i = 0; i < count1; i++) {
		printf(" (%d, %d)\n", tree_edge[i], tree_edge[i+1]);
		i++;
	}
	printf("\nCross edges:\n");
	for (i = 0; i < count2; i++) {
		printf(" (%d, %d)\n", cross_edge[i], cross_edge[i+1]);
		i++;
	}
	free(cross_edge);
	free(tree_edge);
}

// PrintElement: prints the value of its parameter x
void PrintElement (Vertex x) {
	printf(" %d\n", x);
}

int SearchVertex (Vertex vertex1, Vertex vertex2, Vertex *array, int count) {
	int i;
	for (i = 0; i<count; i++) {
		if ((array[i] == vertex1 && array[i + 1] == vertex2) || (array[i] == vertex2 && array[i + 1] == vertex1))
			return 1;
		i++;
	}
	return 0;
}

// Finds if the graph is connected using BFS
int IsConnected (Graphptr G) {
	Queue Q;
	int visited[MAXVERTEX];
	int connected = 0;
	Vertex v, w, s;
	Edge *curedge;

	for (v = 0; v < G->n; v++) {
		visited[v] = FALSE;
	}
	InitializeQueue(&Q);

	for (s = 0; s < G->n; s++) {
		if (!visited[s]) {
			Insert(s, &Q);
			visited[s] = TRUE;
			do {
				Remove(&Q, &v);
				curedge = G->firstedge[v];  /* curedge is a pointer to the first edge (v,_) of V */
				while (curedge) {
					w = curedge->endpoint;  /* w is a successor of v and (v,w) is the current edge */
					if (!visited[w]) {
						Insert(w, &Q);
						visited[w] = TRUE;
					}
					curedge = curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
				}
			} while (!Empty(&Q));
			connected++;
		}
	}
	return connected;
}

// Finds the shortest paths from one vertex to all of the others
void ShortestPaths(Graphptr G, Vertex start) {
	int i, num, j = 0, s;
	int path[MAXVERTEX];

	int count_TrEd = Shortest_BFS(G, start); // count_TrEd/2 is the number of edges
	Vertex **verteces = malloc((count_TrEd/2)*sizeof(Vertex *)); // Allocate memory for (count_TrEd / 2) tree edges

	if (verteces == NULL) {
		printf("Cannot allocate memory!\n");
		exit (1);
	}

	for (i = 0; i < MAXVERTEX; i++) {
		path[i] = -1;
	}
	for (i = 0; i < count_TrEd / 2; i++) {
		verteces[i] = malloc(2*sizeof(Vertex)); // Each edge has two verteces
		if (verteces[i] == NULL) {
			printf("Cannot allocate memory!\n");
			exit (1);
		}
	}
	for (i = 0; i < count_TrEd; i++) {  // Create matrix with verteces
		verteces[j][0] = tree_edge[i];  // verteces[j][0] and verteces[j][1] represent a tree edge
		verteces[j][1] = tree_edge[++i];
		j++;
	}
	for (i = 0; i < G->n; i++) { // destination vertex
		solution = 0;
		if (i == start) {
			continue;
		}
		num = Rec(verteces, path, start, i, 0, count_TrEd);
		printf("\nFrom %d to %d:\n", start, i);

		if (num == 0) {
			printf("This path does not exist!\n");
			continue;
		}
		printf(" Distance: %d\n", num);
		printf(" Path: ");

		for (j = 0; j < MAXVERTEX; j++) {
			if (path[j] == -1) {
				break;
			}
			printf(" %d ", path[j]);
		}
		printf("\n");
		for (s = 0; s < MAXVERTEX; s++) {
			path[s] = -1;
		}
	}
	for (i = 0; i < count_TrEd / 2; i++) {
		free(verteces[i]);
	}
	free(verteces);
}

// Recursive function that finds the sortest path between two verteces and builds the path
int Rec(Vertex **array, int *path, Vertex src, Vertex dest, int count, int count1) {
	int i, num = 0;

	for (i = 0; i < count1 / 2; i++) {
		if (array[i][0] == src) {
			if (array[i][1] == dest) {
				path[count] = src;
				path[++count] = dest;
				num = count;
				solution++;
				return num;
			}
			num = Rec(array, path, array[i][1], dest, count+1, count1);
		}
		if (solution == 1) {
			path[count] = src;
			break;
		}
	}
	return num;
}

// BFS used by function ShortestPaths
int Shortest_BFS(Graphptr G, Vertex start) {
	Queue Q;
	int visited[MAXVERTEX];
	int count1 = 0, cond = 1;
	Vertex v, w, s;
	Edge *curedge;

	tree_edge = malloc(2 * count * sizeof(Vertex));
	if (tree_edge == NULL) {
		printf("Cannot allocate memory!\n");
		exit (1);
	}

	for (v = 0; v < G->n; v++) {
		visited[v]=FALSE;
	}

	InitializeQueue(&Q);

	if (start == 0) {
		cond = 0;
	}

	for (s = start; s < G->n; s++) {
		if (!visited[s]) {
			Insert(s, &Q);
			visited[s] = TRUE;
			do {
				Remove(&Q, &v);
				curedge = G->firstedge[v];  // curedge is a pointer to the first edge (v,_) of V
				while (curedge) {
					w = curedge->endpoint;  // w is a successor of v and (v,w) is the current edge
					if (!visited[w]) {
						Insert(w, &Q);
						visited[w] = TRUE;
						if (!SearchVertex(v, w, tree_edge, count1)) {  // Store tree edges
							tree_edge[count1++] = v;
							tree_edge[count1++] = w;
						}
					}
					curedge = curedge->nextedge;  /* curedge is a pointer to the next edge (v,_) of V */
				}
			} while (!Empty(&Q));
		}
		if (s == G->n-1 && cond) { // condition to check all of the verteces if start wasn't 0
			s = -1;
			cond = 0;
		}
	}
	return count1;
}

// Finds how many connected components the graph has
void ConnectedComponents(Graphptr G) {
	int i, j;
	int connected = IsConnected(G);

	ConnectedComp_BFS(G);
	printf("\n%d strongly connected components!\n", connected);

	for (i = 0; i<connected; i++) {
		Selection_Sort(components[i], MAXVERTEX); // Put the verteces of each component in order
		printf("\nStrongly connected component:\n");
		for (j = 0; j < MAXVERTEX; j++) { // Print elements of one connected component
			if (components[i][j] == -1)
				continue;
			printf(" %d ", components[i][j]);
		}
		printf("\n");
	}
}

// BFS used by function ConnectedComponents
void ConnectedComp_BFS(Graphptr G) {
	Queue Q;
	int visited[MAXVERTEX];
	int count3 = 0;
	Vertex v, w, s;
	Edge *curedge;

	int connected = 0; // counts how many connected components there are
	for (v = 0; v < G->n; v++) {
		visited[v]=FALSE;
	}

	InitializeQueue(&Q);

	for (s = 0; s < G->n; s++) {
		if (!visited[s]) {
			Insert(s, &Q);
			visited[s] = TRUE;
			do {
				Remove(&Q, &v);
				components[connected][count3++]=v;
				curedge = G->firstedge[v];  /* curedge is a pointer to the first edge (v,_) of V */
				while (curedge) {
					w = curedge->endpoint;  /* w is a successor of v and (v,w) is the current edge */
					if (!visited[w]) {
						Insert(w, &Q);
						visited[w] = TRUE;
					}
					curedge = curedge->nextedge;  /*curedge is a pointer to the next edge (v,_) of V */
				}
			} while (!Empty(&Q));
			connected++;
		}
	}
}

// Free memory
void Free_Graph(Graphptr graph) {
	int i;
	for (i = 0; i < graph->n; i++) {
		Free_List(&graph->firstedge[i]);
	}
	free(graph);
	free(tree_edge);
}

// General functions

void Swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Selection_Sort(int *array, int N) {
	int i, j, pos;

	for (i = 0; i < N; i++) {
		pos = i;
		for (j = i + 1; j < N; j++) {
			if (array[j] < array[pos])
				pos = j;
		}
		Swap(&array[i], &array[pos]);
	}	
}
