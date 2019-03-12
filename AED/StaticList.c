#include <stdlib.h>
#include <stdio.h>

/*
    "Lista Sequencial Estática"
    ou
    "Lista Linear Estática":

    Tipo de "Lista" onde o sucessor de um elemento ocupa a
    posição física seguinte do mesmo (uso de "array).

    Desvantagens do uso de arrays:
    - Definição prévia do tamanho do array
    - Dificuldade para inserir e remover um elemento
    entre outros dois: é preciso deslocar elementos

    Quando utilizar essa "Lista"?
    - Lista pequenas
    - Inserção e remoção no final da lista
    - Tamanho máximo bem definido
    - A busca é a operação mais frequente

    Como implementar um "Lista Sequencial Estática"
    "StaticList.h": (aqui não vou usar o ficheiro ".h")
    - os protótipos das funções
    - o tipo de dados a ser armazenados na lista
    - o ponteiro "lista"
    - tamanho do vetor usado na lista

    "StaticList.c":
    - o tipo de dados "lista"
    -implemetação das suas funções
*/
///Arquivo "StaticList.h"
#define MAX 100
typedef struct
{
    int registration;
    char name[30];
    float score1, score2, score3;
} Student;

typedef struct staticList StaticList;

StaticList* createSList();

void SListFree(StaticList* li);

int SListSize(StaticList* li);

int SListIsFull(StaticList* li);

int SListIsEmpty(StaticList* li);

int SListInsertInLastPosition(StaticList* li, Student s);

int SListInsertInFirstPosition(StaticList* li, Student s);

int SListInsertInOrder(StaticList* li, Student s);

int SListRemoveLastPosition(StaticList* li);

int SListRemoveFirstPosition(StaticList* li);

int SListRemove(StaticList* li, int registration);

int findByPosition(StaticList* li, int position, Student *s);

int findByRegistration(StaticList* li, int registration, Student *s);

///Arquivo "StaticList.c"
struct staticList
{
    int amount;
    Student data[MAX];
};

/*
 * Cria uma "StaticList":
 *      | amout = 0
 *      | data[MAX]
 */
StaticList* createSList()
{
    StaticList *li;
    li = (StaticList*) malloc(sizeof(struct staticList));

    if(li != NULL)
        li->amount = 0;

    return li;
}


void SListFree(StaticList* li)
{
    free(li);
}


int SListSize(StaticList* li)
{
    if(li == NULL)
        return -1;

    return li->amount;
}


int SListIsFull(StaticList* li)
{
    if(li == NULL)
        return -1;

    return li->amount == MAX;
}


int SListIsEmpty(StaticList* li)
{
    if(li == NULL)
        return -1;

    return li->amount == 0;
}


int SListInsertInLastPosition(StaticList* li, Student s)
{
    if(li == NULL)
        return 0;

    if(SListIsFull(li))
        return 0;

    li->data[li->amount] = s;
    li->amount++;
    return 1;
}


int SListInsertInFirstPosition(StaticList* li, Student s)
{
    if(li == NULL)
        return 0;

    if(SListIsFull(li))
        return 0;

    for(int i = li->amount - 1 ; i >= 0; i--)
        li->data[i + 1] = li->data[i];

    li->data[0] = s;
    li->amount++;
    return 1;
}


int SListInsertInOrder(StaticList* li, Student s)
{
    if(li == NULL)
        return 0;

    if(SListIsFull(li))
        return 0;

    int i = 0;
    while(i < li->amount && li->data[i].registration < s.registration)
        i++;

    for(int k = li->amount - 1; k >= i ; k--)
        li->data[k + 1] = li->data[k];

    li->data[i] = s;
    li->amount++;
    return 1;

}


int SListRemoveLastPosition(StaticList* li)
{
    if(li == NULL)
        return 0;

    if(li->amount == 0)
        return 0;

    li->amount--;
    return 1;
}


int SListRemoveFirstPosition(StaticList* li)
{
    if(li == NULL)
        return 0;

    if(li->amount == 0)
        return 0;

    for(int i = 0; i < li->amount-1; i++)
        li->data[i] = li->data[i + 1];
    li->amount--;

    return 1;
}


int SListRemove(StaticList* li, int registration)
{
    if(li == NULL)
        return 0;

    if(li->amount == 0)
        return 0;

    int i = 0;
    while(i < li->amount && li->data[i].registration != registration)
        i++;

    if(i == li->amount) //not found
        return 0;

    for(int k = i; k < li->amount-1; k++)
        li->data[i] = li->data[i + 1];
    li->amount--;

    return 1;
}


int findByPosition(StaticList* li, int position, Student *s)
{
    if(li == NULL || position <= 0 || position > li->amount)
        return 0;

    *s = li->data[position - 1];
    return 1;
}


int findByRegistration(StaticList* li, int registration, Student *s)
{
    if(li == NULL)
        return 0;

    int i = 0;
    while(i < li->amount && li->data[i].registration != registration)
        i++;

    if(i == li->amount) // not found
        return 0;

    *s = li->data[i];
    return 1;
}

///Programa principal
void PrintSList(StaticList* li)
{
    printf("\nPrint List: \n");
    int n = SListSize(li);
    for(int i = 0; i < n; i++)
    {
        printf("S[%d]: %s \n", i, li->data[i].name);
    }
    printf("\n");
}


void PrintStudent(Student s)
{
    printf("Student:\n");
    printf("\tRegistration: %d\n",s.registration);
    printf("\tName: %s\n",s.name);
    printf("\tScore: %.2f | %.2f | %.2f\n", s.score1, s.score2, s.score3);
    printf("\n");
}


void TestStaticList()
{
    StaticList *li;
    li = createSList();

    Student s =  {67004, "Ana", 12,13,14};
    PrintStudent(s);

    SListInsertInLastPosition(li, s);
    PrintSList(li);

    Student s2 =  {67000, "Pedro", 19,18,17};
    SListInsertInFirstPosition(li, s2);
    PrintSList(li);

    Student s3 = {67002, "Ricardo", 13,18,16};
    SListInsertInOrder(li, s3);
    PrintSList(li);

    //SListRemoveLastPosition(li);
    //PrintSList(li);

    //SListRemoveFirstPosition(li);
    //PrintSList(li);

    //SListRemove(li,67009);
    //PrintSList(li);

    //SListRemove(li,67002);
    //PrintSList(li);

    Student s4;
    findByPosition(li, 2, &s4);
    PrintStudent(s4);

    Student s5;
    findByRegistration(li, 67000, &s5);
    PrintStudent(s5);

    int size = SListSize(li);
    printf("Size: %d \n", size);

    int isFull = SListIsFull(li);
    printf("Is full: %s \n", (isFull == 1?"True":"False") );

    int isEmpty = SListIsEmpty(li);
    printf("Is empty: %s \n", (isEmpty == 1?"True":"False") );


    SListFree(li);
}
