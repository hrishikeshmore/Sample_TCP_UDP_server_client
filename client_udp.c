#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include <time.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    int sock,length,n,timelev, timearr;
    char buff_time[256];
    char time_stamp[50];
    char buffs[500];
    struct timeval tv;
    time_t curtime;
    struct sockaddr_in server, from;
    struct hostent *hp;
    char buffer[256];
    if(argc !=3)
    {
        printf("Usage: Server port\n");
        exit(1);
    }
    sock=socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0)
    {
        printf("socket");
    }
    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if(hp==0)
    {
        printf("Unknown host");
    }
    bcopy((char *)hp->h_addr, (char*)&server.sin_addr,hp->h_length);
    server.sin_port = htons(atoi(argv[2]));
    length = sizeof(struct sockaddr_in);
    printf("Please Enter Messsage: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    gettimeofday(&tv, NULL); 
    //curtime=tv.tv_sec;
    timelev=tv.tv_usec;
    strftime(buff_time,30,"%m-%d-%Y  %T.",localtime(&tv));
    printf("%s%ld\n",buff_time,tv.tv_usec);
    bzero(buffs,500);
    strcat(buffs,buffer);
    strcat(buffs,buff_time);
    n=sendto(sock,buffs,strlen(buffs),NULL,&server,length);
    if(n<0)
    {
        printf("Sendto");
    }
    n=recvfrom(sock,buffer,256,NULL,&from,&length);
    if(n<0)
    {
        printf("Recvfrom");
    }
    write(1,"Got an ack : ",12);
    write(1,buffer,n);
    gettimeofday(&tv, NULL); 
    curtime=tv.tv_sec;
    timearr=tv.tv_usec;
    strftime(buff_time,30,"%m-%d-%Y  %T.",localtime(&curtime));
    printf("%s%ld\n",buff_time,tv.tv_usec);
    int rtt;
    rtt = timearr - timelev;
    printf("rtt = %d\n",rtt);
return 0;
}