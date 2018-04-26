#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#define PORT 4444
#define MAXDATASIZE 100

int main()
{
int sockfd, numbytes;
char buf[MAXDATASIZE];
char nilai[MAXDATASIZE];
struct hostent *he;
struct sockaddr_in their_addr;
char no[50];
printf("To (ketik 'localhost') : ");
scanf("%s",no);

printf("@##########################################@\n");
printf("||                                        ||\n");
printf("||             Interface Client           ||\n");
printf("||                                        ||\n");
printf("||========================================||\n");
printf("||                                        ||\n");
printf("|| Ketik IP   untuk mengetahui IP Server  ||\n");
printf("|| Ketik date untuk tanggal Server        ||\n");
printf("|| Ketik bye  untuk terminasi koneksi     ||\n");
printf("||                                        ||\n");
printf("|| *Mungkin terjadi delay, silahkan input ||\n");
printf("||     kembali perintah anda              ||\n");
printf("||                                        ||\n");

if((he=gethostbyname(no))==NULL){
	perror("gethostbyname");
	exit(1);
}

if((sockfd = socket(AF_INET,SOCK_STREAM,0))==-1){
	perror("socket");
	exit(1);
}
their_addr.sin_family = AF_INET;
their_addr.sin_port = htons(PORT);
their_addr.sin_addr = *((struct in_addr *)he->h_addr);
memset(&(their_addr.sin_zero),'\0',8);
if(connect(sockfd, (struct sockaddr *)&their_addr,
	sizeof(struct sockaddr))==-1){
	perror("connect");
	exit(1);
}

while(1){
	printf("Client : ");
	scanf("%s",nilai);
	if(send(sockfd,nilai,50,0)==-1){
		perror("send");
		exit(0);
	}
	numbytes=0;
	if((numbytes=recv(sockfd,buf,MAXDATASIZE-1,0))==-1){
		perror("recv");
		exit(0);
	}
	if(numbytes > 1){		
		buf[numbytes]='\0';
		printf("Server : %s \n",buf);
	}
}
close(sockfd);
return 0;
}
