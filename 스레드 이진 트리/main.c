#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treeNode {
	char data;
	struct treeNode *left;
	struct treeNode *right;
	int isThreadRight;
	int isThreadLeft;
} treeNode;

treeNode* makeRootNode(char data, treeNode* leftNode, treeNode* rightNode, int isThreadRight) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));

	root->data = data;
	root->left = leftNode;
	root->right = rightNode;
	root->isThreadRight = isThreadRight;

	return root;
}

treeNode * findThreadSuccessor(treeNode* p) {
	treeNode *q = p->right;

	if (q == NULL || p->isThreadRight == 1) {
		return q;
	}
	
	while (q->left != NULL) {
		q = q->left;
	}
	return q;
}

void threadpreorder(treeNode* root) {
	treeNode* q = root;
	while (q) {
		while (q->left) {
			printf("%2c", q->data);
			q = q->left;
		}
		printf("%2c", q->data);
		q = findThreadSuccessor(q);
	}
}

void threadInorder(treeNode* root) {
	treeNode* q = root;

	while (q->left) {
		q = q->left;
	}

	while (q) {
		printf("%2c", q->data);
		q = findThreadSuccessor(q);
	}
}

void threadpostorder(treeNode* root) {
	treeNode* q = root;

	while (q->left) {
		q = q->left;
	}

	while (q) {
		printf("%2c", q->data);
		q = findThreadSuccessor(q);
	}
}

void main() {
	treeNode* n7 = makeRootNode('D', NULL, NULL, 0);
	treeNode* n6 = makeRootNode('C', NULL, NULL, 1);
	treeNode* n5 = makeRootNode('B', NULL, NULL, 1);
	treeNode* n4 = makeRootNode('A', NULL, NULL, 1);
	treeNode* n3 = makeRootNode('/', n6, n7, 0);
	treeNode* n2 = makeRootNode('*', n4, n5, 0);
	treeNode* n1 = makeRootNode('-', n2, n3, 0);

	n4->right = n5;
	n5->right = n3;
	n6->right = n7;
	n3->right = n1;

	printf("전위:");
	threadpreorder(n1);
	printf("\n");

	n7 = makeRootNode('D', NULL, NULL, 0);
	n6 = makeRootNode('C', NULL, NULL, 1);
	n5 = makeRootNode('B', NULL, NULL, 1);
	n4 = makeRootNode('A', NULL, NULL, 1);
	n3 = makeRootNode('/', n6, n7, 0);
	n2 = makeRootNode('*', n4, n5, 0);
	n1 = makeRootNode('-', n2, n3, 0);

	n4->right = n2;
	n5->right = n1;
	n6->right = n3;

	printf("중위:");
	threadInorder(n1);
	printf("\n");

	n7 = makeRootNode('D', NULL, NULL, 1);
	n6 = makeRootNode('C', NULL, NULL, 1);
	n5 = makeRootNode('B', NULL, NULL, 1);
	n4 = makeRootNode('A', NULL, n5, 0);
	n3 = makeRootNode('/', n6, NULL, 1);
	n2 = makeRootNode('*', n4, n6, 0);
	n1 = makeRootNode('-', n2, NULL, 0);

	n7->right = n3;
	n5->right = n2;
	n6->right = n7;
	n3->right = n1;
	
	printf("후위:");
	threadpostorder(n1);
	printf("\n");
}