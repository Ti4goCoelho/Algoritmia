#include <stdlib.h>
#include <stdio.h>

/*
    "Lista Dinâmica Encadeada"

    Tipo de "Lista" onde cada elemento aponta para o
    seu sucessor na "lista".
    Usa um ponteiro especial para o primeiro elemento
    da lista e um indicação de final de lista.

    | Dado | Proximo|

            Inicio
    dados»  | 33 |p| -> | 23 |p| -> | 16 |p| -> NULL


    - Cada elemento é tratado como um ponteiro que é
    alocado dinamicamente, a medida que os dados são
    inseridos.

    - Para guardar o primeiro elemento, utilizamos um
    "ponteiro para ponteiro"

    - Um "ponteiro para ponteiro" pode guardar o
    endereço de um "ponteiro"

    - Assim, fica fácil mudar que está no início da lista
    mudando o "conteúdo" do "ponteiro para ponteiro"

    Vantagens:
    - Melhor utilização dos recursos de memória
    - Não precisa movimentar os elementos nas operações
    de inserção e remoção

    Desvantagens:
    - Acesso indireto aos elementos
    - Necessidade de percorrer a lista para aceder a um
    elemento

    Quando utilizar essa "Lista"?
    - Não há neccessidade de garantir um espaço mínimo para
    execução do programa
    -Inserção/remoção em lista ordenada são as operações mais
    frequentes

*/

///Arquivo LinkedList.h
typedef struct
{
    int id;
    char name[30];
    float score1, score2, score3;
} Student;

typedef struct element *LinkedList;

LinkedList *createLinkedList();

void LListFree(LinkedList *li);

int LListSize(LinkedList *li);

// Em Listas Dinâmica a lista nunca fica cheia a
// menos que a memória do computador se esgote.
int LListIsFull(LinkedList *li);

int LListIsEmpty(LinkedList *li);

int LListInsertInFirstPosition(LinkedList *li, Student s);

int LListInsertInLastPosition(LinkedList *li, Student s);

int LListInsertInOrder(LinkedList *li, Student s);

int LListRemoveFirstPosition(LinkedList *li);

int LListRemoveLastPosition(LinkedList *li);

int LListRemove(LinkedList *li, int id);

int LListFindByPosition(LinkedList *li, int position, Student *s);

int LListFindById(LinkedList *li, int id, Student *s);

///Arquivo LinkedList.c
struct element
{
    struct element *next;
    Student student;
};
typedef struct element Element;

LinkedList *createLinkedList()
{
    LinkedList *li = (LinkedList *)malloc(sizeof(LinkedList));
    if (li != NULL)
        *li = NULL;
    return li;
}

void LListFree(LinkedList *li)
{
    if (li != NULL)
    {
        Element *no;
        while ((*li) != NULL)
        {
            no = *li;
            *li = (*li)->next;
            free(no);
        }
        free(li);
    }
}

int LListSize(LinkedList *li)
{
    if (li == NULL)
        return 0;

    int cont = 0;
    Element *no = *li;
    while (no != NULL)
    {
        cont++;
        no = no->next;
    }
    return cont;
}

int LListIsFull(LinkedList *li)
{
    return 0; //FALSE
}

int LListIsEmpty(LinkedList *li)
{
    if (li == NULL)
        return 1;
    if (*li == NULL)
        return 1;
    return 0;
}

int LListInsertInFirstPosition(LinkedList *li, Student s)
{
    if (li == NULL)
        return 0;

    Element *no = (Element *)malloc(sizeof(Element));
    if (no == NULL)
        return 0;

    no->student = s;
    no->next = (*li);
    *li = no;
    return 1;
}

int LListInsertInLastPosition(LinkedList *li, Student s)
{
    if (li == NULL)
        return 0;

    Element *no = (Element *)malloc(sizeof(Element));
    if (no == NULL)
        return 0;

    no->student = s;
    no->next = NULL;

    if ((*li) == NULL) //Lista vazia: insere no início
        *li = no;
    else
    {
        Element *aux = *li;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = no;
    }
    return 1;
}

int LListInsertInOrder(LinkedList *li, Student s)
{
    if (li == NULL)
        return 0;

    Element *no = (Element *)malloc(sizeof(Element));
    if (no == NULL)
        return 0;

    no->student = s;

    if (LListIsEmpty(li)) // Vazia - insere início
    {
        no->next = (*li);
        *li = no;
        return 1;
    }
    else
    {
        Element *prev, *current = *li;
        while (prev != NULL && current->student.id < s.id) //procura a posição correta
        {
            prev = current;
            current = current->next;
        }

        if (current == *li) //Insere no Inicio
        {
            no->next = (*li);
            *li = no;
        }
        else
        {
            no->next = prev->next;
            prev->next = no;
        }
        return 1;
    }
}

int LListRemoveFirstPosition(LinkedList *li)
{
    if (li == NULL)
        return 0;

    if ((*li) == NULL) //Lista vazia
        return 0;

    Element *no = *li;
    *li = no->next;
    free(no);

    return 1;
}

int LListRemoveLastPosition(LinkedList *li)
{
    if (li == NULL)
        return 0;

    if ((*li) == NULL)
        return 0;

    Element *prev, *no = *li;
    while (no->next != NULL)
    {
        prev = no;
        no = no->next;
    }

    if (no == (*li)) //Remover o primeiro elemento
        *li = no->next;
    else
        prev->next = no->next;

    free(no);

    return 1;
}

int LListRemove(LinkedList *li, int id)
{
    if (li == NULL)
        return 0;

    Element *prev, *no = *li;
    while (no != NULL && no->student.id != id)
    {
        prev = no;
        no = no->next;
    }

    if (no == NULL) // Não encontrado
        return 0;

    if (no == *li) // Remover o primeiro
        *li = no->next;
    else
        prev->next = no->next;

    free(no);
    return 1;
}

int LListFindByPosition(LinkedList *li, int position, Student *s)
{
    if (li == NULL || position <= 0)
        return 0;

    Element *no = *li;
    int i = 1;
    while (no != NULL && i < position)
    {
        no = no->next;
        i++;
    }

    if (no == NULL)
        return 0;
    else
    {
        *s = no->student;
        return 1;
    }
}

int LListFindById(LinkedList *li, int id, Student *s)
{
    if (li == NULL)
        return NULL;

    Element *no = *li;
    while (no != NULL && no->student.id != id)
        no = no->next;

    if (no == NULL)
        return 0;
    else
    {
        *s = no->student;
        return 1;
    }
}

///Programa principal

void PrintLListStudent(Student s)
{
    printf("Id: %d\n", s.id);
    printf("Name: %s\n", s.name);
    printf("Score: %.2f %.2f %.2f\n", s.score1, s.score2, s.score3);
    printf("\n");
}

void PrintLList(LinkedList *li)
{

    if (li == NULL)
        return;

    printf("\nStudent's List:\n");

    Element *no = *li;
    while (no != NULL)
    {
        PrintLListStudent(no->student);
        no = no->next;
    }
}

void TestLinkedList()
{
    LinkedList *li;
    li = createLinkedList();

    printf("Number of elements: %d\n", LListSize(li));
    printf("The list is empty: %s\n", (LListIsEmpty(li) == 1 ? "TRUE" : "FALSE"));

    Student s1 = {67000, "Ana", 8, 13, 20};
    LListInsertInFirstPosition(li, s1);
    printf("Number of elements: %d\n", LListSize(li));

    Student s2 = {67004, "Pedro", 19, 18, 17};
    LListInsertInLastPosition(li, s2);
    printf("Number of elements: %d\n", LListSize(li));

    Student s3 = {67002, "Ricardo", 13, 18, 16};
    LListInsertInOrder(li, s3);
    printf("Number of elements: %d\n", LListSize(li));

    //LListRemoveFirstPosition(li);

    //LListRemoveLastPosition(li);

    //LListRemove(li, 67002);

    //PrintLList(li); //Imprime a lista de alunos

    Student s4;
    //LListFindByPosition(li, 2, &s4);
    LListFindById(li, 67004, &s4);
    PrintLListStudent(s4); //Imprime aluno

    LListFree(li);
}
