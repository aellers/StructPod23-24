#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 128
#define MAX_LINE 1024

typedef struct _student {
    char name[MAX_SIZE];
    char lastName[MAX_SIZE];
    int points;
} student;

int countStudents(char fileName[MAX_SIZE]);
student* allocateMemory(int studentNum);
int writeToStudentArray(student* students, char fileName[MAX_SIZE], int studentNum); //which way correct for char arrays?
int displayStudentData(student* students, int studentNum);

int main() {
    char fileName[MAX_SIZE];
    int studentNum = 0;
    student* firstStudentPos = NULL;

    /*printf("Unesi ime datoteke: ");
    scanf("%s", fileName);
    */
    strcpy(fileName, "text.txt");

    studentNum = countStudents(fileName);
    printf("%d students\n", studentNum);
    firstStudentPos = allocateMemory(studentNum);
    writeToStudentArray(firstStudentPos, fileName, studentNum);

    displayStudentData(firstStudentPos, studentNum); //has a fuck ton of errors here, proably 
    //printf("%d\n", firstStudentPos[0].points); //got large neg number so likely issue with input




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
    fclose(file);
    return counter;
}

student* allocateMemory(int studentNum) {
    student* students = NULL;
    students = (student*) malloc(sizeof(student) * studentNum);
    if (students == NULL) {
        printf("Error: unable to allocate memory\n");
        return NULL;
    }
    return students;
}

int writeToStudentArray(student* students, char fileName[MAX_SIZE], int studentNum) { //probably an error here but what is it?
    FILE* file = NULL;
    int i = 0;

    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", fileName);
    }
    for (i = 0; i < studentNum; i++) {
        fscanf(file, " %s %s %d", students[i].name, students[i].lastName, &(students[i].points));
        //printf("%s %s %f\n", students[i].name, students[i].lastName, (students[i].points));

    }



    return 0;
}


int displayStudentData(student* students, int studentNum) {
    int i = 0;

    for (i = 0; i < studentNum; i++) {
        printf("%s %s %d\n", students[i].name, students[i].lastName, students[i].points);
        
    }
    return 0;
}
