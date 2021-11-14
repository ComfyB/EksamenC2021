/*
Du har fått beskjed om å utføre feilretting av denne funksjonen, du får beskjed om at Content-Length ikke blir satt riktig i den 
returnerte structen. (Funksjonen kalles med en tekstbuffer som inneholder HTTP REPLY fra en webserver, og structen blir frigitt av
funksjonen som kaller funksjonen.)
Det viser seg at koden faktisk inneholder 3 feil. Du skal rette alle feilene, i besvarelsen skal du ha den feilrettede funksjonen, 
og en main metode som tester funksjonen (der hvor det er mulig bør main kalle funksjonen på en slik måte at den fremprovoserer feilene 
som var i den opprinnelige koden. I tekstbesvarelsen skal du kort forklare hvilke feil du fant, hvorfor dette er feil og forklare 
hvordan du løste dem.
Det er også ønsket at en ny verdi legges til i structen som sier hvilket årstall websiden sist ble endret (Last-Modified), du skal 
skrive denne koden og legge den til i funksjonen.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct _MYHTTP
{
   int iHttpCode;
   int iContentLength;
   bool bIsSuccess;
   char szLastModified[30];
   char szServer[16];
   char szContentType[16];
} MYHTTP;
//function which takes a http Header and parses the info to variables saaved in a struct of type MYHTTP.
MYHTTP *ProcessHttpHeader(char *pszHttp)
{
   char *pszPtr;   //pointer used for where to start in the header later in the function
   int copyLength; //added for overflowprotection.

   MYHTTP *pHttp = (MYHTTP *)malloc(sizeof(MYHTTP));

   if (!pHttp) //if malloc fails. return NULL from function
      return NULL;

   memset(pHttp, 0, sizeof(MYHTTP)); //clean memory so you dont get the content of the old memory messing with your struct.

   pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x ")); //gets the hhtpCode from the header

   if (pHttp->iHttpCode == 200) //compares the httpcode that was parsed in previous line. Then compares it with 200, which is ok/succsess, then sets
   {                            //bIsSuccess to true. The code was using a single = and therefore was always true and changed the content of the struct.
      pHttp->bIsSuccess = true; //the fix is shown by returning 404 in terminal.
   }

   pszPtr = strstr(pszHttp, "Server"); //search for the word server, thens sets pszPtr to the location of it.

   if (pszPtr) //if the word if found do this
   {
      pszPtr += 6;                //jumps the length of the word server
      while (!isalpha(pszPtr[0])) //jumps to the location where pszpointer givex alpha character. jumps past : and whitespace.
         pszPtr++;
      copyLength = 0;
      while (pszPtr[copyLength] != '\n') //Checks where newline character. and gives copylength a value
         copyLength++;
      if (copyLength < 16)                             //checks if the string is longer than the size of the memeory allocated in the struct. if it is it will only copy the first 15 characters
         strncpy(pHttp->szServer, pszPtr, copyLength); //dis fixed
      else
         strncpy(pHttp->szServer, pszPtr, 15); //dis fixed

      //strncpy(pHttp->szServer, pszPtr,15);
      //strchr(pszPtr, '\n')[0] = 0;
      //pszPtr[strlen(pHttp->szServer)] = '\n';  // has no protection for overflow and crashes the program.
   }

   pszPtr = strstr(pszHttp, "Last-Modified");
   if (pszPtr)
   {
      pszPtr += 13;
      while (!isalpha(pszPtr[0]))
         pszPtr++;

      copyLength = 0;
      while (pszPtr[copyLength] != '\n')
         copyLength++;
      if (copyLength < 30)
         strncpy(pHttp->szLastModified, pszPtr, copyLength);
      else
         strncpy(pHttp->szLastModified, pszPtr, 29);
   }

   pszPtr = strstr(pszHttp, "Content-Type");
   if (pszPtr)
   {
      pszPtr += 13;
      while (!isalpha(pszPtr[0]))
         pszPtr++;
      copyLength = 0;
      while (pszPtr[copyLength] != '\n')
         copyLength++;
      if (copyLength < 30)
         strncpy(pHttp->szContentType, pszPtr, copyLength); //
      else
         strncpy(pHttp->szContentType, pszPtr, 15); // 
         
     /*strchr(pszPtr, '\n')[0] = 0; //bad permisssions on mem access
      strncpy(pHttp->szContentType, pszPtr, 15);
      pszPtr[strlen(pHttp->szContentType)] = '\n'; //bad permissons for mapped region */
   }
  

   

   pszPtr = strstr(pszHttp, "Content-Length");
   if (pszPtr)
   {
      pszPtr += 14;
      while (!isdigit(pszPtr[0]))
         pszPtr++;
      pHttp->iContentLength = atoi(pszPtr); //this one was taking pszHttp as input and not the correct pointer. which led to it not parsing content length
   }                                         //easy swap with pszPtr and the funciton works as intended.
   return pHttp;
}//processhttphead() end;
int main(void)
{
   MYHTTP *m = (MYHTTP *)malloc(sizeof(MYHTTP)); //initalize ste struct to store the data. return from the  header parsing function.

   m = ProcessHttpHeader("HTTP/1.1 404 Not Found\r\nDate: Thu, 04 Nov 2021 22:27:23 GMT\r\nServer: Apache\r\nContent-Length: 196\r\nLast-Modified: Wed, 21 Oct 2021 01:23:45 GMT\r\nContent-Type: text/html; charset=iso-8859-1\r\nX-Varnish: 976359640\r\nAge: 0\r\nVia: 1.1 varnish (Varnish/7.0)\r\nConnection: keep-alive");

   printf("Content-Length:\t%d \t\t\t\t\t# fixed by swapping the pointer to the correct one\n", m->iContentLength);
   printf("Http - code:  \t%d \t\t\t\t\t# got set to 200 in the if statement\n", m->iHttpCode);
   printf("Last-Modified: \t%s \t\t# made as task wanted implementation of\n", m->szLastModified);
   printf("Is success?: \t%d \t\t\t\t\t# used to always be Yes due to non strict comparitor. Which in c just updates the value to 200 then returns true\n", m->bIsSuccess);
   printf("Content-Type: \t%s \t\t\t# used to always be 0, due to the wrong variable\n", m->szContentType);
   printf("Server: \t%s \n", m->szServer);

   free(m);
   return 0;
}