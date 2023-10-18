#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student{
    char name[MAX_SIZE];
    char lastname[MAX_SIZE]; //change to lastName
    double points;
} student;

int countStudents(char fileName[MAX_SIZE]);
student* allocateMemory(int studentNum);

int main() {
    char fileName[MAX_SIZE];
    int studentNum = 0;
    student* firstStudentPos = NULL;

    printf("Unesi ime datoteke: ");
    scanf("%s", fileName);

    studentNum = countStudents(fileName);
    firstStudentPos = allocateMemory(studentNum);




    return 0;
}

int countStudents(char* fileName) { //dont remember is making it a pointer is whats best
    FILE* file;
    char line[MAX_LINE];
    int counter = 0;

    file = fopen(fileName, "r");
    if (!file) {
        printf("Neuspjesno otvaranje\n");
        //return sth when put into function
    }

    while (!feof(file)) {
        fgets(line, MAX_LINE, file);
        counter++;
    }

    return counter;
}

student* allocateMemory(int studentNum) {
    student* students = NULL;
    students = (student*)malloc(sizeof(student) * studentNum);
    if (students == NULL) {
        printf("Error: unable to allocate memory\n");
        return NULL;
    }
    return students;
}




