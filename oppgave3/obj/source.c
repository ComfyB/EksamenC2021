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
void deQueue(Node *pheadNode); //delete last added node
void searchAndDelete(Node **pheadNode); //delete all nodes with name "*Input*"
float sum(Node **pheadNode); //sum pris på alle varer i listen
void menu(Node *pheadNode);
void handleInput(Node **pheadNode);
void cleanUpAndExit(Node *pheadNode);

int main(){
    Node *pheadNode = NULL;
    
    menu(pheadNode);
    free(pheadNode);
return 0;
}


void menu(Node *pheadNode){
    char choice;
    int inputOk;
        printf("\n*********************\n");
        printf(  "*       Menu        *");
        printf("\n*********************\n");
        printf("Skriv inn et valg og bekreft med enter:\n");
        printf("1. Legg til vare i slutten av listen:\n");
        printf("2. Slett forrige/ angre forrige element\n");
        printf("3. Fjern alle varer med navn fra listen: \n");
        printf("4. Sum av alle varer: \n");
        printf("5. Kvittering\n");
        printf("6. Exit program\n");
        while(1){
            inputOk = scanf("%c", &choice);
            
            if(choice >='1' && choice <='6')
                break;
            if(choice != '\n')
                printf("%s is not a valid menu option!\n",&choice);
        }
        switch (choice){
            case '1':
                    handleInput(&pheadNode);
                    break;
            case '2':
                    deQueue(pheadNode);
                    break;                
            case '3':
                    searchAndDelete(&pheadNode);
                    break;
            case '4':
                    printf("%2.f",sum(&pheadNode));

                    break;
            case '5':
                    printList(&pheadNode);
                    break;
            case '6':
                    cleanUpAndExit(pheadNode);
                    break;
            default:
                    printf("something went wrong");   
                    cleanUpAndExit(pheadNode); 
        }
}


void handleInput(Node **pheadNode){

    char * navn = malloc(sizeof(char)*25);
    float pris;
    int antall;
    int inputOk;
    int i=0;
   // char clearBuff[255];
//kdjsadk
    printf("\n*********************\n");
    printf("Oppgi et varenavn og trykk enter:  ");
    inputOk = scanf("%s", navn);
    printf("\nOppgi en pris og trykk enter:  ");
            while(1){
                
                if(scanf("%f", &pris)) //,printf("\n")
                    break;
                //empty stdin so we get a proper input.
                while(fgetc(stdin)== 1){
                    i=0;
                }
                i++;
                if(i%3 == 0||i==0)
                    printf(". \n");
                if(i==1)
                    printf("please insert a valid number:\n");
            }
            
        
    printf("\nOppgi antall varer og trykk enter:  ");
     while(1){
                
                if(scanf("%d", &antall)) //,printf("\n")
                    break;
                //empty stdin so we get a proper input.
                while(fgetc(stdin)== 1){
                    i=0;
                }
                i++;
                if(i%3 == 0||i==0)
                    printf(". clearing cache\n");
                if(i==1)
                    printf("please insert a valid number:\n");
            }
            
    printf("\n%d  %s for kr %.2f hver\n",antall,navn,pris);
    if(pheadNode!=NULL) 
        queue(pheadNode, navn, pris, antall);
    else
        queue(NULL, navn, pris, antall);

}


void queue(Node **pheadNode, char* navn, float pris, int antall){
    Node *newNode;    
    newNode = malloc(sizeof(newNode));
    *newNode->VARENAVN = navn;
    newNode->PRIS = pris;
    newNode->ANTALL = antall;
    //check if there's no Nodes
        if(*pheadNode == NULL){ 
            newNode->PREV = NULL;
            newNode->NEXT = NULL;
            *pheadNode = newNode;
            printf("%f",newNode->PRIS);
            printf("nullNode");
            menu(*pheadNode);
        } 
    
    Node *i = *pheadNode;   
    //go to end of list
    while (i->NEXT != NULL){
        i=i->NEXT;
    } 
    //Set temp next to newnode
    i->NEXT = newNode;
    newNode->PREV = i;
    
    //printf("%f",newNode->PRIS);
    menu(*pheadNode);
} //add a node to the end of the list

void printList(Node **pheadNode){
    Node *i;
    printf("*********************************\n");
    printf("navn\tpris\tantall\tvaretotal\n");
    printf("_________________________________\n\n");

    for (i = *pheadNode; i != NULL; i = i->NEXT){
  
        printf("%s\t", *i->VARENAVN);
        printf("%.2f\t", i->PRIS); 
        printf("%d\t", i->ANTALL); 
        printf("%.2f\n",(i->PRIS * i->ANTALL));
  //  printf("\n*********************\n");
    }
printf("_________________________________\n\n");

printf("\033[0;31m\t\tTotal \t%.2f\n\033[0;0m",sum(pheadNode));
          printf("*********************************\n");

menu(*pheadNode);
} //print all nodes into terminal
   
void deQueue(Node *pheadNode){

 //Need to check if empty!! 
    if(pheadNode == NULL){
        printf ("Listen er tom!\n");
        menu(NULL);
    } 
    Node *i= malloc(sizeof(Node));
    memset(i,0,sizeof(Node));
    i = pheadNode;

    if(i->NEXT == NULL){
        free(i);
        menu(NULL);
    }
    while(i->NEXT != NULL) {
        i = i->NEXT;
    }
    if(i->NEXT==NULL){
        i->PREV->NEXT = NULL;
        free(i);
        menu(pheadNode);
    }
    

} //delete last added node

void searchAndDelete(Node **pheadNode){
    int inputOk; 
    int i =0;
    char searchTerm[25];
    while(1){
                
                if(scanf("%s", searchTerm)) //,printf("\n")
                    break;
                //empty stdin so we get a proper input.
                while(fgetc(stdin)== 1){
                    i=0;
                }
                i++;
                if(i%3 == 0||i==0)
                    printf(". \n");
                if(i==1)
                    printf("please insert a valid string:\n");
            }
            
    //trenger input validering! ! ! ! 
   // inputOk = scanf("%s", searchTerm);
     // Store head node
    if (*pheadNode != NULL){

        Node *i = *pheadNode, *prev = NULL; //node i = temporary

    
                            
        while (i->NEXT != NULL)
        {
            Node *next = i->NEXT; //i er her head -- next er no2

    
            if(strcmp(*i->VARENAVN, searchTerm)==0){
                if(i->PREV != NULL)
                    i->PREV = next->PREV;
                
                free(i);
                if(prev)
                    prev->NEXT = next;
                else
                    *pheadNode = next;
            }else
                prev = i;
            
            i=next;
    
        }
        menu(*pheadNode);
    }

    else{
        printf("Listen er allerede tom! \n");
        menu(NULL);
    }


} //delete all nodes with name "*Input*"

float sum(Node **pheadNode){
    float sum = 0;
    Node *i = malloc(sizeof(Node));
    memset(i, 0, sizeof(Node));
    if(pheadNode == NULL)
        return 0;
    for (i = *pheadNode; i != NULL; i = i->NEXT)
        sum+=i->PRIS*i->ANTALL;
    
    //printf("%.2f",sum);
    //menu(*pheadNode);
    free(i);
    return sum;
} //sum pris på alle varer i listen


void cleanUpAndExit(Node *pheadNode){
  //  Node *tmp = *pheadNode;
    while(pheadNode!= NULL){
        Node *tmp = pheadNode->NEXT;
        free(pheadNode);
        pheadNode = tmp;
    
    }
    exit(0);
    
}
