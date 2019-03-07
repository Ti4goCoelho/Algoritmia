#include <stdlib.h>
#include <stdio.h>

//Isto deve ser colocado num ficheiro ".h"
typedef struct node *Node;
Node NewNode(int id, char *name, float average);
void TestClass_Alunos_V2();

//--
struct node
{
    Node Next;
    int id;
    char *name;
    float average;
};

Node NewNode(int id, char *name, float average)
{
    Node newNode;

    if((newNode = (Node) malloc(sizeof(struct node))) == NULL)
        return NULL;

    newNode->id = id;
    newNode->name = name;
    newNode->average = average;
    newNode->Next = NULL;

    return newNode;
}

void TestClass_Alunos_V2()
{

    Node students = NewNode(69102, "Maria Sousa", 18);
    printf("\n N Mecanografico: %d \n Nome: \t\t  %s \n Media do Curso:  %0.2f \n",students->id, students->name, students->average);
}
