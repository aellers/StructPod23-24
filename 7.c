#define _CRT_SECURE_NO_WARNINGS
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
int goToParent(stackPosition stackHead, treePosition* currentDirectoryPtr);

//functions for stack
int push(stackPosition head, treePosition directoryAddress); 
treePosition pop(stackPosition head); 

//user interface
//not finished
int menu(treePosition treeHead, stackPosition stackHead, treePosition* currentDirectoryPtr);
int listChildren(treePosition currentDirectory);
treePosition findChild(treePosition currentDirectory, char* dirToFind); 
int listCurrentDir(treePosition currentDirectory);

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

int goToParent(stackPosition stackHead, treePosition* currentDirectoryPtr)
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
	char dirName[64] = { 0 };
	int numRead = 0; 
	treePosition newDirPosition = NULL; 

	int userChoice = 0; 
	int continueLoop = 1; 
	while (continueLoop)
	{
		printf("choose a command: \n"); 
		printf("1 - md\n2 - cd dir\n3 - cd..\n4 - dir\n5 - exit\n"); 
		scanf_s("%d", &userChoice); 
		switch (userChoice) 
		{
		case 1: 
			printf("Enter directory name: "); 
			numRead = scanf(" %65s", dirName); 
			if (numRead != 1) {
				continue;
			}
			addChild(*currentDirectoryPtr, dirName); 
			break; 
		case 2: //infinite loop for some reason?
			//enter name
			printf("Enter directory name: ");
			numRead = scanf(" %65s", dirName);
			
			//find directory with that name 
			//go to that directory
			newDirPosition = findChild(*currentDirectoryPtr, dirName); 
			push(stackHead, *currentDirectoryPtr); 
			*currentDirectoryPtr = newDirPosition; 
			break;
		case 3: 
			if (*currentDirectoryPtr != treeHead->firstChild) {
				goToParent(stackHead, currentDirectoryPtr);
			}
			break; 
		case 4: 
			//output current directory's children
			listChildren(*currentDirectoryPtr); 
			break; 
		case 5:
			continueLoop = 0;
			break;
		case 6: 
			listCurrentDir(*currentDirectoryPtr); //can be an error here but idk what it is
			break; 
		default:
			printf("Invalid input, please try again\n");
			break;
		}
			
	}
	return 0;
}

int listChildren(treePosition currentDirectory)
{
	treePosition position = currentDirectory->firstChild;
	if (position == NULL) {
		printf("Empty directory\n"); 
		return 0; 
	}
	printf("\n"); 
	while (position != NULL) {
		printf("%s\n", position->name); 
		position = position->nextSibling;
	}

	return 0;
}

treePosition findChild(treePosition currentDirectory, char* dirToFind)
{
	treePosition position = currentDirectory->firstChild;

	while ((position != NULL) && (strcmp(position->name, dirToFind) != 0)) {
		position = position->nextSibling;
	}

	if (position == NULL) {
		printf("Unable to find directory with name %s\n", dirToFind); 
	}
	return position;
}

int listCurrentDir(treePosition currentDirectory)
{
	printf("Current directory name: %s\n", currentDirectory->name); 
	return 0;
}
