#include <stdio.h>
#include <malloc.h>

typedef char element;
typedef struct Node {
	element data;
	struct Node *llink, *rlink;
} Node;

typedef struct {
	Node *front, *rear;
} DQType;

DQType *createDQ() {
	DQType *DQ = (DQType *)malloc(sizeof(DQType));

	DQ->front = DQ->rear = NULL;
	return DQ;
}

int isEmpty(DQType *DQ) {
	return DQ->front == NULL;
}

void addFront(DQType *DQ, element data) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;
	
	if (isEmpty(DQ)) {
		newNode->llink = newNode->rlink = NULL;
		DQ->front = DQ->rear = newNode;
	}
	else {
		newNode->llink = NULL;
		newNode->rlink = DQ->front;
		DQ->front->llink = newNode;
		DQ->front = newNode;
	}
}

void addRear(DQType *DQ, element data) {
	Node *newNode = (Node *)malloc(sizeof(Node));

	newNode->data = data;

	if (isEmpty(DQ)) {
		newNode->llink = newNode->rlink = NULL;
		DQ->front = DQ->rear = newNode;
	}
	else {
		newNode->rlink = NULL;
		newNode->llink = DQ->rear;
		DQ->rear->rlink = newNode;
		DQ->rear = newNode;
	}
}

element pollFront(DQType *DQ) {
	if (isEmpty(DQ)) {
		return 0;
	}
	Node *old = DQ->front;
	element data = old->data;

	if (DQ->front->rlink == NULL) {
		DQ->front = DQ->rear = NULL;
	}
	else {
		DQ->front = DQ->front->rlink;
		DQ->front->llink = NULL;
	}
	free(old);

	return data;
}

element pollRear(DQType *DQ) {
	if (isEmpty(DQ)) {
		return 0;
	}
	Node *old = DQ->rear;
	element data = old->data;

	if (DQ->rear->llink == NULL) {
		DQ->front = DQ->rear = NULL;
	}
	else {
		DQ->rear = DQ->rear->llink;
		DQ->rear->rlink = NULL;
	}
	free(old);

	return data;
}

void printDQ(DQType *DQ) {
	Node *temp = DQ->front;
	printf("[");

	while (temp) {
		printf("%2c", temp->data);
		temp = temp->rlink;
	}
	printf(" ]\n");
}

void main() {
	DQType *DQ = createDQ();
	int input;

	while (1) {
		printf("1. front 삽입, 2. rear 삽입, 3: front 삭제, 4. rear 삭제, 5. 끝내기: ");
		scanf_s("%d", &input);

		if (input == 1) {
			element data;

			printf("문자 입력: ");
			scanf_s(" %c", &data);

			addFront(DQ, data);
			printDQ(DQ);
		}
		else if (input == 2) {
			element data;

			printf("문자 입력: ");
			scanf_s(" %c", &data);

			addRear(DQ, data);
			printDQ(DQ);
		}
		else if (input == 3) {
			element data = pollFront(DQ);

			if (data) {
				printf("삭제한 원소: %c\n", data);
				printDQ(DQ);
			}
			else {
				printf("비어있음\n");
			}
		}
		else if (input == 4) {
			element data = pollRear(DQ);

			if (data) {
				printf("삭제한 원소: %c\n", data);
				printDQ(DQ);
			}
			else {
				printf("비어있음\n");
			}
		}
		else if (input == 5) {
			break;
		}
		else {
			printf("다시 입력\n");
		}
		printf("-----------------------\n");
	}
}