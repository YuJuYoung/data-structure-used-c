#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef char element;

typedef struct Node {
	char data;
	struct Node *next;
} Node;

Node* bucket[5];

Node* getNewNode(element data) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

int toHashCode(char c) {
	return c % 5;
}

int search(element data) {
	int hashCode = toHashCode(data);
	Node *node = bucket[hashCode];

	while (node != NULL) {
		if (node->data == data) {
			return TRUE;
		}
		node = node->next;
	}
	return FALSE;
}

int insert(element data) {
	Node *newNode = getNewNode(data);
	int hashCode = toHashCode(data);

	if (search(data)) {
		printf("이미 값이 있음\n\n");
		return 0;
	}
	else {
		newNode->next = bucket[hashCode];
		bucket[hashCode] = newNode;
	}
	return 1;
}

void delete(element data) {
	int hashCode = toHashCode(data);

	Node *node = bucket[hashCode];
	Node *last = NULL;

	while (node != NULL) {
		if (node->data == data) {
			if (last == NULL) {
				bucket[hashCode] = node->next;
			}
			else {
				last->next = node->next;
			}

			free(node);
			printf("%c 제거 완료\n\n", data);
			return;
		}
		last = node;
		node = node->next;
	}
	printf("값이 없음\n\n");
}

void printStore() {
	for (int i = 0; i < 5; i++) {
		printf("Bucket[%d]: [ ", i);

		Node *node = bucket[i];

		while (node != NULL) {
			printf("%c ", node->data);
			node = node->next;
		}
		printf("]\n");
	}
	printf("\n");
}

void main() {
	int selector;
	char input;

	while (TRUE) {
		printf("1 삽입, 2 검색, 3: 삭제, 4 종료: ");
		scanf_s("%d", &selector);
		getchar();
		printf("\n");

		switch (selector) {
		case 1:
			printf("삽입할 문자: ");
			scanf_s("%c", &input);
			printf("\n");

			if (insert(input)) {
				printStore();
			}
			break;
		case 2:
			printf("검색할 문자: ");
			scanf_s("%c", &input);
			printf("\n");

			printf(search(input) ? "검색 성공" : "검색 실패");
			printf("\n\n");
			break;
		case 3:
			printf("삭제할 문자: ");
			scanf_s("%c", &input);
			printf("\n");

			delete(input);
			printStore();
			break;
		case 4:
			return;
		default:
			break;
		}
	}
}