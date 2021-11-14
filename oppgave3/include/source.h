#ifndef _SOURCE_h
#define _SOURCE_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *ITEMNAME[25];
    int QUANTITY;
    float PRICE;
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
void inputValidation(DLL *list);
void cleanExit(DLL *list);
void deleteWithKey(DLL *list);
void delNode(DLL *list, Node *_delete);
void appendNode(DLL *list, char *name, float price, int quantity);
float sum(DLL *list);

#endif