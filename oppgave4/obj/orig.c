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


typedef struct _MYHTTP { 
   int iHttpCode; 
   int iContentLength;
   bool bIsSuccess; 
   char szServer[16]; 
   char szContentType[16]; 
} MYHTTP;




MYHTTP* ProcessHttpHeader(char *pszHttp) {
   char* pszPtr;

   MYHTTP* pHttp = (MYHTTP*)malloc(sizeof(MYHTTP));

   if (!pHttp) return NULL;


   memset(pHttp, 0, sizeof(MYHTTP));
   pHttp->iHttpCode = atoi(pszHttp + strlen("HTTP/1.x "));
   if (pHttp->iHttpCode = 200) {
      pHttp->bIsSuccess = true;
   }
   pszPtr = strstr(pszHttp, "Server");
   
   
   if (pszPtr) {

   
      pszPtr += 6; 
   
      while (!isalpha(pszPtr[0]))
         pszPtr++;
      strchr(pszPtr, '\n')[0] = 0;
      strcpy(pHttp->szServer, pszPtr);

      pszPtr[strlen(pHttp->szServer)] = '\n';

   }
   pszPtr = strstr(pszHttp, "Content-Type");



   if (pszPtr) {
      pszPtr += 12; 
      while (!isalpha(pszPtr[0]))
         pszPtr++;
      strchr(pszPtr, '\n')[0] = 0;
      strncpy(pHttp->szContentType, pszPtr, 15);
      pszPtr[strlen(pHttp->szContentType)] = '\n';
   }
   pszPtr = strstr(pszHttp, "Content-Length");



   if (pszPtr) {
      pszPtr += 14; 
      while (!isdigit(pszPtr[0])) 
         pszPtr++;
      pHttp->iContentLength = atoi(pszHttp); 
   }
return pHttp;
}
int main(){

//MYHTTP *m = ProcessHttpHeader("HTTP/1.1 404 Not Found\r\nDate: Thu, 04 Nov 2021 22:27:23 GMT\r\nServer: Apache\r\nContent-Length: 196\r\nContent-Type: text/html; charset=iso-8859-1\r\nX-Varnish: 976359640\r\nAge: 0\r\nVia: 1.1 varnish (Varnish/7.0)\r\nConnection: keep-alive");
/* MYHTTP *m = ProcessHttpHeader("GET HTTP/3 200 OK\r\n
date: Sat, 06 Nov 2021 01:20:28 GMT\r\n
expires: -1
cache-control: private, max-age=0
content-type: text/html; charset=UTF-8
strict-transport-security: max-age=31536000
content-encoding: br
server: gws
content-length: 34559
x-xss-protection: 0
"); */
MYHTTP *m = ProcessHttpHeader("GET /pg3401/test.html HTTP/1.1\r\nHost: eastwillsecurity.com\r\n Server: Apache\r\nContent-Type: text/html\r\nContent-Length: 420 \r\n\r\n\r\n");
printf("content-length: %d\n",m->iContentLength);
printf("http - code: %d\n",m->iHttpCode);
printf("Is success?: %d\n",m->bIsSuccess);
printf("Content type: %s\n",m->szContentType);
printf("Server: %s\n",m->szServer);
//printf("Last-modified: %d", m->iLastModified);

return 0;
}