#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct treeNode {
	element key;
	struct treeNode *left, *right;
} treeNode;

void searchBST(treeNode* root, element x) {
	treeNode *p = root;

	while (p && x != p->key) {
		if (x < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	printf(p ? "ã��" : "Ű ����");
	printf("\n");
}

treeNode* insertNode(treeNode *p, element x) {
	if (!p) {
		treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
		newNode->key = x;
		newNode->left = newNode->right = NULL;

		return newNode;
	}
	else if (x < p->key) {
		p->left = insertNode(p->left, x);
	}
	else if (x > p->key) {
		p->right = insertNode(p->right, x);
	}
	else {
		printf("���� Ű ����\n");
	}
	return p;
}

treeNode* deleteNode(treeNode *root, element x) {
	treeNode *parent = NULL, *p = root;
	int isLeft = 0;

	while (p && p->key != x) {
		parent = p;
		
		if (x < p->key) {
			p = p->left;
			isLeft = 1;
		}
		else {
			p = p->right;
			isLeft = 0;
		}
	}

	if (!p) {
		printf("Ű ����\n");
	}
	else {
		treeNode* old = p;

		if (!p->left && !p->right) {
			p = NULL;
			free(old);
		}
		else if (p->left && p->right) {
			treeNode *pp = p->left;
			treeNode *pp_parent = NULL;

			while (pp->right) {
				parent = pp;
				pp = pp->right;
			}
			p->key = pp->key;

			if (pp_parent) {
				pp_parent->right = pp->left;
			}
			else {
				p->left = pp->left;
			}
			free(pp);
		}
		else if (p->left) {
			p = p->left;
			free(old);
		}
		else {
			p = p->right;
			free(old);
		}

		if (!parent) {
			root = p;
		}
		else {
			if (isLeft) {
				parent->left = p;
			}
			else {
				parent->right = p;
			}
		}
	}
	return root;
}

void printTree(treeNode* root) {
	if (root) {
		printTree(root->left);
		printf("%d ", root->key);
		printTree(root->right);
	}
}

void main() {
	treeNode *root = NULL;
	int choice, num;

	while (1) {
		printf("1 ���� 2 ���� 3 Ű ã�� 4 Ʈ�� ��� 5 ����: ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("�� �Է�: ");
			scanf_s("%d", &num);
			root = insertNode(root, num);
			break;
		case 2:
			printf("�� �Է�: ");
			scanf_s("%d", &num);
			root = deleteNode(root, num);
			break;
		case 3:
			printf("�� �Է�: ");
			scanf_s("%d", &num);
			searchBST(root, num);
			break;
		case 4:
			printTree(root);
			printf("\n");
			break;
		case 5:
			return;
		default:
			break;
		}
	}
}