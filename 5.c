#define _CRT_SECURE_NO_WARNINGS
#define MAX 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//how does stderr work?

struct _stackElement;
typedef struct _stackElement* Position; 

typedef struct _stackElement {
	double number;
	Position next;
}StackElement;

int deleteAll(Position head); //later

int readExpression(char* fileName, char* buffer); 
double calculateExpression(Position head, char* fileName);
int calculateResult(Position head, double* result, char operator);  
Position createNewStackElement(double number);

int push(Position head, Position newElement); 
int pop(Position head, double* result);

int main() 
{
	StackElement head = { .number = 0, .next = NULL };
	double result = 0.0;

	result = calculateExpression(&head, "text.txt"); //there are problems here but I'll fix them later
	printf("result: %lf\n", result);

	//call delete all when make that function
	return 0; 
}

int readExpression(char* fileName, char* buffer)
{
	FILE* file = NULL; 
	file = fopen(fileName, "r");
	if (!file) {
		return EXIT_FAILURE;
	}
	fgets(buffer, MAX, file); 

	fclose(file);
	return 0;
}

double calculateExpression(Position head, char* fileName)
{
	char buffer[MAX] = { 0 };
	char* currentBuffer = NULL;
	char operator = '\0'; //is this what it should be initialized to?
	int status = 1; //assume things fail
	int calculateStatus = 0; 
	double number = 0; 
	int numberOfBytes = 0;
	double currentResult = 0.0; 
	Position newElement = NULL;

	status = readExpression(fileName, buffer); 
	if (status == EXIT_FAILURE) {
		return EXIT_FAILURE;
	}

	currentBuffer = buffer;
	while ((strlen(currentBuffer) > 0) && !calculateStatus) {
		status = sscanf(currentBuffer, " %lf %n", &number, &numberOfBytes);
		if (!status) {
			sscanf(currentBuffer, " %c %n", &operator, &numberOfBytes);
			calculateStatus = calculateResult(head, &currentResult, operator);
			if (calculateStatus) {
				break;
			}
			newElement = createNewStackElement(currentResult); 
			push(head, newElement); 
		}

		currentBuffer += numberOfBytes;
	}
	if (calculateStatus) {
		return EXIT_FAILURE;
	}
	
	return head->number;
}

int calculateResult(Position head, double* result, char operator)
{
	double operand1 = 0.0; 
	double operand2 = 0.0; 
	int status1 = 0; 
	int status2 = 0; 

	status1 = pop(head, &operand1);
	status2 = pop(head, &operand2);

	if (status1 || status2) { //wrong number of elements, not proper postfix expression
		return EXIT_FAILURE;
	}


	switch (operator) {
	case '+':
		*result = operand2 + operand1;
		break;
	case '-': 
		*result = operand2 - operand1;
		break;
	case '*':
		*result = operand2 * operand1;
		break;
	case '/':
		*result = operand2 / operand1;
		break;
	default:
		break;
	}

	return 0;
}

Position createNewStackElement(double number)
{
	Position newElement = NULL; 
	newElement = (Position)malloc(sizeof(StackElement));
	return newElement;
}

int push(Position head, Position newElement)
{
	Position afterNewElement = head->next;
	newElement->next = afterNewElement;
	head->next = newElement;

	return 0;
}

int pop(Position head, double* result) //is it sucess or failure if there's not element to pop?, didn't get element wanted for failure?
{
	Position headNext = NULL; 

	if (head->next != NULL) {
		headNext = head->next->next;
	}
	else {
		return EXIT_FAILURE;
	}

	*result = head->next->number;
	free(head->next); 
	head->next = headNext;

	return 0;
}

