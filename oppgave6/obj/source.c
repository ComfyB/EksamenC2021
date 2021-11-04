/* Oppgave 6. Nettverk (20 %)
Du skal i denne oppgaven lage en enkelt nettleser (browser). Applikasjonen skal hente data fra en reel webserver på internett, 
hvilket betyr at maskinen (og VMen hvis du kjører Linux i en VmWare maskin slik vi har brukt i undervisningen) må ha internett tilgang
når du løser oppgaven.
Oppgaven skal ikke løses ved bruk av Curl eller andre tredjepartsbiblioteker, og skal ikke basere seg på wget eller tilsvarende fra 
operativsystemet – kun bruk av Sockets slik vi har lært på forelesning 11 om Nettverk vil gi poeng på oppgaven.
Applikasjonen (den enkle browseren) skal laste ned følgende URL:
   «http://www.eastwillsecurity.com/pg3401/test.html»
Applikasjonen kan startes uten parameter, og main metoden kan hardkode protokoll TCP, port nummer 80 og server manuelt (du kan også
hardkode IP adressen til www.eastwillsecurity.com hvis du ønsker). Klient applikasjonen skal CONNECTE til oppgitt port på webserveren, 
og sende en HTTP GET pakke til URLen som oppgitt over.
Klient applikasjonen skal så lese svaret den får tilbake fra webserveren, og skrive ut websiden som kommer tilbake i terminal vinduet, 
før den avslutter. */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
//#include <sys/types.h>
#include <arpa/inet.h>
#include <linux/in.h>

#define SERVER_PORT 80
#define MAXLINE 3096
#define SA struct sockaddr
#define WEBADDR "77.111.240.75"
int errorHandling(){
    printf("sumthingswron");
}

int main(){
   // char* getreq = "GET /pg3401/test.html HTTP/1.1\r\n";
   // char* domain = "http://www.eastwillsecurity.com/pg3401/test.html";
    int sockFd, n, sendbytes;
    struct sockaddr_in servaddr;
    char    sendline[MAXLINE];
    char    recvline[MAXLINE];
    sockFd = socket(AF_INET,SOCK_STREAM,0);
    if(sockFd < 0) 
        printf("socket not opened properly");
    bzero(&servaddr, sizeof(servaddr));
    //struct sockaddr_in saAddr = {0};
    //int iPort = atoi("80");
   // saAddr.sin_family;
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERVER_PORT);//hgons ->> network standard byteorder
    //connect()
    if(inet_pton(AF_INET,"77.111.240.75",&servaddr.sin_addr)<=0)
        errorHandling();
    if(connect(sockFd, (SA*)&servaddr,sizeof(servaddr))<0)
        errorHandling();

    sprintf(sendline, "GET /pg3401/test.html HTTP/1.1\r\n");//maybe write here
    sendbytes = strlen(sendline);

    if(write(sockFd, sendline, sendbytes)!= sendbytes)
        errorHandling();

    memset(recvline,0,MAXLINE);

    while ((n=read(sockFd,recvline,MAXLINE-1))>0)
        {
            printf("%s",recvline);
        }
        if(n<0)
            errorHandling;
    exit(0);
    {
        /* code */
    }
    

}