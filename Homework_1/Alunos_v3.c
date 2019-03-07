#include <stdlib.h>
#include <stdio.h>

//Isto deve ser colocado num ficheiro ".h"
typedef struct aluno *Aluno;
typedef struct dados Dados;
Aluno CriarAluno(Dados d);
void TestClass_Alunos_V3();


//--
struct dados
{
    int id;
    char *name;
    float average;
};
struct aluno
{
    Aluno Next;
    Dados d;
};



Aluno CriarAluno(Dados d)
{
    Aluno novo;

    if((novo = (Aluno) malloc(sizeof(struct aluno))) == NULL)
        return NULL;

    novo->d = d;
    novo->Next = NULL;

    return novo;
}

void TestClass_Alunos_V3()
{
    Dados d = {69102, "Maria Sousa", 18};
    Aluno al = CriarAluno(d);
    printf("\n N Mecanografico: %d \n Nome: \t\t  %s \n Media do Curso:  %0.2f \n",al->d.id, al->d.name, al->d.average);
}
