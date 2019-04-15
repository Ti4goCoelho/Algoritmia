//
// Created by Eduardo Queirós on 2019-04-14.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Student.h"

pStudents CreateStudent(int id, char *name, char gender, date reg, int average) {
    pStudents s = (pStudents) malloc(sizeof(struct Student));
    if (s == NULL) return NULL;
    s->id = id;
    strcpy(s->name, name);
    s->gender = gender;
    s->Registration = reg;
    s->average = average;
    return s;
}

pNode CreateNode(pStudents student) {
    pNode n = (pNode) malloc(sizeof(struct Node));
    n->next = NULL;
    n->student = student;
    return n;
}

pNode *CreateList() {
    pNode *list = (pNode *) malloc(sizeof(pNode));
    if (list != NULL)
        *list = NULL;
    return list;
}

int AddNodeInLast(pNode *list, pNode node) {
    if (list == NULL) return 0;

    if (*list == NULL) {
        *list = node;
        return 1;
    }

    pNode l = *list;
    while (l->next != NULL) {
        l = l->next;
    }
    l->next = node;
    return 1;
}

int AddNodeInOrder(pNode *list, pNode node) {
    if (list == NULL) return 0;

    if (*list == NULL) {
        *list = node;
        return 1;
    }

    pNode l = *list;
    pNode prev = NULL;
    while (l != NULL && l->student->id < node->student->id) {
        prev = l;
        l = l->next;
    }
    if (prev == NULL) {
        node->next = *list;
        *list = node;
    } else {
        node->next = l;
        prev->next = node;
    }
    return 1;
}


pStudents FindStudentByID(pNode *list, int id) {
    pNode n = *list;
    while (n != NULL) {
        if (n->student->id == id)
            return n->student;

        n = n->next;
    }
    return NULL;
}

pNode *FindStudentsByYear(pNode *list, int year) {
    pNode *aux = CreateList();
    pNode l = *list;
    while (l != NULL) {
        if (l->student->Registration.year == year) {
            pNode n = CreateNode(l->student);
            AddNodeInLast(aux, n);
        }
        l = l->next;
    }
    return aux;
}

pNode *FindStudentsByAverage(pNode *list, int avg) {
    pNode *aux = CreateList();
    pNode l = *list;
    while (l != NULL) {
        if (l->student->average == avg) {
            pNode n = CreateNode(l->student);
            AddNodeInLast(aux, n);
        }
        l = l->next;
    }
    return aux;
}

void printStudents(pNode *list) {
    if (list == NULL || *list == NULL) {
        printf("Empty List...\n");
    } else {
        int i = 1;
        pNode n = *list;
        while (n != NULL) {
            printf("Student[%d]\n", i++);
            printStudent(n->student);
            printf("\n");
            n = n->next;
        }
    }
}

void printStudent(pStudents student) {
    if (student == NULL) {
        printf("Don't have any information... \n");
    } else {
        printf("\tNumber: %d\n", student->id);
        printf("\tName: %s\n", student->name);
        printf("\tGender: %c\n", student->gender);
        printf("\tRegistration dd/mm/yyyy: %d/%d/%d\n",
               student->Registration.day,
               student->Registration.month,
               student->Registration.year);
        printf("\tAverage: %d\n", student->average);
    }
}

/// File operations
void saveStudents(pNode *list) {

    FILE *fp = fopen("../db/students.csv", "w");

    if (*list == NULL) return;

    pNode l = *list;
    char str[500];
    snprintf(str, 500, "id,name,gender,year,month,day,average\n");
    fprintf(fp, str);
    while (l != NULL) {
        int id = l->student->id;
        char *name = l->student->name;
        char gender = l->student->gender;
        int year = l->student->Registration.year;
        int month = l->student->Registration.month;
        int day = l->student->Registration.day;
        int average = l->student->average;
        snprintf(str, 500, "%d,%s,%c,%d,%d,%d,%d\n", id, name, gender, year, month, day, average);
        fprintf(fp, str);
        l = l->next;
    }
    fclose(fp);
}

void readStudents(pNode *list) {
    if (list == NULL) return;

    const int SL = 500;
    FILE *fp = fopen("../db/students.csv", "r");
    if (fp == NULL) {
        printf("Error - Failed to open file (students.csv)...\n");
    } else {
        char line[SL];
        printf("Read students data...\n");
        fgets(line, SL, fp);
        printf("%s", line);

        char *delim = ",";
        while (fgets(line, SL, fp)) {
            //id,name,gender,year,month,day,average
            char *id = strtok(line, delim);
            char *name = strtok(NULL, delim);
            char *gender = strtok(NULL, delim);
            char *year = strtok(NULL, delim);
            char *month = strtok(NULL, delim);
            char *day = strtok(NULL, delim);
            char *average = strtok(NULL, delim);

            date d = {atoi(year), atoi(month), atoi(day)};
            pStudents student = CreateStudent(atoi(id), name, gender[0], d, atoi(average));
            pNode node = CreateNode(student);
            //AddNodeInLast(list, node);
            AddNodeInOrder(list, node);
        }
    }
    fclose(fp);
}






