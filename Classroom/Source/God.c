//
// Created by Eduardo Queirós on 2019-04-14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "Student.h"
#include "God.h"

enum mes{
    Janeiro = 1,
    Fevereiro,
    Marco,
    Abril,
    Maio,
    Junho,
    Julho,
    Agosto,
    Setembro,
    Outubro,
    Novembro,
    Dezembro
};

typedef struct DataAux Data;
struct DataAux{
    char val1[200];
    char val2[30];
    char val3[30];
};

int generateStudents(STUDENT sList[], int amount)
{
    srand(time(NULL));

    // Names and genders
    FILE *fp = fopen("../db/nomes.csv", "r");
    // Surname
    FILE *f = fopen("../db/alcunhas.csv", "r");

    if(fp == NULL || f == NULL){
        printf("Error - Failed to open file (nomes.cvs or alcunhas.csv)...\n");
    }else{
        //Create a list nickname
        char surname[80];
        int size_A = atoi(fgets(surname,80, f)); //amount of surnames
        char **alcunhas = (char *) malloc(size_A * sizeof(char*));
        for(int i = 0; i < size_A; i++)
        {
            fgets(surname, 80, f);
            alcunhas[i] = (char *) malloc(strlen(surname) * sizeof(char));
            char *sn = strtok(surname, "\n");
            sn[strlen(sn) - 1] = '\0';
            strcpy(alcunhas[i], sn);
        }

        //Create other info
        char dl[]=",";
        char line[300];
        int size = atoi(fgets(line, 300, fp)); //amount of names
        Data * names_and_sex = (Data *) malloc(sizeof(Data) * size);

        for(int i = 0 ; i < size; i++)
        {
            fgets(line, 300, fp);
            char *aux = strtok(line, dl);
            strcpy(names_and_sex[i].val1, aux);

            strtok(NULL, dl);

            int idx = rand() % size_A;
            strcpy(names_and_sex[i].val2, alcunhas[idx]);

            aux = strtok(NULL, dl);
            strcpy(names_and_sex[i].val3, aux);
        }


        for(int i = 0 ; i < amount; i++) {
            int idx = rand() % size;

            strcpy(sList[i].name, names_and_sex[idx].val1);
            strcat(sList[i].name, " ");
            strcat(sList[i].name, names_and_sex[idx].val2);
            sList[i].gender = names_and_sex[idx].val3[0];
            sList[i].id = (1000 + i);
            sList[i].Registration.year = 2000 + rand() % 19;
            sList[i].Registration.month = Setembro;
            sList[i].Registration.day = 15 + rand() % 5;
            sList[i].average = 5 + rand() % 16;
        }
        fclose(fp);
        fclose(f);
    }
    return 1;
}

