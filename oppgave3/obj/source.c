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
    char* VARENAVN[20];
    int ANTALL;
    float PRIS;
    struct Node* NEXT;
    struct Node* PREV;
}Node;
void push(Node **pheadNode);
void pop(Node **pheadNode, int ant, float pris);
void ctrlZ();
void delVare();

int main(){
    Node *phead = NULL;
    int choice;
        printf("Menu\n");
        printf("Write a number then confirm selection with enter\n");

        printf("1. push Node\n");
        printf("2. Delete last added element\n");
        printf("3. Delete any VARE with name: \n");
        printf("4. get the price of all VARE with naem: \n");
        printf("5. print the lis\n");
        printf("6. Exit program\n");
        scanf("%i", &choice);
            switch (choice){
                case 1:
                    push(&phead);
                    break;
                case 2:
                    ctrlZ();
                    break;
                default:
                    printf("not a valid option");
            }
return 0;
}


void push(Node **pheadNode){
    printf("hei\n");
    main();
};

void pop(Node **pheadNode, int ant, float pris){};
void ctrlZ(){};
void delVare(){};