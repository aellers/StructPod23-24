//a,b,c za slijedeci put?
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128

struct _Person;
typedef _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char lastName[MAX_SIZE];
	int DOB; //date of birth
	Position next;
}Person;


int newFirstElement(Position p, char* newName, char* newlastName, int newDOB);
int newLastElement(Position p, char* newName, char* newlastName, int newDOB);
Position createPerson(char* newName, char* newlastName, int newDOB);
int menu(); //work on this later


int main() {
	Person head; //whats that .name way initialization?
	strcpy(head.name, "");
	strcpy(head.lastName, "");
	head.DOB = 0;
	head.next = NULL;



	return 0;
}

int newFirstElement(Position p, char* newName, char* newlastName, int newDOB) {
	Position newPerson = NULL;
	newPerson = createPerson(newName, newlastName, newDOB);
	if (!newPerson) {
		printf("Error: unable add person\n");
		return 1; //do i return 1 here or not?
	}
	newPerson->next = p->next; 
	p->next = newPerson;

	return 0;
}

int newLastElement(Position p, char* newName, char* newlastName, int newDOB) {

	return 0;
}

Position createPerson(char* newName, char* newlastName, int newDOB) {
	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Error: unable to allocate memory\n");
		return NULL;
	}
	strcpy(newPerson->name, newName);
	strcpy(newPerson->lastName, newlastName);
	newPerson->DOB = newDOB;

	return newPerson;

}

