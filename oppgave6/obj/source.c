#include "source.h"
int main(int argC, char* argV[])
{
    char* ip;
    if (argC <0)
        ip =  getIpaddr("eastwillsecurity.com");
    else
        ip= getIpaddr(argV[0]);
    int socketConnection, n, sendbytes;
    struct sockaddr_in serveraddress;

    char sendBuffer[MAXLENGTH]; //arrays with macro maxline of 4046 for recieving and sending data.
    char recvBuffer[MAXLENGTH];
    socketConnection = socket(AF_INET, SOCK_STREAM, 0); //create the socket

    if (socketConnection < 0)
        errorMsg("\nSocketen ble ikke initialisert riktig\n");

    memset(&serveraddress, 0, sizeof(serveraddress));

    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(SERVER_PORT); //htons ->> network standard byteorder little endian /big endian for portability

    if (inet_pton(AF_INET, ip, &serveraddress.sin_addr) <= 0) //converting address into binary representation of the address with int_pton
        errorMsg("\nproblem med konvertering av ip til binært\n");

    printf("\nipen er konvertert til binært\n");

    if (connect(socketConnection, (SOCKETADDRESS *)&serveraddress, sizeof(serveraddress)) < 0) //create the connection to the socket
        errorMsg("\n feil under tilkobling til ip\n");

    printf("\nkoblet til to ip\n");

    sprintf(sendBuffer, "GET /pg3401/test.html HTTP/1.1\r\nConnection: close\r\nHost: eastwillsecurity.com\r\n\r\n"); //writes the header into sendbuffer
    sendbytes = strlen(sendBuffer);

    if (write(socketConnection, sendBuffer, sendbytes) != sendbytes) //writes through the socket a get req to the server.
        errorMsg("\nfeil under sending av header\n");

    printf("\nheader sent, venter på svar\n\n");
    memset(recvBuffer, 0, MAXLENGTH); //remove old trash from memory

    while ((n = read(socketConnection, recvBuffer, MAXLENGTH - 1)) > 0) //reads the recieved data from the server. then prints to terminal
    {
        printf("%s", recvBuffer);
    }
    if (n < 0)
        errorMsg("\ningen svar fra server!\n");

    close(socketConnection); //cleanup
    printf("\nferdig med å laste siden, avslutter\n");
    free(ip); //free the malloc from start.
    return 0;
} //main() end
//function that prints errormsg and returns 1
int errorMsg(char *error)
{
    printf("%s\n", error);
    return 1;
} //errorMsg() end

char* getIpaddr(char* url){
    int i;
    struct hostent *add = gethostbyname("eastwillsecurity.com"); //get host by name, will return a struct with addr list  "database entry of a host"
    struct in_addr **addr_list;                                  //Make address into network byte order by combining NET with host local addr.
    char *ip = malloc(sizeof(int *) * 33);

    if (add)
    {
        addr_list = (struct in_addr **)add->h_addr_list; //h_addr_list gives a alist of returned host values

        for (i = 0; addr_list[i] != NULL; i++)
        {
            strcpy(ip, inet_ntoa(*addr_list[i])); //inet_ntoa converts ip to string and strcpy copies it into a variable called ip.
            printf("ip found: %s", ip);
        }
    }
    else //if hosts is not found we go to a hardcoded ip to the server.
    {
        strcpy(ip, SERVERIP);
        printf("ip not found, defaulting to hardcoded ip.");
    } //end of the part used to get ip from host.
return ip;
}