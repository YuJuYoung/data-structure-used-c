#include <stdio.h>
#include <malloc.h>

typedef char element;
typedef struct Node {
	element data;
	struct Node *link;
} Node;

typedef struct {
	Node *front, *rear;
} QType;

QType *createQueue() {
	QType *Q = (QType *)malloc(sizeof(QType));

	Q->front = Q->rear = NULL;
	return Q;
}

int isEmpty(QType *Q) {
	return Q->front == NULL;
}

void add(QType *Q, element data) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	newNode->link = NULL;

	if (isEmpty(Q)) {
		Q->front = Q->rear = newNode;
	}
	else {
		Q->rear->link = newNode;
		Q->rear = newNode;
	}
}

element poll(QType *Q) {
	if (isEmpty(Q)) {
		return 0;
	}
	Node *old = Q->front;
	element data = old->data;

	if (Q->front->link == NULL) {
		Q->front = Q->rear = NULL;
	}
	else {
		Q->front = Q->front->link;
	}
	free(old);

	return data;
}

void printQ(QType *Q) {
	Node *temp = Q->front;
	printf("[");

	while (temp) {
		printf("%2c", temp->data);
		temp = temp->link;
	}
	printf(" ]\n");
}

void main() {
	QType *Q = createQueue();
	int input;

	while (1) {
		printf("1. 삽입, 2. 추출, 3. 끝내기: ");
		scanf_s("%d", &input);

		if (input == 1) {
			element data;

			printf("문자 입력: ");
			scanf_s(" %c", &data);

			add(Q, data);
			printQ(Q);
		}
		else if (input == 2) {
			element data = poll(Q);

			if (data) {
				printf("삭제한 원소: %c\n", data);
				printQ(Q);
			}
			else {
				printf("비어있음\n");
			}
		}
		else if (input == 3) {
			break;
		}
		else {
			printf("다시 입력\n");
		}
		printf("----------------------\n");
	}
}