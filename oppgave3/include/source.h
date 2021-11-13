#ifndef _SOURCE_h
#define _SOURCE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *VARENAVN[25];
    int ANTALL;
    float PRIS;
    struct Node *NEXT;
    struct Node *PREV;
} Node;

typedef struct DLL
{
    Node *head;
    Node *tail;
} DLL;

int menu(DLL *list);

DLL *initDLL(void);
Node *initNode(void);

void printList(DLL *list);
void handleInput(DLL *list);
void cleanExit(DLL *list);
void deleteWithKey(DLL *list);
void delNode(DLL *list, Node *_delete);
void appendNode(DLL *list, char *navn, float pris, int antall);
float sum(DLL *list);

#endif