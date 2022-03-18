#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int len = 0;

typedef struct treeNode {
	char data;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;

treeNode *makeRootNode(char data, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));

	root->data = data;
	root->left = leftNode;
	root->right = rightNode;

	return root;
}

treeNode *makeTree(char str[]) {
	len = strlen(str);

	char numStack[len / 2];
}

void preorder(treeNode* root) {
	if (root) {
		printf("%c", root->data);
		preorder(root->left);
		preorder(root->right);
	}
}

void inorder(treeNode* root) {
	if (root) {
		inorder(root->left);
		printf("%c", root->data);
		inorder(root->right);
	}
}

void postorder(treeNode* root) {
	if (root) {
		postorder(root->left);
		postorder(root->right);
		printf("%c", root->data);
	}
}

void main() {
	treeNode *n13 = makeRootNode('G', NULL, NULL);
	treeNode *n12 = makeRootNode('F', NULL, NULL);
	treeNode *n11 = makeRootNode('E', NULL, NULL);
	treeNode *n10 = makeRootNode('D', NULL, NULL);
	treeNode *n9 = makeRootNode('C', NULL, NULL);
	treeNode *n8 = makeRootNode('B', NULL, NULL);
	treeNode *n7 = makeRootNode('A', NULL, NULL);
	treeNode *n6 = makeRootNode('*', n12, n13);
	treeNode *n5 = makeRootNode('/', n10, n11);
	treeNode *n4 = makeRootNode('*', n8, n9);
	treeNode *n3 = makeRootNode('*', n7, n4);
	treeNode *n2 = makeRootNode('-', n5, n6);
	treeNode *n1 = makeRootNode('+', n3, n2);

	preorder(n1);
	printf("\n");

	inorder(n1);
	printf("\n");

	postorder(n1);
	printf("\n");
}