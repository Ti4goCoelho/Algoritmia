#include <stdlib.h>
#include <stdio.h>

//Isto deve ser colocado num ficheiro ".h"
typedef struct node *PtNode;
typedef struct student Student;
PtNode CreateNewNode(Student);
void TestClass_Alunos_V1();

// --
struct node
{
    PtNode PtNext;
    Student *student;
};


struct student
{
    int id;
    char *name;
    float average;
};


PtNode CreateNewNode(Student student)
{
    PtNode newNode;

    if((newNode = (PtNode) malloc(sizeof(struct node))) == NULL)
        return NULL;

    if(( newNode->student = (Student*) malloc(sizeof(Student))) == NULL)
    {
        free(newNode);
        return NULL;
    }

    *newNode->student = student;
    newNode->PtNext = NULL;

    return newNode;
}


void TestClass_Alunos_V1()
{
    Student al = {69102, "Maria Sousa", 18};
    PtNode students = CreateNewNode(al);
    printf("\n N Mecanografico: %d \n Nome: \t\t  %s \n Media do Curso:  %0.2f \n",students->student->id, students->student->name, students->student->average);
}
