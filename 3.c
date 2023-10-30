#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char lastName[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

//might want to add function that puts new element in place
//change for specific thing from last name to person so we can be pretty sure
//replace other values with exit_failure if it's more obvious what it means
//what exactly is exit_failure used for

int newFirstElement(Position p, char* newName, char* newlastName, int newBirthYear); //&head
int newLastElement(Position p, char* newName, char* newlastName, int newBirthYear); //&head
int newBeforeElement(Position p, char* newName, char* newlastName, int newBirthYear, char* soughtLastName); //&head //returns error if not found
int newAfterElement(Position p, char* newName, char* newlastName, int newBirthYear, char* soughtLastName); //&head

Position createPerson(char* newName, char* newlastName, int newBirthYear);
Position findElement(Position p, char* lastName); //head.next
Position findBeforeElement(Position p, char* lastName); //&head //returns null if not found;
int deleteElement(Position p, char* lastName); //&head
int deleteAll(Position p);  //head.next
int swapElements(Position p, Position q); //two (pointers of) elements we want to swap
int findElementNum(Position p); //headnext

int bubbleSortElements(Position p); //head.next
int printList(Position p); //head.next

int writeList(Position p, char* fileName); //to file  //&head
/*
* outputs elements in file
* somewhat ambiguous cause this could be a function which reads from file and creates/adds list
*/
int readList(char* fileName);

//int menu(); //work on this later, maybe


int main() {
	Person head; //whats that .name way initialization?
	strcpy(head.name, "");
	strcpy(head.lastName, "");
	head.birthYear = 0;
	head.next = NULL;

	newFirstElement(&head, "a", "z", 2000);
	newAfterElement(&head, "b", "u", 1997, "z");
	printList(head.next);

	bubbleSortElements(head.next);
	/*

	printf("\n\nnew list\n");
	printf("element num: %d\n", findElementNum(head.next));
	*/
	//writeList(&head, "text.txt");
	//readList("text.txt"); 

	deleteAll(head.next);
	head.next = NULL; 

	return 0;
}

int newFirstElement(Position p, char* newName, char* newlastName, int newBirthYear) {
	Position newPerson = NULL;
	newPerson = createPerson(newName, newlastName, newBirthYear);
	if (!newPerson) {
		printf("Error: unable add person\n");
		return 1; //do i return 1 here or not?
	}
	newPerson->next = p->next;
	p->next = newPerson;

	return 0;
}

int newLastElement(Position p, char* newName, char* newlastName, int newBirthYear) { //&head
	Position newPerson = NULL;
	newPerson = createPerson(newName, newlastName, newBirthYear);

	while (p->next != NULL) {
		p = p->next;
	}
	p->next = newPerson;
	newPerson->next = NULL;
	return 0;
}

int newBeforeElement(Position p, char* newName, char* newlastName, int newBirthYear, char* soughtLastName) {
	Position newPerson = NULL;
	Position beforeElement = NULL;
	Position temp = NULL;

	beforeElement = findBeforeElement(p, soughtLastName);
	if (beforeElement == NULL) {
		return EXIT_FAILURE;
	}
	newPerson = createPerson(newName, newlastName, newBirthYear);


	temp = beforeElement->next;
	beforeElement->next = newPerson;
	newPerson->next = temp;

	return 0;
}

int newAfterElement(Position p, char* newName, char* newlastName, int newBirthYear, char* soughtLastName) {
	Position newPerson = NULL;
	Position afterElement = NULL; //kinda confusing if you think about it, what would be better?
	Position temp = NULL;

	afterElement = findElement(p, soughtLastName);
	if (afterElement == NULL) {
		return EXIT_FAILURE;
	}
	newPerson = createPerson(newName, newlastName, newBirthYear);

	if (afterElement->next != NULL) {
		temp->next = afterElement->next;
	}

	afterElement->next = newPerson;
	newPerson->next = temp;

	return 0;
}

Position createPerson(char* newName, char* newlastName, int newBirthYear) {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Error: unable to allocate memory\n");
		return NULL;
	}
	strcpy(newPerson->name, newName);
	strcpy(newPerson->lastName, newlastName);
	newPerson->birthYear = newBirthYear;

	return newPerson;

}

Position findElement(Position p, char* lastName) { //does this work properly if element doesn't exist? //where is this used
	if (p == NULL) {
		//printf("Empty list\n");
		return NULL;
	}

	while ((p != NULL) && (strcmp(lastName, p->lastName) != 0)) {
		p = p->next;

	}
	return p;
}

Position findBeforeElement(Position p, char* lastName) { //&head //returns null if not found
	if (p->next == NULL) {
		return NULL;
	}
	while ((p->next != NULL) && (strcmp(p->next->lastName, lastName)) != 0) {
		p = p->next;
	}
	if (p->next == NULL) { //is this necessary
		return NULL;
	}
	return p;
}

int deleteElement(Position p, char* lastName) {
	Position temp = NULL;

	while (p->next != NULL) {
		if (strcmp(lastName, p->next->lastName) == 0) {
			break;
		}
		p = p->next;
	}
	if (p->next == NULL) { //is this a failure or not? idk?
		return EXIT_FAILURE;
	}

	temp = p->next;
	p->next = p->next->next; //can be NULL but that's fine
	if (temp == NULL) {
		return 0;
	}

	free(temp);
	return 0;
}

int deleteAll(Position p) {
	Position temp = NULL;

	while (p->next != NULL) {
		temp = p->next;
		free(p);
		p = temp;
	}
	return 0;
}

int swapElements(Position p, Position q) { //are there better ways to do this?
	int tempInt = 0;
	char* tempFirst = NULL;
	char* tempLast = NULL;

	if (p == NULL || q == NULL) {
		return EXIT_FAILURE;
	}

	tempFirst = (char*)malloc((strlen(p->name) + 1) * sizeof(char));

	if (tempFirst == NULL) {
		return EXIT_FAILURE;
	}

	tempLast = (char*)malloc((strlen(p->lastName) + 1) * sizeof(char));

	if (tempLast == NULL) {
		return EXIT_FAILURE;
	}

	tempInt = p->birthYear;
	p->birthYear = q->birthYear;
	q->birthYear = tempInt;

	strcpy(tempFirst, p->name);
	strcpy(p->name, q->name);
	strcpy(q->name, tempFirst);

	strcpy(tempLast, p->lastName);
	strcpy(p->lastName, q->lastName);
	strcpy(q->lastName, tempLast);

	free(tempFirst);
	free(tempLast);

	return 0;
}

int findElementNum(Position p) { //headnext
	int counter = 0;
	while (p != NULL) {
		counter++;
		p = p->next;
	}
	return counter;
}

/*
* 1 element - sorted
* 0 elements - failure or sucess? will just say sucess
* appears to be error here? maybe? doesn't show up with debugger
*/
int bubbleSortElements(Position p) { //head.next 
	Position temp = NULL;
	int i = 0;
	int swapedNum = 0;

	int elNum = findElementNum(p);
	if (elNum == 0) {
		return 0;
	}
	else if (elNum == 1) {
		return 0;
	}

	temp = p;
	do {
		swapedNum = 0;
		for (i = 0; i <= (elNum - 2); i++) {
			if (strcmp(p->lastName, p->next->lastName) > 0) {
				swapElements(p, p->next);
				swapedNum++;
			}
			temp = temp->next;
		}

	} while (swapedNum != 0);

	return 0;
}

int printList(Position p) { //headnext
	if (p == NULL) {
		printf("Empty list\n");
		return 0;
	}

	while (p != NULL) {
		printf("%s %s %d\n", p->name, p->lastName, p->birthYear);
		p = p->next;
	}
	return 0;
}


int writeList(Position p, char* fileName) { //&head
	FILE* file = fopen(fileName, "w");
	if (file == NULL) {
		return EXIT_FAILURE;
	}
	while (p->next != NULL) {
		p = p->next;
		fprintf(file, "%s %s %d\n", p->name, p->lastName, p->birthYear);
	}
	fclose(file);
	return 0;
}

int readList(char* fileName) { //getting erros I don't understand
	FILE* file = fopen(fileName, "r");
	char* name = { 0 };
	char* lastName = { 0 };
	int birthYear = 0;

	if (file == NULL) {
		return EXIT_FAILURE;
	}
	printf("Text from file %s\n", fileName);
	while (!feof(file)) {
		fscanf(file, "%s %s %d ", name, lastName, &birthYear);
		printf("%s %s %d\n", name, lastName, birthYear);
	}

	fclose(file);
	return 0;
}
