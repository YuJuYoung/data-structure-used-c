#include <stdio.h>
#include <stdlib.h>

typedef int element;

typedef struct treeNode {
	element key;
	int node_count;
	struct treeNode *left, *right;
} treeNode;

treeNode* insertNode(treeNode *p, element x) {
	if (!p) {
		p = (treeNode *)malloc(sizeof(treeNode));
		p->key = x;
		p->node_count = 1;
		p->left = p->right = NULL;

		return p;
	}

	int left_count = p->left ? p->left->node_count : 0;
	int right_count = p->right ? p->right->node_count : 0;

	if (left_count > right_count) {
		p->right = insertNode(p->right, x);

		if (p->key < p->right->key) {
			int temp = p->key;
			p->key = p->right->key;
			p->right->key = temp;
		}
	}
	else {
		p->left = insertNode(p->left, x);
		
		if (p->key < p->left->key) {
			int temp = p->key;
			p->key = p->left->key;
			p->left->key = temp;
		}
	}
	p->node_count++;

	return p;
}

treeNode* deleteNode(treeNode *root) {
	if (!root) {
		return NULL;
	}
	else if (!root->left && !root->right) {
		free(root);
		root = NULL;
	}
	else {
		treeNode *p = root;
		treeNode *parent = NULL;

		while (p->left || p->right) {
			parent = p;
			p = p->right ? p->right : p->left;
		}

		if (parent->left->key == p->key) {
			parent->left = NULL;
		}
		else {
			parent->right = NULL;
		}
		root->key = p->key;
		free(p);

		p = root;

		while (p->left) {
			int left = p->left->key;
			int right = p->right ? p->right->key : INT_MIN;

			if (left > right) {
				if (p->key > left) {
					break;
				}
				
				int temp = p->key;
				p->key = left;
				p->left->key = temp;

				p = p->left;
			}
			else {
				if (p->key > right) {
					break;
				}

				int temp = p->key;
				p->key = right;
				p->right->key = temp;

				p = p->right;
			}
		}
	}
	return root;
}

void main() {
	treeNode *root = NULL;
	char choice;
	int key;

	while (1) {
		printf("\n1 삽입 2 삭제 3 종료: ");
		scanf_s(" %c", &choice);

		switch (choice)
		{
		case '1':
			printf("수 입력: ");
			scanf_s("%d", &key);
			root = insertNode(root, key);
			break;
		case '2':
			if (root) {
				printf("%d", root->key);
			}
			else {
				printf("비어있음");
			}
			root = deleteNode(root);
			break;
		case '3':
			return;
		default:
			break;
		}
	}
}