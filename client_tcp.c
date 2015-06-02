#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#include <stdlib.h>
void error(char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n, timelev, timearr;
    char buff_time[256];
    char time_stamp[50];
    char buffs[500];
    struct timeval tv;
    time_t curtime;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[525];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    //server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
    gettimeofday(&tv, NULL); 
    //curtime=tv.tv_sec;
    timelev=tv.tv_usec;
    strftime(buff_time,30,"%m-%d-%Y  %T.",localtime(&tv));
    printf("%s%ld\n",buff_time,tv.tv_usec);
    //buffer = buffer + time_stamp + tv.tv_usec;
    //itoa(timelev,buffs,10);
    //strcat(buff_time,buffs);
    bzero(buffs,500);
    strcat(buffs,buffer);
    strcat(buffs,buff_time);
    n = write(sockfd,buffs,strlen(buff_time));
    if (n < 0) 
         error("ERROR writing to socket");
    
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
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