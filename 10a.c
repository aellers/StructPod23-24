#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define NAME_SIZE 100
//list of trees
struct _drzava;
typedef struct _drzava* drzavaPointer;

struct _city;
typedef struct _city* cityPointer;


//will need to add pointer to root when get to that
typedef struct _drzava
{
	char ime[NAME_SIZE];
	drzavaPointer nextDrzava;
	cityPointer rootCity; 

}drzava;


typedef struct _city //assuming its a binary search tree
{
	char name[NAME_SIZE]; 
	int population; 
	cityPointer leftChild;
	cityPointer rightChild; 

}city;

int createStateList(drzava* drzavaHead, char* fileName);
drzava* createState(char* stateName);

city* createCityTree(char* fileName); 
city* createCityNode(city* root, char* cityName, int cityPop);

int listStates(drzava* drzavaHead); 

int main()
{
	drzava drzavaHead = { .ime = "", .nextDrzava = NULL }; 

	createStateList(&drzavaHead, "drzave.txt");

	listStates(&drzavaHead);

	return 0;
}

int createStateList(drzava* drzavaHead, char* fileName)
{
	FILE* file = fopen(fileName, "r"); 
	if (!file) {
		return EXIT_FAILURE;
	}

	char stateName[NAME_SIZE];
	char citiesFileName[2 * NAME_SIZE];
	drzava* prev = drzavaHead;
	drzava* current = drzavaHead->nextDrzava;
	city* rootCity = NULL; 

	while (fscanf(file, "%s %s ", stateName, citiesFileName) == 2)
	{
		printf("state: %s, cities file: %s \n", stateName, citiesFileName);
		while ((current != NULL) && (strcmp(stateName, current->ime) > 0)) //don't need to check if names of countries same cause they can't be; current cause increment before tests (can not pass test once)
		{
			prev = current;
			current = current->nextDrzava;
		}

		prev->nextDrzava = createState(stateName); 
		prev->nextDrzava->nextDrzava = current;

		rootCity = createCityTree(citiesFileName); 
		prev->nextDrzava->rootCity = rootCity; 

		//
		prev = drzavaHead;
		current = drzavaHead->nextDrzava;
		 
	}


	return 0;
}

drzava* createState(char* stateName)
{
	drzava* newState = (drzava*)malloc(sizeof(drzava));
	if (!newState)
	{
		return newState;
	}
		
	strcpy(newState->ime, stateName); 
	newState->nextDrzava = NULL; 
	newState->rootCity = NULL;
	return newState;
}

city* createCityTree(char* fileName) //file with all the cities of one state
{
	city* root = (city*)malloc(sizeof(city)); 
	if (!root)
	{
		return NULL; 
	}
	FILE* file = fopen(fileName, "r");
	if (!file)
	{
		return NULL; 
	}

	char name[NAME_SIZE] = "";
	int cityPop = 0; 

	if (fprintf(file, "%s %d ", name, cityPop) == 2) {
		root->leftChild = NULL; 
		root->rightChild = NULL; 
		strcpy(root->name, name); 
		root->population = cityPop; 

	}
	else {
		root->leftChild = NULL;
		root->rightChild = NULL;
		strcpy(root->name, "");
		root->population = 0;
		return root; 
	}

	while (fprintf(file, "%s %d ", name, cityPop) == 2)
	{
		createCityNode(root, name, cityPop); 
	}

	return root;
}

city* createCityNode(city* root, char* cityName, int cityPop)
{
	if (root == NULL) {
		root = (city*)malloc(sizeof(city)); 
		strcpy(root->name, cityName); 
		root->population = cityPop;
		root->leftChild = NULL; 
		root->rightChild = NULL; 
	}
	else if (root->population > cityPop) {
		createCityNode(root->leftChild, cityName, cityPop); 
	}
	else if (root->population < cityPop) {
		createCityNode(root->rightChild, cityName, cityPop); 
	}
	else if (root->population == cityPop) {
		if (strcmp(root->name, cityName) <= 0) {
			createCityNode(root->rightChild, cityName, cityPop); 
		}
		else {
			createCityNode(root->leftChild, cityName, cityPop); 
		}
	}
	return root;
}

int listStates(drzava* drzavaHead)
{
	drzavaHead = drzavaHead->nextDrzava;
	printf("List of states: \n");
	while (drzavaHead != NULL)
	{
		printf("%s \n", drzavaHead->ime); 
		drzavaHead = drzavaHead->nextDrzava;
	}
	return 0;
}

