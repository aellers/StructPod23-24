//can write them in the polynomials however want for this assignment, obviously it needs to be same
//can have 
//exponent and coefficient are from set Z, intergers
//will have 4 lists 
//read polynomials (&head1, &head2, file)
// \033[ \033] prints in red?
//for reading use sscanf "%dx^%d %n" %n for number of bytes, how many things were read so here 2
//sscanf vraca koliko je procitao, ovdje treba biti 2, uvijek
//free elements with zero coefficient

//use exit_sucess/failure

//make variable names full words
//make variable names clearly show what they're about coefficient not co

//ne mora zbrajat i mnoziti

/*
* todo: Monday 13.11.23
*  make insertSorted() function
* 3. whatever else I figure out needs doing

*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 128

struct _Element;
typedef struct _Element* Position;

typedef struct _Element {
    int coefficient;
    int exponent;
    Position next;

}Element;

int readPolynomials(Position head1, Position head2, char* fileName);
Position createElement(int co, int ex);
int deleteElement(Position prev, Position p);
Position findPrevEl(Position head, Position p);
int insertElement(Position beforeEl, Position el);
int createPolynomial(Position head, char* currentBuffer);

int insertSorted(Position head, int coefficient, int exponent);

int printPolynomial(Position head);

int addPolynomials(Position head1, Position head2, Position headAdd);
int multiplyPolynomials(Position head1, Position head2, Position headMult);


int main() {
    Element polynomial1 = { .coefficient = 0, .exponent = 0, .next = NULL };
    Element polynomial2 = { .coefficient = 0, .exponent = 0, .next = NULL };

    Element polynomialAdd = { .coefficient = 0, .exponent = 0, .next = NULL }; //for reslt of addition
    Element polynomialMult = { .coefficient = 0, .exponent = 0, .next = NULL }; //for result of multiplication


    readPolynomials(&polynomial1, &polynomial2, "text.txt");
    printPolynomial(&polynomial1);
    printPolynomial(&polynomial2);

    addPolynomials(&polynomial1, &polynomial2, &polynomialAdd); //some problems here, not everything shows up //? 
    printf("add\n");
    printPolynomial(&polynomialAdd);

    multiplyPolynomials(&polynomial1, &polynomial2, &polynomialMult); //sth's fucked here?
    printf("mult\n");
    printPolynomial(&polynomialMult); 

    return 0;
}

int readPolynomials(Position head1, Position head2, char* fileName) {
    FILE* file = NULL;
    char buffer[MAX] = { 0 };
    char* currentBuffer = NULL;

    file = fopen(fileName, "r");
    if (!file) {
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX, file);
    currentBuffer = buffer;
    createPolynomial(head1, currentBuffer);

    fgets(buffer, MAX, file);
    currentBuffer = buffer;
    createPolynomial(head2, currentBuffer);


    fclose(file);

    return 0;
}

Position createElement(int co, int ex) {
    Position newElement = NULL;
    newElement = (Position)malloc(sizeof(Element));
    if (newElement == NULL) { //is NULL
        return EXIT_FAILURE;
    }
    newElement->coefficient = co;
    newElement->exponent = ex;
    newElement->next = NULL;
    return newElement;
}

int deleteElement(Position prev, Position p) {
    Position temp = p->next;
    prev->next = temp;
    free(p);

    return 0;
}

int insertElement(Position beforeEl, Position el) {
    Position temp = NULL;

    temp = beforeEl->next;
    beforeEl->next = el;
    el->next = temp;
    return 0;
}

int createPolynomial(Position head, char* currentBuffer) {
    Position p = NULL;
    Position newEl = NULL;
    int numBytes = 0;
    int status = 0;
    int co = 0;
    int ex = 0;

    while (strlen(currentBuffer) > 0) {
        status = sscanf(currentBuffer, "%dx^%d %n", &co, &ex, &numBytes);
        if (status != 2) {
            fprintf(stderr, "Error reading polynomial\n");
            return EXIT_FAILURE;
        }
        currentBuffer += numBytes;
        p = head;
        if (co == 0) {
            continue;
        }
        while ((p->next != NULL) && (ex <= p->next->exponent)) { //pay attention to things like this, actually think
            p = p->next;
        }
        if (p->exponent == ex) { //can this be undefined?
            p->coefficient += co;
            if (p->coefficient == 0) {
                deleteElement(findPrevEl(head, p), p); // is this bad practice?

            }
        }
        else {
            newEl = createElement(co, ex);
            insertElement(p, newEl);
        }

    }

    return 0;
}

int insertSorted(Position head, int coefficient, int exponent) //should be for the given ex and co of some element
{
    Position newElement = NULL;
    Position before = head->next;
    if (head->next == NULL) { 
        newElement = createElement(coefficient, exponent);
        insertElement(head, newElement);
        return 0; 
    }
    
    while ((before->next != NULL) && (!(before->exponent > exponent && exponent >= before->next->exponent))) { //this is probably not exactly correct
        before = before->next;
    }

    if (exponent == before->exponent) {
        before->exponent += exponent;
    }
    else { //not sure if this is saying exactly what I want it to be meaning //probably is, haven't seen issues so far
        newElement = createElement(coefficient, exponent); 
        insertElement(before, newElement); 
    }
    return 0;
}

int printPolynomial(Position head) { //could make x^0 not show up but with negative ex. makes less sense
    Position p = head->next;

    while (p != NULL) {
        printf("%dx^%d ", p->coefficient, p->exponent);
        if (p->next != NULL) {
            printf("+ ");
        }
        p = p->next;
    }
    printf("\n");

    return 0;
}

Position findPrevEl(Position head, Position p) {
    Position prev = head;
    while ((prev->next != NULL) && (prev->next != p)) {
        prev = prev->next;
    }
    if (prev->next == NULL) {
        return NULL;
    }
    else {
        return prev;
    }
}

int addPolynomials(Position head1, Position head2, Position headAdd) {
    Position p1 = head1->next;
    Position p2 = head2->next;
    Position newEl = NULL;
    Position prev = headAdd;

    while ((p1 != NULL) && (p2 != NULL)) {
        if (p1->exponent == p2->exponent) {
            newEl = createElement(p1->coefficient + p2->coefficient, p1->exponent);
            insertElement(prev, newEl);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if (p1->exponent > p2->exponent) {
            newEl = createElement(p1->coefficient, p1->exponent);
            insertElement(prev, newEl);
            p1 = p1->next;
        }
        else {
            newEl = createElement(p2->coefficient, p2->exponent);
            insertElement(prev, newEl);
            p2 = p2->next;
        }
        prev = newEl;
    }
    while (p1 != NULL) {
        newEl = createElement(p1->coefficient, p1->exponent);
        insertElement(prev, newEl);
        p1 = p1->next;
        prev = newEl;
    }
    while (p2 != NULL) {
        newEl = createElement(p2->coefficient, p2->exponent);
        insertElement(prev, newEl);
        p2 = p2->next;
        prev = newEl;
    }

    return 0;
}

int multiplyPolynomials(Position head1, Position head2, Position headMult) //probably works mostly, lmao
{
    Position position1 = head1->next;
    Position position2 = head2->next;
    Position newElement = NULL;

    while (position1 != NULL) {
        position2 = head2->next;
        while (position2 != NULL) {
            insertSorted(headMult, position1->coefficient * position2->coefficient, position1->exponent + position2->exponent);
                //iterate p2
            position2 = position2->next;
        }
        //iterate p1
        position1 = position1->next;
    }

    return 0;
}
