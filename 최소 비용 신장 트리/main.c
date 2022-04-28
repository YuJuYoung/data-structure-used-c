#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

int set_find(int curr) {
	while (parent[curr] != -1) {
		curr = parent[curr];
	}
	return curr;
}

void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);

	if (root1 != root2) {
		parent[root1] = root2;
	}
}

struct Edge {
	int start, end, weight;
};

typedef struct {
	int n;
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

void graph_init(GraphType* g) {
	g->n = 0;

	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_edge(GraphType* g, int start, int end, int w) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}

int compare(const void* a, const void* b) {
	struct Edge* x = (struct Edge*) a;
	struct Edge* y = (struct Edge*) b;
	return x->weight - y->weight;
}

void kruskal(GraphType *g) {
	int edge_accepted = 0;
	int uset, vset;
	struct Edge e;

	set_init(g->n);
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘 \n");

	int i = 0;
	while (i < g->n) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);

		if (uset != vset) {
			printf("간선 (%c, %c) %d 선택\n", e.start + 'A', e.end + 'A', e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
}

void main() {
	GraphType *g = (GraphType *)malloc(sizeof(GraphType));
	graph_init(g);

	insert_edge(g, 0, 2, 17);
	insert_edge(g, 5, 6, 14);
	insert_edge(g, 1, 6, 12);
	insert_edge(g, 2, 4, 10);
	insert_edge(g, 3, 4, 9);
	insert_edge(g, 2, 5, 8);
	insert_edge(g, 0, 3, 6);
	insert_edge(g, 1, 3, 5);
	insert_edge(g, 4, 5, 4);
	insert_edge(g, 0, 1, 3);
	insert_edge(g, 4, 6, 2);

	kruskal(g);
	free(g);
}