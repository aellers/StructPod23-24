#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 100
#define BUCKET_NUMBER 11

struct _drzava;
typedef struct _drzava* drzavaPointer;

struct _city;
typedef struct _city* cityPointer;


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

int createCountryHashTable(drzava** bucketArray, char* countriesFileName, int bucketNumber);
drzava* createCountry(char* countryName);

city* createCityTree(char* fileName);
city* createCityNode(city* root, char* cityName, int cityPop);

int main() {

	drzava* bucketArray[BUCKET_NUMBER];

	createCountryHashTable(&bucketArray, "drzave.txt", BUCKET_NUMBER); //something about this function causes a build error, idk what 



	return 0;
}


int createCountryHashTable(drzava** bucketArray, char* countriesFileName, int bucketNumber) {
	int hashValue = 0;
	int bucketNum = 0;
	FILE* countryFile = fopen(countriesFileName, "r");

	if (!countryFile) {
		return EXIT_FAILURE;
	}

	char countryName[NAME_SIZE];
	char citiesFileName[2 * NAME_SIZE];
	drzava* newCountry = NULL;
	city* rootCity = NULL;

	drzava* prev = NULL;
	drzava* current = NULL;

	while (fscanf(countryFile, " %s %s ", countryName, citiesFileName) == 2) {
		hashValue = 0;
		//calculate hash value
		for (int i = 0; i < 5; ++i) { //assuming every country has four letters at least and each string is null terminated
			hashValue += (int)countryName[i];
		}
		bucketNum = hashValue % BUCKET_NUMBER;

		current = bucketArray[bucketNum];

		while ((current != NULL) && (strcmp(countryName, current->ime) > 0)) {
			prev = current;
			current = current->nextDrzava;
		}

		//create country data piece, structure
		newCountry = createCountry(countryName);
		//add to correct bucket

		prev->nextDrzava = newCountry;
		newCountry->nextDrzava = current;

		//create city tree
		newCountry->rootCity = createCityTree(citiesFileName); 
	}


	fclose(countryFile);
	return 0;
}

drzava* createCountry(char* countryName) {
	drzava* newCountry = (drzava*)malloc(sizeof(drzava));
	if (newCountry == NULL) {
		return newCountry;
	}

	strcpy(newCountry->ime, countryName);
	newCountry->nextDrzava = NULL;
	newCountry->rootCity = NULL;

	return newCountry;
}


city* createCityTree(char* fileName) { //file with all the cities of one state
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

	if (fscanf(file, "%s %d ", name, &cityPop) == 2) {
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

	while (fscanf(file, "%s %d ", name, &cityPop) == 2)
	{
		createCityNode(root, name, cityPop);
	}

	return root;
}

city* createCityNode(city* root, char* cityName, int cityPop) {
	if (root == NULL) {
		root = (city*)malloc(sizeof(city));
		strcpy(root->name, cityName);
		root->population = cityPop;
		root->leftChild = NULL;
		root->rightChild = NULL;
	}
	else if (root->population > cityPop) {
		root->leftChild = createCityNode(root->leftChild, cityName, cityPop);
	}
	else if (root->population < cityPop) {
		root->rightChild = createCityNode(root->rightChild, cityName, cityPop);
	}
	else if (root->population == cityPop) {
		if (strcmp(root->name, cityName) <= 0) {
			root->rightChild = createCityNode(root->rightChild, cityName, cityPop);
		}
		else {
			root->leftChild = createCityNode(root->leftChild, cityName, cityPop);
		}
	}
	return root;
}
