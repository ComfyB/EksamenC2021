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

//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


int main(){
ProcessHttpHeader("YOyooYOYoyoOY");
return 0;
}
typedef struct _MYHTTP {
   int iHttpCode; 
   int iContentLength;   
   bool bIsSuccess; 
   char szServer[16]; 
   char szContentType[16]; 
   int iLastModified; //added last modified
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