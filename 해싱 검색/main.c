#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char element;

typedef struct Node {
	char data;
	struct Node *next;
} Node;

Node store[5];

Node* getNewNode(element data) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

int toHashCode(char c) {
	return c % 5;
}

void insert(element data) {
	Node *newNode = getNewNode(data);
	int hashCode = toHashCode(data);

	newNode->next = &store[hashCode];
	store[hashCode] = *newNode;
}

void search(element data) {
	int hashCode = toHashCode(data);
	Node *node = &store[hashCode];

	while (node != NULL) {
		if (node->data == data) {
			printf("�˻� ����\n\n");
			return;
		}
		node = node->next;
	}

	printf("�˻� ����\n\n");
}

void main() {
	int selector;
	char input;

	while (TRUE) {
		printf("1 ����, 2 �˻�, 3 ����: ");
		scanf_s("%d", &selector);
		getchar();

		switch (selector) {
		case 1:
			printf("������ ����: ");
			scanf_s("%c", &input);
			insert(input);
			break;
		case 2:
			printf("�˻��� ����: ");
			scanf_s("%c", &input);
			search(input);
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}