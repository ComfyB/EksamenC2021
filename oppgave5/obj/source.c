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
#include <syscall.h>// må aktiveres for feilsøking med syscall
#include <unistd.h>//for sleeep
/*
#33###############3
avslutter om quit er første ord!!!!
casting to single pointer er ass måte å gjøre det på!

*/

typedef struct Buffer{
  char input[11];
}Buffer;
pthread_mutex_t lock_x;

pthread_cond_t shared_x;
pthread_cond_t writing_status;
 

void *workThread(void *structPointer){
    
    Buffer *Buffer = structPointer;
    while(strncmp(Buffer->input,"quit",4)){
        
       // printf("Thread_1_Id: %ld\n",syscall(SYS_gettid));
        
        FILE    *outPut =     fopen("outPut.txt","a");
        fprintf (outPut,"%s", Buffer->input);
        fclose  (outPut);

        //kjører whileloopen når den får signal
        
        pthread_mutex_trylock   (&lock_x);
        pthread_cond_signal     (&writing_status);
        pthread_cond_wait       (&shared_x,&lock_x);
        pthread_mutex_unlock    (&lock_x);
    }
    pthread_cond_signal (&writing_status);
    printf              ("\nworkThread is Ready to Join!\n");
    pthread_exit        (0);  
}    
  
    


int main(){
    char *szInput;
    szInput = malloc(sizeof (char)*11);
    pthread_mutex_init  (&lock_x,NULL);
    pthread_cond_init   (&shared_x,NULL);
    pthread_cond_init   (&writing_status,NULL); 

    Buffer      *structBuffer = malloc(sizeof(Buffer));
   // *structBuffer->input =0; 
   
    pthread_t   thread_1;
   // *structBuffer->input = malloc(sizeof (char)*11);
   // printf("ThreadId: %ld",syscall(SYS_gettid));
    //szInput = fgets   (structBuffer->input,10,stdin);//take input
     

    pthread_create  (&thread_1, NULL, workThread, structBuffer);
    while(strncmp(structBuffer->input,"quit",4)){
        szInput = fgets   (structBuffer->input,10,stdin);//take input
        pthread_cond_signal     (&shared_x);//sender signal for å kjøre while loopen en gang
        pthread_cond_wait       (&writing_status,&lock_x);//kjører whileloopeb når den får signal
        
        //sleep(1);//for feilsøking av tråder
      
    } 
    
    pthread_cond_signal     (&shared_x);//sender signal for å kjøre while loopen en gang
    printf                  ("\nMain Thread Ready to Join!\n");
    pthread_join            (thread_1, NULL); 
    printf("joined threads");
    pthread_mutex_unlock    (&lock_x);
    pthread_mutex_destroy   (&lock_x);

    pthread_cond_destroy    (&shared_x);
    pthread_cond_destroy    (&writing_status);

  //  free        (structBuffer->input);
    free        (structBuffer);
    printf      ("\nCleanup Done!\n");
    
    return 0;
    
}