#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Source/Student.h"
#include "Source/God.h"
#include "Source/Art.h"

//Const
#define N 50

//functions declaration
void createList(pNode *list);

pStudents newStudent();

///Menu
int MainMenu();

///Util
void CleanBuffer();
void Pause();

int main() {
    //Create a List
    pNode *list = CreateList();

    //Generate students.csv
    //createList(list);

    //Read students.csv
    readStudents(list);

    int op = -1;
    while (op) {
        op = MainMenu();
        switch (op) {
            case 0:
                printf("Goodbye, see you next time ...\n");
                break;
            case 1:
                printStudents(list);
                Pause();
                break;
            case 2:
                printf("Enter the student number: ");
                int id = 0;
                scanf(" %d", &id);
                printStudent(FindStudentByID(list, id));
                Pause();
                break;
            case 3:
                printf("Enter the year: ");
                int year = 0;
                scanf(" %d", &year);
                printStudents(FindStudentsByYear(list, year));
                Pause();
                break;
            case 4:
                printf("Enter the average: ");
                int avg = 0;
                scanf(" %d", &avg);
                printStudents(FindStudentsByAverage(list, avg));
                Pause();
                break;
            default:
                printf("The option is invalid...\n");
                printf("Press any key to cont...");
                CleanBuffer();
                getchar();
        }
    }

    //printStudents(list);
    return 0;
}


///Menus
int MainMenu() {
    printf("\n\n\n");
    Title();
    printf("\n<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>\n");
    printf("*\t\t\t\t\tMAIN MENU\t\t\t\t\t *\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t *\n");
    printf("*\t  1 - Print all Students\t\t\t\t\t *\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t *\n");
    printf("*\t  Find: \t\t\t\t\t\t\t\t\t *\n");
    printf("*\t  2 - Find Student by Number\t\t\t\t *\n");
    printf("*\t  3 - Find all Students by Year\t\t\t\t *\n");
    printf("*\t  4 - Find all Students by Average\t\t\t *\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t *\n");
    printf("*\t  0 - Close The Program\t\t\t\t\t\t *\n");
    printf("*\t\t\t\t\t\t\t\t\t\t\t\t *\n");
    printf("<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>*<>\n");
    printf("Select an Option: ");
    int op = -1;
    scanf("%d", &op);
    return op;
}

/// Other Functions
void createList(pNode *list) {
    STUDENT sLis[N];
    generateStudents(sLis, N);

    for (int i = 0; i < N; i++) {
        pStudents student = CreateStudent(sLis[i].id, sLis[i].name, sLis[i].gender, sLis[i].Registration,
                                          sLis[i].average);
        pNode node = CreateNode(student);
        AddNodeInLast(list, node);
    }
    saveStudents(list);
}

pStudents newStudent() {
    char name[50], g;
    int num = 0, avg = 0;
    date d = {0, 0, 0};

    printf("Insert new Student:\n");
    printf("Students Name: ");
    scanf("%[^\n]s", name);
    fflush(stdin);

    printf("Students Number: ");
    scanf(" %d", &num);
    fflush(stdin);

    printf("Students Gender(F,M): ");
    scanf(" %c", &g);
    g = toupper(g);
    g = (g == 'M' || g == 'F') ? g : 'I';
    fflush(stdin);

    printf("Registration date: yyyy/mm/dd: ");
    scanf(" %d/%d/%d", &(d.year), &(d.month), &(d.day));
    fflush(stdin);

    printf("Average: ");
    scanf(" %d", &avg);
    fflush(stdin);


    pStudents student = CreateStudent(num, name, g, d, avg);
    return student;
}

void CleanBuffer() {
    scanf("%*[^\n]");
    scanf("%*c");
}

void Pause()
{
    printf("Press any key to cont...");
    CleanBuffer();
    getchar();
}