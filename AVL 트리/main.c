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

treeNode* insertNode(treeNode *p, element x) {
	if (!p) {
		p = (treeNode *)malloc(sizeof(treeNode));
		p->key = x;
		p->left = p->right = NULL;
	}
	else {
		if (x < p->key) {
			p->left = insertNode(p->left, x);
			p = rebalance(p);
		}
		else if (x > p->key) {
			p->right = insertNode(p->right, x);
			p = rebalance(p);
		}
		else {
			printf("같은 키 존재\n");
			exit(1);
		}
	}
	return p;
}

treeNode* deleteNode(treeNode *p, element x) {
	if (!p) {
		printf("키 없음\n");
		exit(1);
	}
	else {
		if (x < p->key) {
			p->left = deleteNode(p->left, x);
			p = rebalance(p);
		}
		else if (x > p->key) {
			p->right = deleteNode(p->right, x);
			p = rebalance(p);
		}
		else {
			treeNode *target = p;

			if (!p->left && !p->right) {
				p = NULL;
			}
			else if (p->left && p->right) {
				treeNode *pp = p->left;
				treeNode *pp_parent = NULL;

				while (pp->right) {
					pp_parent = pp;
					pp = pp->right;
				}

				if (pp_parent) {
					pp_parent->right = pp->left;
					pp->left = p->left;
				}
				pp->right = p->right;
				p = pp;
			}
			else {
				p = p->left ? p->left : p->right;
			}
			free(target);
		}
	}
	return p;
}

void searchTree(treeNode *p, element x) {
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
	printf(p ? "%d번째 찾음" : "%d번째 실패", count);
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
	treeNode *root = NULL;
	char choice;
	int num;

	while (1) {
		printf("\n1 삽입 2 삭제 3 키 찾기 4 종료: ");
		scanf_s(" %c", &choice);

		switch (choice)
		{
		case '1':
			printf("수 입력: ");
			scanf_s("%d", &num);
			root = insertNode(root, num);
			printTree(root);
			break;
		case '2':
			printf("수 입력: ");
			scanf_s("%d", &num);
			root = deleteNode(root, num);
			printTree(root);
			break;
		case '3':
			printf("수 입력: ");
			scanf_s("%d", &num);
			searchTree(root, num);
			break;
		case '4':
			return;
		default:
			break;
		}
	}
}