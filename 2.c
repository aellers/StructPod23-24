//a,b,c za slijedeci put?
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
	int birthYear; //date of birth
	Position next;
}Person;


int newFirstElement(Position p, char* newName, char* newlastName, int newBirthYear); //&head
int newLastElement(Position p, char* newName, char* newlastName, int newBirthYear); //todo
Position createPerson(char* newName, char* newlastName, int newBirthYear);
Position findElement(Position p, char* lastName); //head.next
int deleteElement(Position p, char* lastName); //&head
int printList(Position p); //head.next

int menu(); //work on this later


int main() {
	Person head; //whats that .name way initialization?
	strcpy(head.name, "");
	strcpy(head.lastName, "");
	head.birthYear = 0;
	head.next = NULL;

	newFirstElement(&head, "abc", "xyz", 2000); 
	newFirstElement(&head, "a", "m", 1997);

	printList(head.next);
	deleteElement(&head, "m");
	deleteElement(&head, "xyz");
	printf("new print out\n");
	printList(head.next);

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

int newLastElement(Position p, char* newName, char* newlastName, int newBirthYear) { //todo

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

Position findElement(Position p, char* lastName) {
	if (p == NULL) {
		//printf("Empty list\n");
		return NULL;
	}

	while ((p != NULL) && (strcmp(lastName, p->lastName) != 0)) { 
		p = p->next;

	}
	return p;
}

int deleteElement(Position p, char* lastName) {
	Position temp = NULL;

	while (p->next != NULL) {
		if (strcmp(lastName, p->next->lastName) == 0) {
			break;
		}
	}

	temp = p->next;
	p->next = p->next->next;
	free(temp);

	return 0; 
}

int printList(Position p) { //headnext(
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
