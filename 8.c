#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef _node;
typedef struct _node* nodePosition;

typedef struct _node
{
	int value;
	nodePosition leftChild;
	nodePosition rightChild;
}node;

nodePosition find(int toFind, nodePosition rootPos);
nodePosition add(int newValue, nodePosition rootPos);
nodePosition newNode(int newValue);
nodePosition deleteNode(nodePosition root, int value);

void preorder(nodePosition rootPos);
void inorder(nodePosition rootPos);
void postorder(nodePosition rootPos);

int levelOrder(node* root);

int main()
{
	nodePosition rootPosition = NULL;

	rootPosition = add(5, rootPosition);
	rootPosition = add(2, rootPosition);
	rootPosition = add(8, rootPosition);

	deleteNode(rootPosition, 5); 
	preorder(rootPosition);

	printf("\n"); 
	inorder(rootPosition); 

	printf("\n"); 
	postorder(rootPosition); 

	printf("\n");
	levelOrder(rootPosition);

	return 0;
}

nodePosition find(int toFind, nodePosition rootPos)
{
	if (rootPos == NULL) {
		return NULL;
	}
	else if (toFind < rootPos->value)
	{
		find(toFind, rootPos->leftChild);
	}
	else if (toFind > rootPos->value)
	{
		find(toFind, rootPos->rightChild);
	}
	else
	{
		return rootPos;
	}
}

nodePosition add(int newValue, nodePosition rootPos)
{
	if (rootPos == NULL) {
		return newNode(newValue); //had before as rootPos = newNode(newValue);, why is that wrong?
	}
	else if (newValue <= rootPos->value) {
		rootPos->leftChild = add(newValue, rootPos->leftChild);
	}
	else if (newValue > rootPos->value) {
		rootPos->rightChild = add(newValue, rootPos->rightChild);
	}
	return rootPos;
}

nodePosition newNode(int newValue)
{
	nodePosition newNode = (nodePosition)malloc(sizeof(node));
	if (newNode == NULL) {
		printf("Unable to allocate memory\n");
		return NULL;
	}
	newNode->value = newValue;
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
}

nodePosition deleteNode(nodePosition root, int value)
{
	if (root == NULL) {
		return root; 
	}

	if (value < root->value) {
		root->leftChild = deleteNode(root->leftChild, value); 
	}
	else if (value > root->value) {
		root->rightChild = deleteNode(root->rightChild, value); 
	}
	else {
		//0 or 1 child
		if (root->leftChild == NULL) {
			nodePosition temp = root->rightChild; 
			free(root); 
			return temp; 
		}
		else if (root->rightChild == NULL) {
			nodePosition temp = root->leftChild; 
			free(root); 
			return temp; 
		}

		//2 children
		nodePosition temp = root->rightChild; 
		while (temp->leftChild != NULL) {
			temp = temp->leftChild; 
		}

		root->value = temp->value; 
		root->rightChild = deleteNode(root->rightChild, temp->value); 
	}
	return root;
}

void preorder(nodePosition rootPos) //still not working properly 
{
	if (rootPos != NULL) {
		printf("%d\n", rootPos->value);

		preorder(rootPos->leftChild);
		preorder(rootPos->rightChild);
	}
}

void inorder(nodePosition rootPos)
{
	if (rootPos != NULL) {
		inorder(rootPos->leftChild);
		printf("%d\n", rootPos->value);
		inorder(rootPos->rightChild);
	}
}

void postorder(nodePosition rootPos)
{
	if (rootPos != NULL) {
		postorder(rootPos->leftChild);
		postorder(rootPos->rightChild);
		printf("%d\n", rootPos->value);
	}

}

int levelOrder(node* root) {
	if (root == NULL)
		return;

	node* queue[100] = { 0 };
	int front = 0, rear = 0;

	queue[rear++] = root;

	while (front < rear) {
		node* current = queue[front++];

		printf("%d ", current->value);

		if (current->leftChild != NULL)
			queue[rear++] = current->leftChild;

		if (current->rightChild != NULL)
			queue[rear++] = current->rightChild;
	}
	return 0;
}
