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
   char szContentType[30];
} MYHTTP;

MYHTTP *ProcessHttpHeader(char *pszHttp)
{
   char *pszPtr;
   int copyLength;

   MYHTTP *pHttp = (MYHTTP *)malloc(sizeof(MYHTTP));

   if (!pHttp)
      return NULL;

   memset(pHttp, 0, sizeof(MYHTTP));

   pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x "));

   if (pHttp->iHttpCode == 200)
   {                            //dis is fixed non strct comparator
      pHttp->bIsSuccess = true; //was always true
   }

   pszPtr = strstr(pszHttp, "Server");

   if (pszPtr)
   {
      pszPtr += 6;
      while (!isalpha(pszPtr[0]))
         pszPtr++;
      copyLength = 0;
      while (pszPtr[copyLength] != '\n')
         copyLength++;
      if (copyLength < 16)
         strncpy(pHttp->szServer, pszPtr, copyLength); //dis fixed
      else
         strncpy(pHttp->szServer, pszPtr, 15); //dis fixed

      //pszPtr[strlen(pHttp->szServer)] = '\n';  // has no protection for overflow
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
         strncpy(pHttp->szLastModified, pszPtr, copyLength); //feil eller ikke?
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
      // printf("%s",pszPtr);
      if (copyLength < 30)
         strncpy(pHttp->szContentType, pszPtr, copyLength); //feil eller ikke?
      else
         strncpy(pHttp->szContentType, pszPtr, 29); //feil eller ikke?
   }

   pszPtr = strstr(pszHttp, "Content-Length");
   if (pszPtr)
   {
      pszPtr += 14;
      while (!isdigit(pszPtr[0]))
         pszPtr++;
      pHttp->iContentLength = atoi(pszPtr); //dis fix
   }
   return pHttp;
}
int main(void)
{
   MYHTTP *m = (MYHTTP *)malloc(sizeof(MYHTTP));

   m = ProcessHttpHeader("HTTP/1.1 404 Not Found\r\nDate: Thu, 04 Nov 2021 22:27:23 GMT\r\nServer: Apache\r\nContent-Length: 196\r\nLast-Modified: Wed, 21 Oct 2021 01:23:45 GMT\r\nContent-Type: text/html; charset=iso-8859-1\r\nX-Varnish: 976359640\r\nAge: 0\r\nVia: 1.1 varnish (Varnish/7.0)\r\nConnection: keep-alive");

   printf("Content-Length: %d\n", m->iContentLength);
   printf("Http - code: %d\n", m->iHttpCode);
   printf("Last-Modified: %s\n", m->szLastModified);
   printf("Is success?: %d\n", m->bIsSuccess);
   printf("Content-Type: %s\n", m->szContentType);
   printf("Server: %s\n", m->szServer);

   free(m);
   return 0;
}