#include "source.h"

int main(void)
{

    int sockFd, n, sendbytes;
    struct sockaddr_in servaddr;

    char sendline[MAXLINE];
    char recvline[MAXLINE];
    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockFd < 0)
        errorMsg("\nSocketen ble ikke initialisert riktig\n");

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT); //hgons ->> network standard byteorder

    if (inet_pton(AF_INET, SERVERIP, &servaddr.sin_addr) <= 0)
        errorMsg("\nproblem med konvertering av ip til binært\n");

    printf("\nipen er konvertert til binært\n");

    if (connect(sockFd, (SA *)&servaddr, sizeof(servaddr)) < 0)
        errorMsg("\n feil under tilkobling til ip\n");

    printf("\nkoblet til to ip\n");

    sprintf(sendline, "GET /pg3401/test.html HTTP/1.1\r\nHost: eastwillsecurity.com\r\n\r\n"); //maybe write here
    sendbytes = strlen(sendline);

    if (write(sockFd, sendline, sendbytes) != sendbytes)
        errorMsg("\nfeil under sending av header\n");

    printf("\nheader sent, venter på svar\n");
    memset(recvline, 0, MAXLINE);

    while ((n = read(sockFd, recvline, MAXLINE - 1)) > 0)
    {
        printf("%s", recvline);
    }
    if (n < 0)
        errorMsg("\ningen svar fra server!\n");

    close(sockFd);
    printf("\nferdig med å laste siden, avslutter\n");

    return 0;
}

int errorMsg(char *error)
{
    printf("%s\n", error);
    return 1;
}