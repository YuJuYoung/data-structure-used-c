#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct treeNode {
	element key;
	struct treeNode *left, *right;
} treeNode;

void searchBST(treeNode* root, element x) {
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
	printf(p ? "%d번째 성공" : "%d번째 실패", count);
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
		printf("같은 키 있음\n");
	}
	return p;
}
/*treeNode* deleteNode(treeNode *root, element x) {
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
		printf("키 없음\n");
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
}*/

treeNode* deleteNode(treeNode *p, element x) {
	if (!p) {
		printf("키 없음\n");
	}
	else {
		if (x < p->key) {
			p->left = deleteNode(p->left, x);
		}
		else if (x > p->key) {
			p->right = deleteNode(p->right, x);
		}
		else {
			treeNode *old = p;

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
			free(old);
		}
	}
	return p;
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
	char choice;
	int num;

	while (1) {
		printf("\n1 삽입 2 삭제 3 키 찾기 5 종료: ");
		scanf_s(" %c", &choice);

		switch (choice - '0')
		{
		case 1:
			printf("수 입력: ");
			scanf_s("%d", &num);
			root = insertNode(root, num);
			printTree(root);
			break;
		case 2:
			printf("수 입력: ");
			scanf_s("%d", &num);
			root = deleteNode(root, num);
			printTree(root);
			break;
		case 3:
			printf("수 입력: ");
			scanf_s("%d", &num);
			searchBST(root, num);
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}