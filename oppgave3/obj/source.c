#include <stdio.h>
#include <stdlib.h>
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
    char* VARENAVN;
    int ANTALL;
    float PRIS;
    struct Node* NEXT;
    struct Node* PREV;
}Node;
void queue(Node **pheadNode, char* navn, float pris, int antall); //add a node to the end of the list
void printList(Node **pheadNode); //print all nodes into terminal
void deQueue(); //delete last added node
void searchAndDelete(); //delete all nodes with name "*Input*"
int sum(Node **pheadNode); //sum pris på alle varer i listen

//void pop(Node **pheadNode, int ant, float pris);

int main(){
    Node *phead = NULL;
    int choice;
        printf("Menu\n");
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
                    queue(&phead, "Navn", 2.3, 3);
                    break;
                case 2:
                    deQueue();
                    break;                
                case 3:
                    searchAndDelete();
                    break;
                case 4:
                    sum(&phead);
                    break;
                case 5:
                    printList(&phead);
                    break;
                case 6:
                    cleanUpAndExit();
                    break;
                default:
                    printf("not a valid option");
            }
return 0;
}



void queue(Node **pheadNode, char* navn, float pris, int antall){
    struct Node *newNode;    
    newNode = malloc(sizeof*newNode);
    Node *i = *pheadNode;
    newNode->VARENAVN = navn;
    newNode->PRIS = pris;
    newNode->ANTALL = antall;
        if(*pheadNode == NULL){
            newNode->PREV = NULL;
            newNode->NEXT = NULL;
            *pheadNode = newNode;
            return;
        } 
    printf("%f",&newNode->PRIS);
    main();
} //add a node to the end of the list
void printList(Node **pheadNode){
    printf("hei\n");
    main();
} //print all nodes into terminal
void deQueue(){
    printf("hei\n");
    main();
} //delete last added node
void delVare(){
    printf("hei\n");
    main();
} //delete all nodes with name "*Input*"
int sum(Node **pheadNode){
    printf("hei\n");
    main();
} //sum pris på alle varer i listen
void searchAndDelete(){

}
void cleanUpAndExit(){
   // free();
    exit(0);
}
