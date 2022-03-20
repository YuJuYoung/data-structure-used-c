#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

treeNode *initRootNode(char a, char op, char b) {
	treeNode *left = makeRootNode(a, NULL, NULL);
	treeNode *right = makeRootNode(b, NULL, NULL);
	treeNode *root = makeRootNode(op, left, right);

	return root;
}

treeNode *makeTree(char str[]) {
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
	scanf_s("%s", str, 40);

	treeNode *root = makeTree(str);

	preorder(root);
	printf("\n");

	inorder(root);
	printf("\n");

	postorder(root);
	printf("\n");
}