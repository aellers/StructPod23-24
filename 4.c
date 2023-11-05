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

//ne mora zbrajat i mnoziti
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

int printPolynomial(Position head); //maybe make another one which prints to some stream, overload

int addPolynomials(Position head1, Position head2, Position headAdd);
int multiplyPolynomials(Position head1, Position head2, Position headMult); //total mess, what's a nicer way to do it


int main() {
    Element polynomial1 = { .coefficient = 0, .exponent = 0, .next = NULL };
    Element polynomial2 = { .coefficient = 0, .exponent = 0, .next = NULL };

    Element polynomialAdd = { .coefficient = 0, .exponent = 0, .next = NULL }; //for reslt of addition
    Element polynomialMult = { .coefficient = 0, .exponent = 0, .next = NULL }; //for result of multiplication
    

    readPolynomials(&polynomial1, &polynomial2, "text.txt"); 
    printPolynomial(&polynomial1); 
    printPolynomial(&polynomial2);

    addPolynomials(&polynomial1, &polynomial2, &polynomialAdd); //some problems here, not everything shows up
    printf("add\n");
    printPolynomial(&polynomialAdd);

    multiplyPolynomials(&polynomial1, &polynomial2, &polynomialMult);  
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

int multiplyPolynomials(Position head1, Position head2, Position headMult) { //numbers get input all (order) wrong, don't get it
    Position p1 = head1->next;
    Position p2 = head2;
    Position pM = headMult; //for inner for loop
    Position newEl = NULL; 
    Position prev = headMult;

    while (p1 != NULL) {
        p2 = head2;
        while (p2->next != NULL) {
            p2 = p2->next;
            pM = headMult;
            if ((p1->coefficient * p2->coefficient) == 0) {
                p2 = p2->next;
                continue;
            }
            
            while ((pM->next!=NULL) && ((p1->exponent + p2->exponent) <= pM->exponent)) {
                pM = pM->next; //why didn't it loop? 
            }
            if ((p1->exponent + p2->exponent) == pM->exponent) {
                pM->coefficient += (p1->coefficient * p2->coefficient);
                if (pM->coefficient == 0) {
                    deleteElement(findPrevEl(headMult, pM), pM); 
                }
            }
            else {
                prev = pM;
                newEl = createElement((p1->coefficient * p2->coefficient), (p1->exponent + p2->exponent)); 
                insertElement(prev, newEl);
            }
        }

        p1 = p1->next;
    }
    return 0; 

}
