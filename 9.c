#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct _node; 
typedef struct _node* nodePointer; 

typedef struct _node {
	int value; 
	nodePointer leftChild;
	nodePointer rightChild;
}node;

node* insert(int value, node* root); 
int replace(node* root); 
int random(); //returns pseudorandom number between 10 and 90 (incl.)

int levelOrder(node* root); //needed for 8, not 9
void inorder(node* rootPos, FILE* file); 

int main() { //still error when run but who knows what they are
	node* root = NULL; 

	node* ranRoot = NULL; 
	FILE* file = NULL; 

	//2, 5, 7, 8, 11, 1, 4, 2, 3, 7 
	insert(2, root);
	insert(5, root);
	insert(7, root);
	insert(8, root);
	insert(11, root);
	insert(1, root);
	insert(4, root);
	insert(2, root);
	insert(3, root);
	insert(7, root);

	ranRoot = insert(ranRoot, random());
	for (int i = 0; i < 10; i++) {
		insert(random(), ranRoot);
	}

	file = fopen("text.txt", "w"); 

	inorder(ranRoot, file); 
	replace(ranRoot); 
	inorder(ranRoot, file); 

	fclose(file); 


	return 0; 
}

node* insert(int value, node* root)
{
	if (root == NULL) {
		root = (node*)malloc(sizeof(node));
		if (root == NULL) {
			return NULL; 
		}
		root->value = value; 
		root->leftChild = NULL; 
		root->rightChild = NULL; 
	}
	else if (value < root->value) {
		root->rightChild = insert(value, root->rightChild); 
	}
	else if (value >= root->value) {
		root->leftChild = insert(value, root->leftChild); 
	}

	return root; 
	
}

int replace(node* root)
{
	if (root == NULL) {
		return 0; 
	}

	int leftValue = replace(root->leftChild); 
	int rightValue = replace(root->rightChild); 

	int originalValue = root->value; 

	root->value = leftValue + rightValue; 

	return originalValue + root->value;
}

int random()
{
	return rand() % 81 + 10; 
}

void inorder(node* rootPos, FILE* file)
{
	if (rootPos != NULL) {
		inorder(rootPos->leftChild, file);
		fprintf(file, "%d\n", rootPos->value); 
		inorder(rootPos->rightChild, file);
	}
}

