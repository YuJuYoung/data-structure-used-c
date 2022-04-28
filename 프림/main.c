#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTIES 100
#define INF 1000L

typedef struct {
	int n;
	int weight[MAX_VERTIES][MAX_VERTIES];
} GraphType;

int selected[MAX_VERTIES];
int distance[MAX_VERTIES];

int get_min_vertex(int n) {
	int v, i;

	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && distance[i] < distance[v]) {
			v = i;
		}
	}
	return v;
}

void prim(GraphType* g, int s) {
	int i, u, v;

	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
	}
	distance[s] = 0;

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = TRUE;

		if (distance[u] == INF) {
			return;
		}
		printf("정점 %c 추가\n", u + 'A');

		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < distance[v]) {
					distance[v] = g->weight[u][v];
				}
			}
		}
	}
}

void main() {
	GraphType g = { 7, {
		{ 0, 3, 17, 6, INF, INF, INF },
		{ INF, 0, INF, 5, INF, INF, 12 },
		{ INF, INF, 0, INF, 10, 8, INF },
		{ INF, INF, INF, 0, 9, INF, INF },
		{ INF, INF, INF, INF, 0, 4, 2 },
		{ INF, INF, INF, INF, INF, 0, 14 },
		{ INF, INF, INF, INF, INF, INF, 0 }
	}};
	prim(&g, 0);
}