#include "source.h"

int main(void)
{

    DLL *dll = initDLL(); //making a struct to hold head and tail of the list
    int running = 1;      //int that changes when menu returns 0. Then whileloop stops running
    while (running)
    {
        running = menu(dll);
    }
    free(dll); //free the dll when all is done.

    return 0;
}
//function for memory allocation and make a doubly linked list this function is only called in main in this program
//but as its a function it makes it easier to scale the program to more than one list if needed later. returns a
//pointer to a struct that has pointers to head&tail.
DLL *initDLL(void)
{
    DLL *newList = malloc(sizeof(*newList));
    if (newList == NULL) //check if malloc has failed
    {
        printf("error allocation mem for dll");
        exit(1);
    }
    memset(newList, 0, sizeof(*newList)); //clear the meory
    newList->head = NULL;                 //sets head and tail to NULL as we no nodes are created yet.
    newList->tail = NULL;
    return newList; //return pointer to the newly created DLL
}
//function to create a node in the dll. mallocs memory and testes wether it faled or not before memsetting to zero and returning the node.
Node *initNode(void)
{

    Node *newNode = malloc(sizeof(*newNode));
    if (newNode == NULL)
    {
        printf("error allocation of mem for node!");
        exit(1);
    }
    memset(newNode, 0, sizeof(*newNode));

    return newNode; //returns pointer to the newly created node
}
//menu which takes a DLL as argument.
int menu(DLL *list)
{
    char choice;
    printf("\n*********************\n");
    printf("*       Menu        *");
    printf("\n*********************\n");
    printf("Skriv inn et valg og bekreft med enter:\n");
    printf("1. Legg til vare i slutten av listen:\n");
    printf("2. Slett det siste elementet i listen\n");
    printf("3. Fjern alle varer med navn fra listen: \n");
    printf("4. Sum av alle varer: \n");
    printf("5. Kvittering\n");
    printf("6. Exit program\n");
    while (1) //input whilw 1, will break out of the loop if the inpud is valid.
    {
        if (scanf("%c", &choice))
            ;
        if (choice >= '1' && choice <= '6')
            break;
        if (choice != '\n')
            printf("%s is not a valid menu option!\n", &choice);
    }
    switch (choice) //we already know that the choice is valid. so now the menu calls the different functions needed in the dll
    {               //all the cases return 1, so that the while in main takes as is whatever the menu function returns still runs.
    case '1':
        inputValidation(list); //new node input
        return 1;
    case '2':
        delNode(list, list->tail); //delets the tail with the delete function.
        return 1;
    case '3':
        deleteWithKey(list); //starts the funcion which delete with key
        return 1;
    case '4':
        printf("\nTotal: %.2f\n", sum(list)); //returns the sum and prints it in terminal.
        return 1;
    case '5':
        printList(list); //print the entire list
        return 1;
    case '6':
        cleanExit(list); //runs the cleanup process to free memory and void leaks before setting "running" in main to 0, which exits the loop in main
        return 0;
    default: //should never happen but in case something went wrong we delete the list and exit the program
        printf("\nsomething went wrong cleaning and exiting\n");
        cleanExit(list);
        return 0;
    }
    cleanExit(list); //should never happen but in case something went wrong we delete the list and exit the program
    printf("\nsomething went wrong cleaning and exiting\n");
    return 0;
}
//Using input from the user this function compares the node->ITEMNAME if its the same as an input. When matched it sends the node pointer to the
//delete fnction
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
    i = list->head;         //sets i to head
    while (i->NEXT != NULL) //then count through the nodes
    {
        tmp = i->NEXT;                      //save temporary as you lose the address when deleting i->NEXT
        if (strcmp(*i->ITEMNAME, key) == 0) //using strcmp to see if the key and node->VARENAVM matches.
            delNode(list, i);
        i = tmp;
    }
}
//function to iterate through the list and print as it goes through. will break the look of the recipt if the name of the item is longer than
//name plus tab. Creates a temporary pointer so we can update it and pull data from all nodes. Then sends the list to the sum function which
//returns the total
void printList(DLL *list)
{
    Node *i;
    printf("*********************************\n");
    printf("navn\tpris\tQUANTITY\tvaretotal\n");
    printf("_________________________________\n\n");

    for (i = list->head; i != NULL; i = i->NEXT)
    {
        //printing the recipt
        printf("%s\t", *i->ITEMNAME);
        printf("%.2f\t", i->PRICE);
        printf("%d\t", i->QUANTITY);
        printf("%.2f\n", (i->PRICE * i->QUANTITY));
    }
    printf("_________________________________\n\n");

    printf("\033[0;31m\t\tTotal \t%.2f;-\n\033[0;0m", sum(list)); //playing with linux terminal settings where \033 is the escape character [0;31m gives the color
    printf("*********************************\n");
}
//function for inputchecking passing arguments to a function for appending the node. Reasoning behind making it a seperate function is that
//if you want to extend the program later with other ways of inserting the values of the node that is not just to the end of the list, we can use
//the same inputvalidator
void inputValidation(DLL *list)
{

    char *name = malloc(sizeof(char) * 25);
    if (name == NULL)
    {
        printf("error while allocation of navn variable");
        exit(1);
    }
    //local variables for the inputted values
    float price;
    int quantity;
    int i = 0;

    printf("\n*********************\n");

    printf("Oppgi et navn og trykk enter:  ");
    if (scanf("%25s", name))
        ;
    printf("\nOppgi en pris og trykk enter:  ");
    while (1) //while loop that gets the break; keyword escaping the loop if scanf gets a float as input, if input is valid scanf returns 1;
    {

        if (scanf("%f", &price)) //,printf("\n")
            break;
        //empty stdin so we get a proper input.
        while (fgetc(stdin) == 1)
        {
            i = 0;
        }
        i++;
        if (i % 3 == 0 || i == 0) //print a dot every third character cleared from stdin.
            printf(". clearing cache\n");
        if (i == 1)
            printf("please insert a valid number:\n"); // written once for proper input.
    }

    printf("\nOppgi mengde varer og trykk enter:  ");
    while (1) //same while loop as over just with an input of int and not float.
    {

        if (scanf("%d", &quantity)) //,printf("\n")
            break;
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
    appendNode(list, name, price, quantity); //pass the values to the function that appends a node to the list
}

void appendNode(DLL *list, char *navn, float price, int QUANTITY)
{

    Node *newNode = initNode();

    *newNode->ITEMNAME = navn;
    newNode->PRICE = price;
    newNode->QUANTITY = QUANTITY;

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
        list->tail = NULL;
        list->head = NULL;
        free(*_delete->ITEMNAME);
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

    free(*_delete->ITEMNAME);
    free(_delete);
}
float sum(DLL *list)
{
    float sum = 0;
    Node *i;

    for (i = list->head; i != NULL; i = i->NEXT)
        sum += i->PRICE * i->QUANTITY;

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
