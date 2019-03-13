#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct Aluno *ALUNO;
struct Aluno{
    int     Num_Mec;
    char    *Nome;
    float    Media;
};

typedef struct No *Ptr_No;
struct No{
    
    Ptr_No    Ptr_Seg;
    ALUNO    Ptr_Al;
    
};

void Verlista(Ptr_No *Ptr);

int main() {
    
    Ptr_No N1, Lista = NULL;

    //Criar 1º elemento da Lista
    
    if(( N1 = (Ptr_No) malloc (sizeof(struct No))) == NULL){
        return -1;
    }    
    
    if(( N1->Ptr_Al = malloc(sizeof(struct Aluno))) == NULL){
        free(N1);
        return -1;
    }

    //Preencher 1ºNó e respetivo elemento
    
    N1->Ptr_Al->Nome = "Maria Sousa";
    N1->Ptr_Al->Num_Mec = 69102;
    N1->Ptr_Al->Media = 18;
    N1->Ptr_Seg = NULL;
    
    //Inicializar o ponteiro da Lista para o endereço do 1º Elemento
    
    Lista = N1;
    Verlista(&Lista);
    
    
    
    
    /*Aluno *ptr_aluno;
    
    ptr_aluno = (Aluno*)malloc(sizeof(Aluno));

    printf("Introduza o numero mecanografico do aluno: ");
    scanf("%d", &(ptr_aluno->Num_Mec));
    printf("Introduza o nome do aluno: ");
    scanf("%s", &(ptr_aluno->Nome));
    printf("Introduza a media do aluno: ");
    scanf("%f", &(ptr_aluno->Media));
    
    free(ptr_aluno);*/
    
    
    system ("pause");
    return 0;
}

void Verlista(Ptr_No *Ptr){
        
    Ptr_No NoAtual = *Ptr;
    int i = 1;
    if(NoAtual == NULL){
        printf("Lista Vazia");
        return;
    }
        
    while(NoAtual != NULL){
        printf("\n Nome: %s\n Numero: %d\n Media:%f\n", NoAtual->Ptr_Al->Nome, NoAtual->Ptr_Al->Num_Mec, NoAtual->Ptr_Al->Media);
        i++;
        NoAtual = NoAtual->Ptr_Seg;
    }
}