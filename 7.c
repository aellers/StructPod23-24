#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct _treeElement;
typedef struct _treeElement* treePosition;

typedef struct _treeElement
{
	char name[64];
	treePosition nextSibling;
	treePosition firstChild;

}treeElement;

struct _stackElement;
typedef struct _stackElement* stackPosition;

typedef struct _stackElement
{
	treePosition directory;
	stackPosition next;
}stackElement;

//functions for tree
int addSibling(treePosition element, char* newSiblingName);
int addChild(treePosition element, char* newChildName); 
treePosition createTreeElement(char* newElementName);

//both
//having both treePosition element and treePosition* currentDirectoryPtr isn't necessary (but it sorta makes sense?)
int goToFirstChild(treePosition element, stackPosition stackHead, treePosition* currentDirectoryPtr); 
int goToNextSibling(treePosition element, treePosition* currentDirectoryPtr);
int goToParent(treePosition element, stackPosition stackHead, treePosition* currentDirectoryPtr);

//functions for stack
int push(stackPosition head, treePosition directoryAddress); 
treePosition pop(stackPosition head); 

//user interface
//not finished
int menu(treePosition treeHead, stackPosition stackHead, treePosition* currentDirectoryPtr);

int main()
{
	treeElement treeHead = { .name = "", .nextSibling = NULL, .firstChild = NULL };
	treePosition currentDirectory = &treeHead; //when changes should put on stack (if in "forward" direction)


	stackElement stackHead = { .directory = NULL, .next = NULL };


	addChild(&treeHead, "root");
	currentDirectory = treeHead.firstChild;

	menu(&treeHead, &stackHead, &currentDirectory); //doesn't seem to work
	
	return 0;
}

int addSibling(treePosition element, char* newSiblingName)
{
	treePosition temp = element->nextSibling;
	treePosition newElement = createTreeElement(newSiblingName);

	if (newElement == NULL) {
		return EXIT_FAILURE;
	}

	element->nextSibling = newElement;
	newElement->nextSibling = temp;

	return 0;
}

int addChild(treePosition element, char* newChildName) {
	treePosition temp = element->firstChild;
	treePosition newElement = createTreeElement(newChildName); 

	if (newElement == NULL) {
		return EXIT_FAILURE;
	}

	element->firstChild = newElement;
	newElement->nextSibling = temp;
	return 0; 
}

treePosition createTreeElement(char* newElementName)
{
	treePosition newElement = (treePosition)malloc(sizeof(treeElement));
	if (newElement == NULL) {
		return NULL; //unable to allocate memory
	}
	//strcpy_s(newElement->name, newElementName); 
	strcpy_s(newElement->name, sizeof(newElement->name), newElementName);
	newElement->nextSibling = NULL;
	newElement->firstChild = NULL;
	return newElement;
}

int goToFirstChild(treePosition element, stackPosition stackHead, treePosition* currentDirectoryPtr) //not yet implemented
{
	treePosition currentDir = element; //at moment before run
	treePosition childDir = element->firstChild;
	push(stackHead, currentDir);
	*currentDirectoryPtr = childDir;
	return 0;
}

int goToNextSibling(treePosition element, treePosition* currentDirectoryPtr)
{
	if (element->nextSibling == NULL) {
		return EXIT_FAILURE;
	}

	*currentDirectoryPtr = element->nextSibling;
	return 0;
}

int goToParent(treePosition element, stackPosition stackHead, treePosition* currentDirectoryPtr)
{
	treePosition parent = NULL; 
	parent = pop(stackHead); 

	if (parent == NULL) {
		return EXIT_FAILURE;
	}

	*currentDirectoryPtr = parent;

	return 0;
}

int push(stackPosition head, treePosition directoryAddress)
{
	stackPosition temp = head->next;
	stackPosition newElement = (stackPosition)malloc(sizeof(stackElement));

	if (newElement == NULL) {
		return EXIT_FAILURE;
	}
	newElement->directory = directoryAddress;

	head->next = newElement;
	newElement->next = temp;
	
	return 0;
}

treePosition pop(stackPosition head)
{
	stackPosition temp = NULL;
	treePosition directoryAddress = NULL;
	if (head->next == NULL) {
		return NULL;
	}
	temp = head->next->next;
	directoryAddress = head->next->directory;
	free(head->next); 
	head->next = temp;
	return directoryAddress;
}

int menu(treePosition treeHead, stackPosition stackHead, treePosition* currentDirectoryPtr) //not yet implemented
{
	int userChoice = 0; 
	int continueLoop = 1; 
	while (continueLoop)
	{
		printf("choose a command: \n"); 
		printf("1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 - exit\n"); 
		scanf_s("%d", &userChoice); 
		switch (userChoice) 
		{
			case 5:
				continueLoop = 0;
				break;
			default:
				printf("Invalid input, please try again\n");
				break;
		}
			
	}
	return 0;
}

