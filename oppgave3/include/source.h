#ifndef _SOURCE_h
#define _SOURCE_h

//included libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for the nodes
typedef struct Node
{
    char *ITEMNAME[25];
    int QUANTITY;
    float PRICE;
    struct Node *NEXT;
    struct Node *PREV;
} Node;
//and struct for doubly linked list
typedef struct DLL
{
    Node *head;
    Node *tail;
} DLL;

int menu(DLL *list); //function for menu

DLL *initDLL(void);   //create the doubly linked list
Node *initNode(void); // and nodes also checking malloc

float sum(DLL *list); //returns sum of all elements in the list

void cleanExit(DLL *list);                                         //frees mem and exits
void printList(DLL *list);                                         //prints the items in pretty terminal
void deleteWithKey(DLL *list);                                     //delete with a key.
void inputValidation(DLL *list);                                   //check if info
void delNode(DLL *list, Node *_delete);                            //delete the node given as arg.
void appendNode(DLL *list, char *name, float price, int quantity); //takes input from inputvalidation. andcreates a node

#endif