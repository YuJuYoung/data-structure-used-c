#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define STACK_SIZE 20

typedef struct treeNode {
	char data;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;

treeNode *node_stack[STACK_SIZE];
char op_stack[STACK_SIZE];

int node_top = -1;
int op_top = -1;

treeNode *makeRootNode(char data, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));

	root->data = data;
	root->left = leftNode;
	root->right = rightNode;

	return root;
}

int priority(char c) {
	if (c == '*' || c == '/') {
		return 0;
	}
	return 1;
}

void connectNode() {
	treeNode *right = node_stack[node_top--];
	treeNode *left = node_stack[node_top--];

	node_stack[++node_top] = makeRootNode(op_stack[op_top--], left, right);
}

treeNode *makeTree(char str[]) {
	for (int i = 0; i < strlen(str); i++) {
		char c = str[i];

		if (c == '*' || c == '/' || c == '(') {
			op_stack[++op_top] = c;
		}
		else if (c == '+' || c == '-') {
			if (op_top > -1 && priority(c) > priority(op_stack[op_top])) {
				while (op_top > -1 && op_stack[op_top] != '(') {
					connectNode();
				}
			}
			op_stack[++op_top] = c;
		}
		else if (c == ')') {
			while (op_stack[op_top] != '(') {
				connectNode();
			}
			op_top--;
		}
		else {
			node_stack[++node_top] = makeRootNode(c, NULL, NULL);
		}
	}

	while (op_top > -1) {
		connectNode();
	}
	return node_stack[0];
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
	char str[40];

	printf("식 입력: ");
	scanf_s("%s", str, STACK_SIZE * 2);

	treeNode *root = makeTree(str);

	printf("전위: ");
	preorder(root);
	printf("\n");

	printf("중위: ");
	inorder(root);
	printf("\n");

	printf("후위: ");
	postorder(root);
	printf("\n");
}