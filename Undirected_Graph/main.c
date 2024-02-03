#include <stdio.h>
#include "graph.h"

int main(int argc, char *argv[]) {
	
	Graphptr g = Initialize(argv[1]);
	ShowGraph(g);
	BreadthFirstSearch(g, 0);
	
	if (IsConnected(g) == 1) {
		printf("\nThe graph is connected!\n");
	}
	else {
		printf("\nThe graph is not connected!\n");
	}
	ShortestPaths(g, 0);
	ConnectedComponents(g);
	Free_Graph(g);

	return 0;
}
