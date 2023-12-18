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

void preorder(nodePosition rootPos); 
void inorder(nodePosition rootPos);
void postorder(nodePosition rootPos); 

int main()
{
	nodePosition rootPosition = NULL; 
	//still issues here
	rootPosition = add(5, rootPosition);
	rootPosition = add(2, rootPosition);
	rootPosition = add(8, rootPosition);

	preorder(rootPosition); 

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
	else if (newValue < rootPos->value) {
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
	newNode->value = newValue;
	newNode->leftChild = NULL; 
	newNode->rightChild = NULL; 
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
		preorder(rootPos->leftChild);
		printf("%d\n", rootPos->value);
		preorder(rootPos->rightChild);
	}
}

void postorder(nodePosition rootPos)
{
	if (rootPos != NULL) {
		preorder(rootPos->leftChild);
		preorder(rootPos->rightChild);
		printf("%d\n", rootPos->value);
	}

}

