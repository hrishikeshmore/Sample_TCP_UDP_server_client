#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<strings.h>
#include <stdio.h>
#include <arpa/inet.h>
int main(int argc, char *argv[])
{
    int sock, length, fromlen, n;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];
    int pn = atoi(argv[1]);
    //printf("%d\n",pn);
    if (argc<2)
    {
        fprintf(stderr, "Error, no port provided\n");
        exit(0);
    }
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock<0)
    {
        printf("Opening Socket");
    }
    length = sizeof(server);
    bzero(&server,length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(pn);
    if (bind(sock,(struct sockaddr *)&server,length)<0)
    {
        printf("Binding\n");
    }
    fromlen = sizeof(struct sockaddr_in);
    while(1)
    {
        printf("Recieving\n");
        n = recvfrom(sock,buf,1024,NULL,(struct sockaddr *)&from,&fromlen);
        if(n<0)
        {
            printf("Recvfrom");
        }
        //write(1,"Recieved a datagram: ",21);
        printf("The data from clien is %s \n",buf);
        //write(1,buf,n);
        n = sendto(sock,buf,1024,NULL,(struct sockaddr *)&from,fromlen);
        if(n<0)
        {
         printf("sendto");
        }
    }
return 0;
}