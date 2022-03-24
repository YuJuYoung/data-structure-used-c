#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct treeNode {
	int size;
	struct treeNode *left;
	struct treeNode *right;
} treeNode;

int FolderSize;

treeNode *makeRootNode(int size, treeNode* leftNode, treeNode* rightNode) {
	treeNode* root = (treeNode *)malloc(sizeof(treeNode));
	root->size = size;
	root->left = leftNode;
	root->right = rightNode;
	return root;
}

int postorder_FolderSize(treeNode* root) {
	if (root) {
		postorder_FolderSize(root->left);
		postorder_FolderSize(root->right);
		FolderSize += root->size;
	}
	return FolderSize;
}

int inorder_FolderSize(treeNode* root) {
	if (root) {
		inorder_FolderSize(root->left);
		FolderSize += root->size;
		inorder_FolderSize(root->right);
	}
	return FolderSize;
}

int preorder_FolderSize(treeNode* root) {
	if (root) {
		FolderSize += root->size;
		preorder_FolderSize(root->left);
		preorder_FolderSize(root->right);
	}
	return FolderSize;
}

void main() {
	treeNode* F11 = makeRootNode(120, NULL, NULL);
	treeNode* F10 = makeRootNode(55, NULL, NULL);
	treeNode* F9 = makeRootNode(100, NULL, NULL);
	treeNode* F8 = makeRootNode(200, NULL, NULL);
	treeNode* F7 = makeRootNode(68, F10, F11);
	treeNode* F6 = makeRootNode(40, NULL, NULL);
	treeNode* F5 = makeRootNode(15, NULL, NULL);
	treeNode* F4 = makeRootNode(2, F8, F9);
	treeNode* F3 = makeRootNode(10, F6, F7);
	treeNode* F2 = makeRootNode(0, F4, F5);
	treeNode* F1 = makeRootNode(0, F2, F3);

	printf("C:\\의 용량\n");
	FolderSize = 0;
	printf("전위: %d M\n", preorder_FolderSize(F2));
	FolderSize = 0;
	printf("중위: %d M\n", inorder_FolderSize(F2));
	FolderSize = 0;
	printf("후위: %d\ M\n\n", postorder_FolderSize(F2));

	printf("D:\\의 용량\n");
	FolderSize = 0;
	printf("전위: %d M\n", preorder_FolderSize(F3));
	FolderSize = 0;
	printf("중위: %d M\n", inorder_FolderSize(F3));
	FolderSize = 0;
	printf("후위: %d M\n\n", postorder_FolderSize(F3));

	printf("전체 용량\n");
	FolderSize = 0;
	printf("전위: %d M\n", preorder_FolderSize(F1));
	FolderSize = 0;
	printf("중위: %d M\n", inorder_FolderSize(F1));
	FolderSize = 0;
	printf("후위: %d M", postorder_FolderSize(F1));
}