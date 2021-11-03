#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Oppgave 3. Liste håndtering (20 %)  
Du skal lage en dobbeltlenket liste, hvert element (struct) i listen skal inneholde 
pekere til både forrige element og neste element. Elementet skal også inneholde en 
tekststreng som inneholder VARENAVN, en integer som inneholder ANTALL, og en 
float som inneholder PRIS PER VARE. Totalt sett utgjør listen en salgskvittering i en 
matvarebutikk. 
 
Du skal lage funksjoner som utfører følgende operasjoner på listen: 
• Legge til et element i slutten av listen 
• Slette siste element i listen (en «angreknapp») 
• Sletter alle elementer i listen som har et gitt VARENAVN (sendes som 
parameter til funksjonen) 
• Summerer sammen total pris for varene i listen (husk å ta hensyn til antall) 
• Printer ut en kvittering (i konsoll vinduet) 
Du skal lage en main funksjon som mottar instrukser fra bruker basert på input fra 
tastaturet, main må altså kunne kalle alle de fem funksjonene over (for eksempel i en 
form for meny) og be brukeren om data som er nødvendig for å kalle de nevnte 
funksjoner. Main skal rydde opp alle data før den returnerer (et valg i menyen må 
være å avslutte).
*/

typedef struct Node{
    char* VARENAVN[25];
    int ANTALL;
    float PRIS;
    struct Node* NEXT;
    struct Node* PREV;
}Node;


void queue(Node **pheadNode, char* navn, float pris, int antall); //add a node to the end of the list
void printList(Node **pheadNode); //print all nodes into terminal
void deQueue(Node **pheadNode); //delete last added node
void searchAndDelete(Node **pheadNode); //delete all nodes with name "*Input*"
int sum(Node **pheadNode); //sum pris på alle varer i listen
void menu(Node *pheadNode);
void handleInput(Node **pheadNode);
void cleanUpAndExit(Node **pheadNode);

int main(){
    Node *pheadNode = NULL;
    queue(&pheadNode, "ole", 2, 3);
    queue(&pheadNode, "per", 2, 3);
    queue(&pheadNode, "katt", 2, 3);
    queue(&pheadNode, "fisk", 2, 3);
    queue(&pheadNode, "lisa", 2, 3);

    menu(pheadNode);
return 0;
}


void menu(Node *pheadNode){
    int choice;
        printf("\n*********************\n");
        printf("Menu\n");
        printf("\n*********************\n");
        printf("Write a number then confirm selection with enter\n");
        printf("1. Legg til vare i slutten av listen:\n");
        printf("2. Slett forrige/ angre forrige element\n");
        printf("3. Fjern alle varer med navn fra listen: \n");
        printf("4. Sum av alle varer: \n");
        printf("5. Kvittering\n");
        printf("6. Exit program\n");
        scanf("%i", &choice);
            switch (choice){
                case 1:
                    handleInput(&pheadNode);
                    break;
                case 2:
                    deQueue(&pheadNode);
                    break;                
                case 3:
                    searchAndDelete(&pheadNode);
                    break;
                case 4:
                    sum(&pheadNode);
                    break;
                case 5:
                    printList(&pheadNode);
                    break;
                case 6:
                    cleanUpAndExit(&pheadNode);
                    break;
                default:
                    printf("not a valid option");
            }
}


void handleInput(Node **pheadNode){
char * navn = malloc(sizeof(char)*25);
float pris;
int antall;
printf("\n*********************\n");
printf("Oppgi et varenavn og trykk enter:  ");
scanf("%s", navn);
printf("\nOppgi en pris og trykk enter:  ");
scanf("%f",&pris);
printf("\nOppgi antall varer og trykk enter:  ");
scanf("%d",&antall);
printf("\n");
queue(pheadNode, navn, pris, antall);
}


void queue(Node **pheadNode, char* navn, float pris, int antall){
    Node *newNode;    
    newNode = malloc(sizeof*newNode);
    *newNode->VARENAVN = navn;
    newNode->PRIS = pris;
    newNode->ANTALL = antall;
    //check if there's no Nodes
        if(*pheadNode==NULL){ //for some reason it's never null
            newNode->PREV = NULL;
            newNode->NEXT = NULL;
            *pheadNode = newNode;
            printf("%f",newNode->PRIS);
            printf("nullNode");
            menu(*pheadNode);
            return;
        } 
    
    Node *i = *pheadNode;   
    //go to end of list
    while (i->NEXT != NULL){
        i=i->NEXT;
    } 
    //Set temp next to newnode
    i->NEXT = newNode;
    newNode->PREV = i;
    
    printf("%f",newNode->PRIS);
    menu(*pheadNode);
} //add a node to the end of the list

void printList(Node **pheadNode){
    Node *i;
    for (i = *pheadNode; i != NULL; i = i->NEXT){
    printf("\n*********************\n");
    printf("navn: %s\n", *i->VARENAVN);
    printf("pris: %f\n", i->PRIS); 
    printf("antall: %d\n", i->ANTALL); 
    printf("\n*********************\n");
    }
   menu(*pheadNode);
   } //print all nodes into terminal
   
void deQueue(Node **pheadNode){
    Node *i=*pheadNode;
    while(i->NEXT!= NULL) i = i->NEXT;
    i->PREV->NEXT = NULL;
    free(i);
    menu(*pheadNode);
} //delete last added node

void searchAndDelete(Node **pheadNode){
    char * searchTerm =malloc(sizeof(char)*25);
    printf("\nSkriv navnet på det du ønsker å slette: \n");
    scanf("%s", searchTerm);
     // Store head node
    Node *i = *pheadNode, *prev;
 
    // If head node itself holds the key to be deleted
    if (i != NULL && i->VARENAVN == searchTerm) {
        printf("deleted headnode\n");
        *pheadNode = i->NEXT; // Changed head
        free(i); // free old head
        menu(*pheadNode);
    }
 
    // Search for the key to be deleted, keep track of the
    // previous node as we need to change 'prev->next'
    while (i != NULL && i->VARENAVN != searchTerm) {
        printf("next node\n");

        prev = i;
        i = i->NEXT;
    }
    if(i!=NULL && i->VARENAVN==searchTerm){
        // Unlink the node from linked list
    prev->NEXT = i->NEXT;
    free(i);
    }
    // If key was not present in linked list
    if (i == NULL)
        printf(" keynot found\n");
        
 
 
 
    free(i); // Free memory
    menu(*pheadNode);

    /* Node *i = *pheadNode;
    while(i->NEXT != NULL){
        if(i->VARENAVN == &searchTerm){//delete i
            i->NEXT= i->PREV->NEXT;
            i->PREV= i->NEXT->PREV;
        }
         i = i->NEXT;
         }
         if(i->NEXT ==NULL && i->VARENAVN==&searchTerm){//checks if null recursive with dequeue, if its only element dqueue handle
             deQueue(pheadNode);
         }
        
    
    free(i);  */
    menu(*pheadNode);

} //delete all nodes with name "*Input*"
int sum(Node **pheadNode){
    printf("hei\n");
    main();
    return 0;
} //sum pris på alle varer i listen


void cleanUpAndExit(Node **pheadNode){
   // free();
    exit(0);
}
