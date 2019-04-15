//
// Created by Eduardo Queirós on 2019-04-14.
//

#ifndef CLASSROOM_STUDENT_H
#define CLASSROOM_STUDENT_H

typedef struct Date{
    int year;
    int month;
    int day;
}date;

typedef struct Student *pStudents, STUDENT;
struct Student{
    int id;
    char name[200];
    char gender;
    date Registration;
    int average;
};

typedef struct Node *pNode;
struct Node{
    pNode next;
    pStudents student;
};


/// List operations
/// Create:list, node, students
/// Add new node: last position, in order by id
/// Find: by ID
pStudents CreateStudent(int id, char *name, char gender, date reg, int average);
pNode CreateNode(pStudents student);
pNode* CreateList();
int AddNodeInLast(pNode *list, pNode node);
int AddNodeInOrder(pNode *list, pNode node);
pStudents FindStudentByID(pNode *list, int id);
pNode* FindStudentsByYear(pNode *list, int year);
pNode* FindStudentsByAverage(pNode *list, int avg);


/// CLI
void printStudents(pNode *list);
void printStudent(pStudents student);

///File operations
void saveStudents(pNode *list);
void readStudents(pNode *list);


#endif //CLASSROOM_STUDENT_H
