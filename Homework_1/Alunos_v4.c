#include <stdio.h>
#include <stdlib.h>

typedef struct al *pAluno;
typedef struct al ALUNO;
struct al
{
    int Num_Mec;
    char *Nome;
    float Media;
};

typedef struct No *pNO;
struct No
{
    pNO pNext;
    pAluno pAl;
};

pAluno creatNode(ALUNO a)
{
    pNO newNode;

    if((newNode = (pNO) malloc(sizeof(struct No))) == NULL)
        return NULL;

    if(( newNode->pAl = (pAluno) malloc(sizeof(ALUNO))) == NULL)
    {
        free(newNode);
        return NULL;
    }

    *newNode->pAl = a;
    newNode->pNext = NULL;

    return newNode;
}

void PrintLista(pNO *p)
{
    pNO atual = *p;
    if(atual == NULL)
    {
        printf("Lista Vazia");
        return;
    }
    while(atual != NULL)
    {
        printf("Numero de mecanografico: %d\n", atual->pAl->Num_Mec);
        printf("Nome: %s\n", atual->pAl->Nome);
        printf("Media: %.2f\n", atual->pAl->Media);
        atual = atual->pNext;
    }

}

int addNoInList(pNO *p, pNO no)
{
    if(no == NULL)
    {
        return 0;
    }

    if(*p == NULL)
    {
        *p = no;
    }
    else
    {
        pNO atual = *p;
        while(atual->pNext != NULL)
        {
            atual = atual->pNext;
        }
        atual->pNext = no;
    }
    return 1;
}


void TestClass_Alunos_V4()
{
    ALUNO a1 = {69102, "Maria Sousa", 18};
    ALUNO a2 = {69103, "Luis Sousa", 13};
    ALUNO a3 = {69104, "Ana Rita", 16};
    ALUNO a4 = {69105, "Pedro Nunes", 19};

    pNO n1 = creatNode(a1);
    pNO n2 = creatNode(a2);
    pNO n3 = creatNode(a3);
    pNO n4 = creatNode(a4);

    pNO list = NULL;
    addNoInList(&list, n1);
    addNoInList(&list, n2);
    addNoInList(&list, n3);
    addNoInList(&list, n4);
    if(list != NULL)
    {
        PrintLista(&list);
    }
}