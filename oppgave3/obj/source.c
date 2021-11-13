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
typedef struct DLL
{
    Node* head;
    Node* tail;
}DLL;




DLL* initDLL(void);
Node * initNode(void);

float sum(DLL *list);

int menu(DLL *list);
void printList(DLL *list);
void handleInput(DLL *list);
void cleanExit(DLL *list);
void deleteWithKey(DLL *list);
void delNode(DLL* list, Node *delete);
void * appendNode(DLL *list, char* navn, float pris, int antall);


DLL * initDLL(void){
    DLL *newList = malloc(sizeof(*newList));
    if(newList == NULL){
        printf("error allocation mem for dll");
    }
    memset(newList, 0 ,sizeof(*newList));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

int main(void){
    DLL *dll = initDLL();
    int running = 1;
    while(running){
        running = menu(dll);
    }
    free(dll);
return 0;
}

Node * initNode(void){
    
    Node* newNode = malloc(sizeof(*newNode));
        if(newNode==NULL){
            printf("error allocation of mem for node exiting!");
            exit(1);}
    memset(newNode,0,sizeof(*newNode));

    return newNode;
}

int menu(DLL *list){
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
                    handleInput(list);
                    return 1;
                    
            case '2':
                    delNode(list,list->tail);
                    return 1;
            case '3':
                    deleteWithKey(list);
                    return 1;
            case '4':
                    printf("\nTotal: %2.f\n",sum(list));
                    return 1;
            case '5':
                    printList(list);
                    return 1;
            case '6':
                   cleanExit(list);
                   return 0;
            default:
                    printf("something went wrong");   
                    //cleanUpAndExit(pheadNode); 
        }
}
void deleteWithKey(DLL *list){
    if(list->head ==NULL){
        printf("\nlisten er allerede tom!\n");
        return;
    }
    Node *i=initNode();
    Node *tmp=initNode();
    char key[25];
    if(scanf("%s",key));
    for (i = list->head; i != NULL; i = tmp->NEXT){
        if(strcmp(*i->VARENAVN,key)==0){
            tmp->NEXT=i->NEXT;
            printf("deleting: %s",key);
            delNode(list,i);
        }
            
    
    } 
}
void printList(DLL *list){
    Node *i;
    printf("*********************************\n");
    printf("navn\tpris\tantall\tvaretotal\n");
    printf("_________________________________\n\n");

    for (i = list->head; i != NULL; i = i->NEXT){
  
        printf("%s\t", *i->VARENAVN);
        printf("%.2f\t", i->PRIS); 
        printf("%d\t", i->ANTALL); 
        printf("%.2f\n",(i->PRIS * i->ANTALL));
    }
    printf("_________________________________\n\n");

    printf("\033[0;31m\t\tTotal \t%.2f\n\033[0;0m",sum(list));
    printf("*********************************\n");
    
} //print all nodes into terminal

void handleInput(DLL *list){

    char navn [25];
    if(navn==NULL)
        exit(1);
    float pris;
    int antall;
    int inputOk;
    int i=0;

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
            
       
        
    appendNode(list, navn, pris, antall);
    
    

}


void *appendNode(DLL* list, char* navn, float pris, int antall){
      
    Node *newNode = initNode();
    
    *newNode->VARENAVN = navn;
    newNode->PRIS = pris;
    newNode->ANTALL = antall;

    
    if(list->head == NULL){
        newNode->NEXT = NULL;
        newNode->PREV = NULL;
        list->head = newNode;
        list->tail = newNode;
    }else{
        list->tail->NEXT = newNode;
        newNode->PREV=list->tail;
        newNode->NEXT=NULL;
        list->tail = newNode;
    }
   
} //add a node to the end of the list
void delNode(DLL *list, Node *delete){

    if(list->head == NULL || delete == NULL)
        return;
    if(list->head == delete && delete->NEXT == NULL){
        list->head = NULL;
        free(delete);
        return;
    }
    if(list->head == delete){
        list->head = delete->NEXT;
        delete->NEXT->PREV=NULL;
    }    
    
    if(delete->NEXT != NULL){
        delete->NEXT->PREV = delete->PREV;

    }    
    if(delete->PREV != NULL)
        delete->PREV->NEXT = delete->NEXT;

    if(delete->NEXT == NULL)
        list->tail= delete->PREV;

    free(delete); 
    

}
float sum(DLL* list){
    float sum = 0;
    Node *i = initNode();

    for (i = list->head; i != NULL; i = i->NEXT)
        sum+=i->PRIS*i->ANTALL;
    
    free(i);
    return sum;
} //sum pris på alle varer i listen


void cleanExit(DLL* list){
    Node *i;
    Node *tmp = initNode();
    for (i = list->head; i != NULL; i = tmp->NEXT){
            tmp->NEXT=i->NEXT;
            delNode(list,i);
        }
    free(tmp);
}
 