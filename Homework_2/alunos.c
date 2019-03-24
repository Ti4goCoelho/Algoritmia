#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>


// Definição das variáveis globais
int N=8;
int V_num[8]= {32125, 28365, 31666, 40000, 52125, 48365, 51666, 60000};
char *V_nome[]= {"Maria Alves", "Pedro Ramos", "Ana Coelho", "Sofia Ribeiro", "Carlos Ribeiro", "Carlos Pinto", "Tiago Barbosa", "Alda Castro"};
int V_nota[8]= {19,17,13,18,10,11,13,20};

// Definição da estrutura Decomposta da Lista
typedef struct Dados *Elemento;
struct Dados
{
	int num;
	char nome[20];
	int nota;
};

typedef struct No *Ptr_No;
struct No
{
       Ptr_No   Ptr_Seg;
       Elemento Ptr_Elem;
};
///<<<< Feito pelo PROF >>>>///
//Declaração da função para criar um nó
Ptr_No Criar_No(int indice);

//Declaração da função para inserir elementos na lista
void InserirElemento(Ptr_No *Ptr, int indice);

//Declaração da função para inserir elementos na lista pelo utilizador
void InserirElementoUser(Ptr_No *Ptr);

//Declaração da função para procurar elemento através do número mecanográfico
void ProcurarElementoNum(Ptr_No *Ptr, int valor);

//Declaração da função para remover um nó
void RemoverNo(Ptr_No *Ptr_Elem);

//Declaração da função para remover elementos na lista através do número mecanográfico
void RemoverElemento(Ptr_No *Ptr, int valor);

//Declaração da função para visualizar a lista
void VerLista(Ptr_No *Ptr);

///<<< TPC >>>///
//Procurar o melhor aluno
Elemento ProcurarMelhorAluno(Ptr_No *Ptr);

//Apresentar dados de um aluno
void ImprimeAluno(Elemento aluno);

//Procurar aluno pelo numero
Ptr_No ProcuraraAluno_Num(Ptr_No *Ptr, int num);

// Programa Principal
int main()
{
    int i, op=9;
    Ptr_No noMax, lista=NULL;

    // Criar a Lista
    if (( lista=(Ptr_No) malloc (sizeof(struct No))) == NULL )
        exit(-1);

    // Criar 1o Elemento da Lista
    if ((lista = (Ptr_No) Criar_No(0)) == NULL)
        exit(-1);

    // Inserir os N outros elementos
    for( i=1; i<N; i++)
        InserirElemento( &lista, i);

    while(op!=0)
    {
        printf("\n\n ***** MENU ******\n");
        printf("\n [ 1 ] Ver conteudo da Lista");
        printf("\n [ 2 ] Inserir um novo Aluno");
        printf("\n [ 3 ] Melhor Aluno");
        printf("\n [ 4 ] Procurar Aluno");
        printf("\n [ 0 ] Sair do programa");
        printf("\n\n >>>> Escolher uma opcao (0,1,2,3,4): ");
        scanf("%d",&op);

        switch (op)
        {
        case 1:
            // Ver conteúdo da Lista ordenada
            printf("\n <<< Conteudo da Lista >>>");
            VerLista(&lista);
            break;
    printf("O Melhor aluno e: \n");
        case 2:
            // Inserir elemento pelo Utilizador
            InserirElementoUser(&lista);
            VerLista(&lista);
            break;

        case 3:
            printf("\n <<< Melhor Aluno >>>\n");
            Elemento aluno = ProcurarMelhorAluno(&lista);
            ImprimeAluno(aluno);
            printf("\nPress any key to cont...");
            _cscanf("%c");
            system("cls");
            break;

        case 4:
            printf("\n <<< Obter Dados do ALuno >>>\n");
            printf("Numero de aluno: ");
            int num = 0;
            scanf("%d", &num);
            Ptr_No no = ProcuraraAluno_Num(&lista, num);
            if(no == NULL)
                printf("O aluno numero %d nao existe na nossa base de dados.", num);
            else
                ImprimeAluno(no->Ptr_Elem);
            printf("\nPress any key to cont...");
            _cscanf("%c");
            system("cls");
            break;

        default:
            printf("\n valor inserido errado \n");
        }
    }

    system("pause");
    free(lista);

    return 0;
}

///////////////////////////////////////////////////////////////////
// Função Criar nó
Ptr_No Criar_No(int indice)
{
    Ptr_No No;

    if (( No=(Ptr_No) malloc (sizeof(struct No))) == NULL )
        return NULL;

    if (( No->Ptr_Elem=(Elemento) malloc (sizeof(struct Dados)))== NULL )
    {
        free(No);
        return NULL;
    }
    No->Ptr_Elem->num = V_num[indice];
    strcpy(No->Ptr_Elem->nome,V_nome[indice]);
    No->Ptr_Elem->nota = V_nota[indice];
    No->Ptr_Seg = NULL;

    return No;
}

// Inserir Elemento numa Lista
void InserirElemento(Ptr_No *Ptr, int indice)
{
    // Declaração dos ponteiros
    Ptr_No NoInserir;
    Ptr_No NoAnterior = NULL;
    Ptr_No NoActual = *Ptr;

    if ((NoInserir = Criar_No(indice)) == NULL)
        return;

    // Procura da posição de inserção na Lista
    while ( NoActual != NULL && V_num[indice] > NoActual->Ptr_Elem->num)
    {
        NoAnterior = NoActual;
        NoActual = NoActual->Ptr_Seg;
    }

    // Inserir o elemento na lista
    if (NoAnterior == NULL)
    {
        NoInserir->Ptr_Seg = *Ptr;
        *Ptr = NoInserir;
    }
    else
    {
        NoInserir->Ptr_Seg = NoActual;
        NoAnterior->Ptr_Seg = NoInserir;
    }
}

//Procurar elemento através do número mecanográfico
void ProcurarElementoNum(Ptr_No *Ptr, int valor)
{
    // Declaração dos ponteiros
    Ptr_No NoActual = *Ptr;
    int i=2;

    // Verificar se a lista está vazia
    if (NoActual == NULL)
        return;

    // Elemento no início da lista
    if (valor == NoActual->Ptr_Elem->num)
    {
        printf("\nNumero Encontrado no No/Elemento 1:\n\tNumero: %d \n\tNome: %s \n\tNota: %d\n", NoActual->Ptr_Elem->num, NoActual->Ptr_Elem->nome, NoActual->Ptr_Elem->nota);
        return;
    }
    else
    {
        NoActual=NoActual->Ptr_Seg;
    }

    // Procurar o elemento na lista
    while (NoActual != NULL)
    {
        if(NoActual->Ptr_Elem->num == valor)
        {
            printf("\nNumero Encontrado no No/Elemento %d:\n\tNumero: %d \n\tNome: %s \n\tNota: %d\n", i, NoActual->Ptr_Elem->num, NoActual->Ptr_Elem->nome, NoActual->Ptr_Elem->nota);
            return;
        }
        else
        {
            NoActual = NoActual->Ptr_Seg;
        }
        i++;
    }
}

// Remover Nó
void RemoverNo(Ptr_No *Ptr_Elem)
{
    free((*Ptr_Elem)->Ptr_Elem);
    free(*Ptr_Elem);

    Ptr_Elem = NULL;
}

// Remover Elemento numa Lista
void RemoverElemento(Ptr_No *Ptr, int valor)
{
    // Declaração dos ponteiros
    Ptr_No NoAnterior = *Ptr;
    Ptr_No NoActual = *Ptr;
    Ptr_No NoRemover =NULL;

    // Verificar se a lista está vazia
    if (NoActual == NULL)
        return;

    // Elemento no início da lista
    if (valor == NoActual->Ptr_Elem->num)
    {
        NoRemover=NoActual;
        NoActual=NoActual->Ptr_Seg;
        *Ptr = (*Ptr)->Ptr_Seg;
        RemoverNo (&NoRemover);
        //printf("\nNo 1 removido\n");
    }
    else
    {
        NoActual=NoActual->Ptr_Seg;
    }

    // Procurar o elemento na lista
    while (NoActual != NULL)
    {
        if(NoActual->Ptr_Elem->num == valor)
        {
            NoAnterior->Ptr_Seg = NoActual->Ptr_Seg;
            NoRemover = NoActual;
            NoActual = NoActual->Ptr_Seg;
            RemoverNo(&NoRemover);
        }
        else
        {
            NoAnterior = NoActual;
            NoActual = NoActual->Ptr_Seg;
        }
    }
}

// Ver conteúdo de uma Lista
void VerLista(Ptr_No *Ptr)
{
    Ptr_No NoActual = *Ptr;
    int i = 1;

    if (NoActual == NULL)
    {
        printf("Lista vazia");
        return;
    }
    while (NoActual != NULL)
    {
        printf("Elemento %d \n\tNumero: %d \n\tNome: %s\n\tNota: %d\n", i, NoActual->Ptr_Elem->num, NoActual->Ptr_Elem->nome, NoActual->Ptr_Elem->nota);
        i++;
        NoActual = NoActual->Ptr_Seg;
    }
}


// Inserir Elemento numa Lista pelo utilizador
void InserirElementoUser(Ptr_No *Ptr)
{
    // Declaração dos ponteiros
    Ptr_No NoInserir;
    Ptr_No NoAnterior = NULL;
    Ptr_No NoActual = *Ptr;

    if (( NoInserir =(Ptr_No) malloc (sizeof(struct No))) == NULL )
        return;

    if (( NoInserir->Ptr_Elem=(Elemento) malloc (sizeof(struct Dados)))== NULL )
    {
        free(NoInserir);
        return;
    }

    // Preenchimento da estrutura de dados
    printf("\n Inserir o No Mecanografico: ");
    scanf("%d", &NoInserir->Ptr_Elem->num);
    printf("\n Inserir o Nome do aluno: ");
    scanf("%s", NoInserir->Ptr_Elem->nome);
    printf("\n Inserir a nota final de curso: ");
    scanf("%d", &NoInserir->Ptr_Elem->nota);
    NoInserir->Ptr_Seg = NULL;

    // Procura da posição de inserção na Lista
    while ( NoActual != NULL && NoInserir->Ptr_Elem->num > NoActual->Ptr_Elem->num)
    {
        NoAnterior = NoActual;
        NoActual = NoActual->Ptr_Seg;
    }

    // Inserir o elemento na lista
    if (NoAnterior == NULL)
    {
        NoInserir->Ptr_Seg = *Ptr;
        *Ptr = NoInserir;
    }
    else
    {
        NoInserir->Ptr_Seg = NoActual;
        NoAnterior->Ptr_Seg = NoInserir;
    }
}


///<<< TPC >>>///
Elemento ProcurarMelhorAluno(Ptr_No *Ptr)
{
    Ptr_No MelhorAluno, NoActual = *Ptr;

    if (NoActual == NULL)
        return NULL;

    MelhorAluno = NoActual;
    NoActual = NoActual->Ptr_Seg;
    while (NoActual != NULL)
    {
        if(NoActual->Ptr_Elem->nota > MelhorAluno->Ptr_Elem->nota)
        {
            MelhorAluno = NoActual;
        }
        NoActual = NoActual->Ptr_Seg;
    }
    return MelhorAluno->Ptr_Elem;
}

void ImprimeAluno(Elemento aluno)
{
    printf(" Nome: %s\n Numero: %d\n Com %d valores\n", aluno->nome, aluno->num, aluno->nota);
}

Ptr_No ProcuraraAluno_Num(Ptr_No *Ptr, int num)
{
    Ptr_No NoActual = *Ptr;

    if (NoActual == NULL)
        return NULL;

    while (NoActual != NULL)
    {
        if(NoActual->Ptr_Elem->num == num) return NoActual;
        NoActual= NoActual->Ptr_Seg;
    }

    return NULL;
}
