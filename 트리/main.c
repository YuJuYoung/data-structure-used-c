#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define STACK_SIZE 20

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

/*
treeNode *initRootNode(char a, char op, char b) {
	treeNode *left = makeRootNode(a, NULL, NULL);
	treeNode *right = makeRootNode(b, NULL, NULL);
	treeNode *root = makeRootNode(op, left, right);

	return root;
}
*/

treeNode *makeTree(char str[]) {
	/*
	treeNode *root = initRootNode(str[0], str[1], str[2]);
	char last_op = root->data;

	for (int i = 3; i < strlen(str); i++) {
		char ch = str[i];

		if (ch == '*' || ch == '/' || ch == '+' || ch == '-') {
			last_op = ch;
		}
		else {
			treeNode *add = makeRootNode(ch, NULL, NULL);

			if (last_op == '*' || last_op == '/') {
				root->right = makeRootNode(last_op, root->right, add);
			}
			else {
				root = makeRootNode(last_op, root, add);
			}
		}
	}
	return root;
	*/

	treeNode *node_stack[STACK_SIZE];
	char op_stack[STACK_SIZE];

	int node_top = -1;
	int op_top = -1;

	for (int i = 0; i < strlen(str); i++) {
		char ch = str[i];

		if (ch == '*' || ch == '/' || ch == '(') {
			op_stack[++op_top] = ch;
		}
		else if (ch == '+' || ch == '-') {
			if (op_top != -1) {
				char last_op = op_stack[op_top];

				if (last_op == '*' || last_op == '/') {
					while (op_top > -1) {
						treeNode *right = node_stack[node_top--];
						treeNode *left = node_stack[node_top--];

						node_stack[++node_top] = makeRootNode(op_stack[op_top--], left, right);
					}
				}
			}
			op_stack[++op_top] = ch;
		}
		else if (ch == ')') {
			while (op_stack[op_top] != '(') {
				treeNode *right = node_stack[node_top--];
				treeNode *left = node_stack[node_top--];

				node_stack[++node_top] = makeRootNode(op_stack[op_top--], left, right);
			}
			op_top--;
		}
		else {
			node_stack[++node_top] = makeRootNode(ch, NULL, NULL);
		}
	}

	while (op_top > -1) {
		treeNode *right = node_stack[node_top--];
		treeNode *left = node_stack[node_top--];

		node_stack[++node_top] = makeRootNode(op_stack[op_top--], left, right);
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

	printf("╫д ют╥б: ");
	scanf_s("%s", str, STACK_SIZE * 2);

	treeNode *root = makeTree(str);

	preorder(root);
	printf("\n");

	inorder(root);
	printf("\n");

	postorder(root);
	printf("\n");
}