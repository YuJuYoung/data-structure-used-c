// c로 배우는 쉬운 자료구조 개정 3판 8-2 소스코드
// 이지영 지음

#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 30

typedef struct graphNode {
	int vertex;
	struct graphNode* link;
} graphNode;

typedef struct graphgType {
	int n;
	graphNode* adjList_H[MAX_VERTEX];
} graphgType;

void createGraph(graphgType* g) {
	g->n = 0;

	for (int v = 0; v < MAX_VERTEX; v++) {
		g->adjList_H[v] = NULL;
	}
}

void insertVertex(graphgType* g, int v) {
	if (g->n == MAX_VERTEX) {
		printf("\n 가득 참");
	}
	else {
		g->n++;
	}
}

void insertEdge(graphgType* g, int u, int v) {
	graphNode* node;

	if (u >= g->n || v >= g->n) {
		printf("\n 없는 정점");
	}
	else {
		node = (graphNode *)malloc(sizeof(graphNode));
		node->vertex = v;
		node->link = g->adjList_H[u];
		g->adjList_H[u] = node;
	}
}

void print_adjList(graphgType* g) {
	graphNode *p;

	for (int i = 0; i < g->n; i++) {
		printf("\n\t\t정점 %c의 인접 리스트", i + 65);
		p = g->adjList_H[i];

		while (p) {
			printf(" -> %c", p->vertex + 65);
			p = p->link;
		}
	}
}

void main() {
	graphgType *G1, *G2, *G3, *G4;

	G1 = (graphgType *)malloc(sizeof(graphgType));
	G2 = (graphgType *)malloc(sizeof(graphgType));
	G3 = (graphgType *)malloc(sizeof(graphgType));
	G4 = (graphgType *)malloc(sizeof(graphgType));

	createGraph(G1);
	createGraph(G2);
	createGraph(G3);
	createGraph(G4);

	for (int i = 0; i < 4; i++) {
		insertVertex(G1, i);
	}
	insertEdge(G1, 0, 3);
	insertEdge(G1, 0, 1);
	insertEdge(G1, 1, 3);
	insertEdge(G1, 1, 2);
	insertEdge(G1, 1, 0);
	insertEdge(G1, 2, 3);
	insertEdge(G1, 2, 1);
	insertEdge(G1, 3, 2);
	insertEdge(G1, 3, 1);
	insertEdge(G1, 3, 0);
	printf("\n G!의 인접 리스트");
	print_adjList(G1);

	for (int i = 0; i < 3; i++) {
		insertVertex(G2, i);
	}
	insertEdge(G2, 0, 2);
	insertEdge(G2, 0, 1);
	insertEdge(G2, 1, 2);
	insertEdge(G2, 1, 0);
	insertEdge(G2, 2, 1);
	insertEdge(G2, 2, 0);
	printf("\n\n G2의 인접 리스트");
	print_adjList(G2);

	for (int i = 0; i < 4; i++) {
		insertVertex(G3, i);
	}
	insertEdge(G3, 0, 3);
	insertEdge(G3, 0, 1);
	insertEdge(G3, 1, 3);
	insertEdge(G3, 1, 2);
	insertEdge(G3, 2, 3);
	printf("\n\n G3의 인접 리스트");
	print_adjList(G3);

	for (int i = 0; i < 3; i++) {
		insertVertex(G4, i);
	}
	insertEdge(G4, 0, 2);
	insertEdge(G4, 0, 1);
	insertEdge(G4, 1, 2);
	insertEdge(G4, 1, 0);
	printf("\n\n G4의 인접 리스트");
	print_adjList(G4);
}