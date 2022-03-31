#include <stdio.h>
#include <stdlib.h>

typedef char element;
typedef struct treeNode {
	char key;
	struct treeNode *left, *right;
} treeNode;

treeNode *searchBST(treeNode *root, char x) {
	treeNode *p = root;

	while (p != NULL) {
		if (p->key == x) {
			return p;
		}

		if (x < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	printf("\n 키가 없음.");
	return p;
}

treeNode *insertNode(treeNode *p, char x) {
	treeNode *newNode;

	if (p == NULL) {
		newNode = (treeNode *)malloc(sizeof(treeNode));
		newNode->key = x;
		newNode->left = NULL;
		newNode->right = NULL;
		
		return newNode;
	}
	else if (x < p->key) {
		p->left = insertNode(p->left, x);
	}
	else if (x > p->key) {
		p->right = insertNode(p->right, x);
	}
	else {
		printf("\n 이미 같은 키 있음.");
	}
	return p;
}

void deleteNode(treeNode *root, element key) {
	treeNode *parent, *p, *succ, *succ_parent;
	treeNode *child;

	parent = NULL;
	p = root;

	while ((p != NULL) && (p->key != key)) {
		parent = p;
		
		if (key < p->key) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	if (p == NULL) {
		printf("\n 트리에 없음.");
		return;
	}

	if ((p->left == NULL) && (p->right == NULL)) {
		if (parent != NULL) {
			if (parent->left == p) {
				parent->left = NULL;
			}
			else {
				parent->right = NULL;
			}
		}
		else {
			root = NULL;
		}
	}
	else if ((p->left == NULL) || (p->right == NULL)){
		if (p->left != NULL) {
			child = p->left;
		}
		else {
			child = p->right;
		}

		if (parent != NULL) {
			if (parent->left == p) {
				parent->left = child;
			}
			else {
				parent->right = child;
			}
		}
		else {
			root = child;
		}
	}
	else {
		succ_parent = p;
		succ = p->left;

		while (succ->right != NULL) {
			succ_parent = succ;
			succ = succ->right;
		}

		if (succ_parent->left == succ) {
			succ_parent->left = succ->left;
		}
		else {
			succ_parent->right = succ->left;
		}
		p->key = succ->key;
		p = succ;
	}
	free(p);
}

void displayInorder(treeNode *root) {
	if (root) {
		displayInorder(root->left);
		printf("%c_", root->key);
		displayInorder(root->right);
	}
}

void menu() {
	printf("\n---------------------");
	printf("\n1 : 트리 출력");
	printf("\n2 : 문자 삽입");
	printf("\n3 : 문자 삭제");
	printf("\n4 : 문자 검색");
	printf("\n5 : 종료");
	printf("\n---------------------");
	printf("\n메뉴 입력 >> ");
}

void main() {
	treeNode* root = NULL;
	treeNode* foundedNode = NULL;
	char choice, key;

	root = insertNode(root, 'G');
	insertNode(root, 'I');
	insertNode(root, 'H');
	insertNode(root, 'D');
	insertNode(root, 'B');
	insertNode(root, 'M');
	insertNode(root, 'N');
	insertNode(root, 'A');
	insertNode(root, 'J');
	insertNode(root, 'E');
	insertNode(root, 'Q');

	while (1) {
		menu();
		scanf_s(" %c", &choice);

		switch (choice - '0') {
		case 1: printf("[이진 트리 출력] ");
			displayInorder(root);
			printf("\n");
			break;
		case 2: printf("삽입할 문자: ");
			scanf_s(" %c", &key);
			insertNode(root, key);
			break;
		case 3: printf("삭제할 문자: ");
			scanf_s(" %c", &key);
			deleteNode(root, key);
			break;
		case 4: printf("찾을 문자 입력: ");
			scanf_s(" %c", &key);
			foundedNode = searchBST(root, key);

			if (foundedNode != NULL) {
				printf("\n%c", foundedNode->key);
			}
			else {
				printf("\n 못찾음");
			}
			break;
		case 5:
			return;
		default:
			printf("다시");
		}
	}
}