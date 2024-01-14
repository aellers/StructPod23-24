#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_SIZE 100
//tree of lists

struct _state; 
typedef struct _state* statePointer; 

struct _city;
typedef struct _city* cityPointer;

typedef struct _state {
	char name[NAME_SIZE]; 
	statePointer leftChild; 
	statePointer rightChild; 
	cityPointer firstCity; 
}state;



typedef struct _city {
	char name[NAME_SIZE]; 
	int population; 
	cityPointer nextCity; 
}city;

int createStructure(state* rootState, char* fileName);
state* createStateTree(state* rootState, char* name);  //more accurately createStateNode()
city* createCityList(char* fileName); 
city* createCityElement(char* cityName, int cityPop);


state* findState(state* rootState, char* stateName);

#define NAME_SIZE 100

int main() {
	state* root; 


	return 0; 
}

int createStructure(state* rootState, char* fileName)
{
	FILE* file = fopen(fileName, "r");
	if (!file) {
		return EXIT_FAILURE; 
	}

	char stateName[NAME_SIZE] = "";
	char cityFileName[2 * NAME_SIZE] = "";

	state* currentState = NULL; 

	while (fscanf(file, "%s %s ", stateName, cityFileName) == 2) {
		createStateTree(rootState, stateName); 
		currentState = findState(rootState, stateName); 
		//create list of cities
	}
	return 0;
}

state* createStateTree(state* rootState, char* name)
{
	if (rootState == NULL) {
		rootState = (state*)malloc(sizeof(state)); 
		strcpy(rootState->name, name); 
		rootState->leftChild = NULL; 
		rootState->rightChild = NULL; 
		rootState->firstCity = NULL; 
	}
	else if (strcmp(rootState->name, name) > 0) {
		rootState->leftChild = createStateTree(rootState->leftChild, name); 
	}
	else if (strcmp(rootState->name, name) < 0) {
		rootState->rightChild = createStateTree(rootState->rightChild, name); 
	}
	return rootState;
}

city* createCityList(char* fileName)
{
	FILE* cityFile = fopen(fileName, "r"); 
	if (!cityFile) {
		return NULL; 
	}

	char cityName[NAME_SIZE] = ""; 
	int cityPop = 0; 

	city* rootCity = (city*)malloc(sizeof(city)); 
	rootCity->nextCity = NULL; 

	if (fscanf(cityFile, "%s %d ", cityName, &cityPop) == 2) {
		strcpy(rootCity->name, cityName); 
		rootCity->population = cityPop; 
	}
	else {
		strcpy(rootCity->name, cityName);
		rootCity->population = cityPop;
		return rootCity;
	}

	city* prev = rootCity;
	city* current = rootCity->nextCity; //but this isn't sth so it does really matter what we set it to

	while (fscanf(cityFile, "%s %d ", cityName, &cityPop) == 2) {
		while ((current != NULL) && (strcmp(current->name, cityName) > 0)) {
			prev = current; 
			current = current->nextCity;
		}
		prev->nextCity = createCityElement(cityName, cityPop); 
		prev->nextCity->nextCity = current; 

		prev = rootCity;
		current = prev->nextCity;
	}
	
	return rootCity;
}

city* createCityElement(char* cityName, int cityPop)
{
	city* newCity = (city*)malloc(sizeof(city)); 
	if (!newCity) {
		return NULL; 
	}

	strcpy(newCity->name, cityName); 
	newCity->population = cityPop; 
	newCity->nextCity = NULL; 
	return newCity;
}

state* findState(state* rootState, char* stateName)
{
	if (rootState == NULL) {
		return NULL;
	}
	else if (strcmp(rootState->name, stateName) > 0) {
		return findState(rootState->leftChild, stateName);
	}
	else if (strcmp(rootState->name, stateName) < 0) {
		return findState(rootState->rightChild, stateName);
	}
	return rootState;
}

