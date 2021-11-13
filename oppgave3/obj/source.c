#include "source.h"

int main(void)
{
    DLL *dll = initDLL();
    int running = 1;
    while (running)
    {
        running = menu(dll);
    }
    free(dll);
    return 0;
}

DLL *initDLL(void)
{
    DLL *newList = malloc(sizeof(*newList));
    if (newList == NULL)
    {
        printf("error allocation mem for dll");
    }
    memset(newList, 0, sizeof(*newList));
    newList->head = NULL;
    newList->tail = NULL;
    return newList;
}

Node *initNode(void)
{

    Node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL)
    {
        printf("error allocation of mem for node exiting!");
        exit(1);
    }
    memset(newNode, 0, sizeof(*newNode));

    return newNode;
}

int menu(DLL *list)
{
    char choice;
    printf("\n*********************\n");
    printf("*       Menu        *");
    printf("\n*********************\n");
    printf("Skriv inn et valg og bekreft med enter:\n");
    printf("1. Legg til vare i slutten av listen:\n");
    printf("2. Slett forrige/ angre forrige element\n");
    printf("3. Fjern alle varer med navn fra listen: \n");
    printf("4. Sum av alle varer: \n");
    printf("5. Kvittering\n");
    printf("6. Exit program\n");
    while (1)
    {
        if (scanf("%c", &choice))
            ;
        if (choice >= '1' && choice <= '6')
            break;
        if (choice != '\n')
            printf("%s is not a valid menu option!\n", &choice);
    }
    switch (choice)
    {
    case '1':
        handleInput(list);
        return 1;
    case '2':
        delNode(list, list->tail);
        return 1;
    case '3':
        deleteWithKey(list);
        return 1;
    case '4':
        printf("\nTotal: %2.f\n", sum(list));
        return 1;
    case '5':
        printList(list);
        return 1;
    case '6':
        cleanExit(list);
        return 0;
    default:
        printf("something went wrong");
        cleanExit(list);
        return 0;
    }
    cleanExit(list);
    return 0;
}
void deleteWithKey(DLL *list)
{
    if (list->head == NULL)
    {
        printf("\nlisten er allerede tom!\n");
        return;
    }
    Node *i;
    Node *tmp;
    char key[25];
    if (scanf("%s", key))
        ;
    i = list->head;
    while (i->NEXT != NULL)
    {
        tmp = i->NEXT;
        if (strcmp(*i->VARENAVN, key) == 0)
            delNode(list, i);
        i = tmp;
    }
    free(i);
}
void printList(DLL *list)
{
    Node *i = initNode();
    printf("*********************************\n");
    printf("navn\tpris\tantall\tvaretotal\n");
    printf("_________________________________\n\n");

    for (i = list->head; i != NULL; i = i->NEXT)
    {

        printf("%s\t", *i->VARENAVN);
        printf("%.2f\t", i->PRIS);
        printf("%d\t", i->ANTALL);
        printf("%.2f\n", (i->PRIS * i->ANTALL));
    }
    printf("_________________________________\n\n");

    printf("\033[0;31m\t\tTotal \t%.2f;-\n\033[0;0m", sum(list));
    printf("*********************************\n");

} //print all nodes into terminal

void handleInput(DLL *list)
{

    char *navn = malloc(sizeof(char) * 25);

    if (navn == NULL)
        exit(1);

    float pris;
    int antall;
    int i = 0;

    printf("\n*********************\n");

    printf("Oppgi et varenavn og trykk enter:  ");
    if (scanf("%25s", navn))
        ;
    printf("\nOppgi en pris og trykk enter:  ");
    while (1)
    {

        if (scanf("%f", &pris)) //,printf("\n")
            break;
        //empty stdin so we get a proper input.
        while (fgetc(stdin) == 1)
        {
            i = 0;
        }
        i++;
        if (i % 3 == 0 || i == 0)
            printf(". \n");
        if (i == 1)
            printf("please insert a valid number:\n");
    }

    printf("\nOppgi antall varer og trykk enter:  ");
    while (1)
    {

        if (scanf("%d", &antall)) //,printf("\n")
            break;
        //empty stdin so we get a proper input.
        while (fgetc(stdin) == 1)
        {
            i = 0;
        }
        i++;
        if (i % 3 == 0 || i == 0)
            printf(". clearing cache\n");
        if (i == 1)
            printf("please insert a valid number:\n");
    }
    appendNode(list, navn, pris, antall);
}

void appendNode(DLL *list, char *navn, float pris, int antall)
{

    Node *newNode = initNode();

    *newNode->VARENAVN = navn;
    newNode->PRIS = pris;
    newNode->ANTALL = antall;

    if (list->head == NULL)
    {
        newNode->NEXT = NULL;
        newNode->PREV = NULL;
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        list->tail->NEXT = newNode;
        newNode->PREV = list->tail;
        newNode->NEXT = NULL;
        list->tail = newNode;
    }
} //add a node to the end of the list
void delNode(DLL *list, Node *_delete)
{

    if (list->head == NULL || _delete == NULL)
        return;
    if (list->head == _delete && _delete->NEXT == NULL)
    {
        list->head = NULL;
        free(*_delete->VARENAVN);
        free(_delete);
        return;
    }
    if (list->head == _delete)
    {
        list->head = _delete->NEXT;
        _delete->NEXT->PREV = NULL;
    }

    if (_delete->NEXT != NULL)
        _delete->NEXT->PREV = _delete->PREV;

    if (_delete->PREV != NULL)
        _delete->PREV->NEXT = _delete->NEXT;

    if (_delete->NEXT == NULL)
        list->tail = _delete->PREV;

    free(*_delete->VARENAVN);
    free(_delete);
}
float sum(DLL *list)
{
    float sum = 0;
    Node *i = initNode();

    for (i = list->head; i != NULL; i = i->NEXT)
        sum += i->PRIS * i->ANTALL;

    free(i);
    return sum;
} //sum pris på alle varer i listen

void cleanExit(DLL *list)
{
    Node *i;
    Node *tmp = initNode();
    for (i = list->head; i != NULL; i = tmp->NEXT)
    {
        tmp->NEXT = i->NEXT;
        delNode(list, i);
    }
    free(tmp);
}
