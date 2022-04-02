#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define MAX(a, b) (a > b ? a : b)

typedef int element;
typedef struct treeNode {
	element key;
	struct treeNode *left, *right;
} treeNode;

treeNode* LL_rotate(treeNode *parent) {
	treeNode *child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child;
}

treeNode* RR_rotate(treeNode *parent) {
	treeNode *child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

treeNode* LR_rotate(treeNode *p) {
	p->left = RR_rotate(p->left);

	return LL_rotate(p);
}

treeNode* RL_rotate(treeNode *p) {
	p->right = LL_rotate(p->right);

	return RR_rotate(p);
}

int getHeight(treeNode *p) {
	if (!p) {
		return 0;
	}
	return MAX(getHeight(p->left), getHeight(p->right)) + 1;
}

int getBF(treeNode *p) {
	return p ? getHeight(p->left) - getHeight(p->right) : 0;
}

treeNode* rebalance(treeNode *p) {
	int BF = getBF(p);

	if (BF > 1) {
		if (getBF(p->left) > 0) {
			p = LL_rotate(p);
		}
		else {
			p = LR_rotate(p);
		}
	}
	if (BF < -1) {
		if (getBF(p->right) < 0) {
			p = RR_rotate(p);
		}
		else {
			p = RL_rotate(p);
		}
	}
	return p;
}

treeNode* insert_AVL_Node(treeNode *p, element x) {
	if (!p) {
		treeNode *newNode = (treeNode *)malloc(sizeof(treeNode));
		newNode->key = x;
		newNode->left = newNode->right = NULL;

		return newNode;
	}

	if (x < p->key) {
		p->left = insert_AVL_Node(p->left, x);
		p = rebalance(p);
	}
	else if (x > p->key) {
		p->right = insert_AVL_Node(p->right, x);
		p = rebalance(p);
	}
	else {
		printf("이미 있음");
	}
	return p;
}

void searchTree(treeNode *root, element x) {
	treeNode *p = root;
	int count = 1;

	while (p && x != p->key) {
		if (x < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
		count++;
	}
	printf((p ? "%d번째 성공" : "%d번째 실패"), count);
	printf("\n");
}

void printTree(treeNode *root) {
	if (root) {
		printTree(root->left);
		printf("%d ", root->key);
		printTree(root->right);
	}
}

void main() {
	treeNode *AVL = NULL;
	int choice, key;

	while (1) {
		printf("1 삽입 2 탐색 3 트리 출력 4 종료: ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("수 입력: ");
			scanf_s("%d", &key);
			AVL = insert_AVL_Node(AVL, key);
			break;
		case 2:
			printf("수 입력: ");
			scanf_s("%d", &key);
			searchTree(AVL, key);
			break;
		case 3:
			printTree(AVL);
			printf("\n");
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}