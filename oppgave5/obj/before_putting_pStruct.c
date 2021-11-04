/*Oppgave 5. Tråder (25 %)
I praktisk programmering er det ofte effektivt å legge tidkrevende operasjoner ut i arbeidstråder, eksempler på dette er 
filoperasjoner, nettverksoperasjoner og kommunikasjon med eksterne enheter. I denne oppgaven skal du simulere slike operasjoner 
med et mindre datasett.

######
Du skal lage en applikasjon som består av 2 tråder, hovedtråden (som startet main) og en arbeidstråd som skal skrive data. Når 
hovedtråden starter skal den først starte arbeidstråden med mekanismer for tråd-kommunikasjon og synkronisering. Hovedtråden
og arbeidstråden skal ha et minneområde med plass til 10 tegn. (Det kan være en struct som også inneholder andre kontrolldata 
som for eksempel antall tegn i bufferet og annet studenten finner nyttig – men ikke mer enn 10 tegn som en tekstbuffer. Det er 
lov for en slik struct å inneholde char a[11] hvis det ellevte tegnet kun brukes til en 0-terminering.)
Hovedtråden skal be brukeren gjennom terminal vinduet om å skrive inn en tekststreng og avslutte med [enter]. 
Når brukeren har skrevet inn en streng skal hovedtråden sende strengen over til arbeidstråden (gjennom flere sykluser ved hjelp 
av minneområdet beskrevet over, og signaler eller andre synkroniseringsmekanismer hvis mer enn 10 tegn skrives inn av brukeren). 
Arbeidstråden skal lagre denne tekststrengen til en fil (linjeskift ‘\n’ skal skrives når hele tekststrengen er skrevet til 
filen). Når operasjonen er fullført skal hovedtråden be brukeren om en ny tekststreng, eller hvis brukeren oppgir «quit» skal 
applikasjonen avslutte. Applikasjonen skal gå slik i en loop og sende tekst over til arbeidstråden helt frem til brukeren avslutter, 
hver tekststreng skal appendes (legges til på slutten) filen.
*/

//Arbeidstråd som lagrer data
//Når bruker skriver inn en streng skal den sendes til arbeidstråden og trykker enter (append)
//arbeidstråden skal skrive til fil input fra bruker, end med \n
//avsluttes med å skrive inn quit
//loop til den avsluttes
//hver streng skal være appended til slutten av fila
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct Buffer{
    char* input[11];

}Buffer;



void *workThread(void *structPointer){
    Buffer *Buffer = (struct Buffer*)structPointer;
    
    FILE *outPut = fopen("outPut.txt","a");
    
    fprintf(outPut, "%s", *Buffer->input);
    fclose(outPut);
    return NULL;
}

int main(){
    Buffer *Buffer = malloc(sizeof(Buffer));
    pthread_t thread_id;

    pthread_create(&thread_id, NULL, workThread, &Buffer);

    while(strncmp(&Buffer->input,"quit",4)){
        workThread(&Buffer);
        fgets(Buffer->input,10,stdin);
            //scanf("%s", &Buffer->input);
            //printf("\n%s\n",Buffer->input);
    }
    pthread_join(thread_id, NULL);
    free(Buffer);
    
    return 0;
    
}