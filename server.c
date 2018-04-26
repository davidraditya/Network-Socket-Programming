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
#include <time.h>
#define PORT 4444
#define BACKLOG 10
#define MAXDATASIZE 40

int main(void)
{
int sockfd, new_fd, numbytes;
struct sockaddr_in my_addr;
char buf[MAXDATASIZE],nilai[MAXDATASIZE],nilai2[MAXDATASIZE];
struct sockaddr_in their_addr;
int sin_size;
struct sigaction sa;
int yes=1;
if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
	perror("socket");
	exit(1);
}
if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1)
{
	perror("setsockopt");
	exit(1);
}
my_addr.sin_family = AF_INET;
my_addr.sin_port = htons(PORT);
my_addr.sin_addr.s_addr = INADDR_ANY;
memset(&(my_addr.sin_zero),'\0',8);
if(bind(sockfd, (struct sockaddr *)&my_addr,sizeof(struct sockaddr))==-1){
	perror("bind");
	exit(1);
}
if(listen(sockfd, BACKLOG) == -1){
	perror("listen");
	exit(1);
}
sin_size = sizeof(struct sockaddr_in);
if((sockfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size))==-1){
	perror("accept");
}
printf("@##########################################@\n");
printf("||                                        ||\n");
printf("||             Interface Server           ||\n");
printf("||                                        ||\n");
printf("||========================================||\n");
printf("||                                        ||\n");
printf("Server mendapat koneksi dari %s\n",inet_ntoa(their_addr.sin_addr));

time_t curtime;
time(&curtime);

while(1){
	numbytes=0;
	if((numbytes=recv(sockfd,buf,MAXDATASIZE-1,0))==-1){
		perror("recv");
	}
		buf[numbytes]=='\0';
		printf("Client : %s \n",buf);

	strcpy(nilai,buf);
	if(strcmp (buf,"IP") == 0){
	strcpy(nilai,inet_ntoa(my_addr.sin_addr));
	strcpy(nilai2,inet_ntoa(their_addr.sin_addr));
		printf("Server : %s \tClient : %s \n",nilai,nilai2);

	}
	else if(strcmp (buf,"date") == 0){
	strcpy(nilai,ctime(&curtime));
		printf("Server : %s \n",nilai);
	}
	else if(strcmp (buf,"bye") == 0){
		close(sockfd);
		return 0;
	}
	else{
		printf("Server : %s \n",nilai);
	}	
	if(send(sockfd,nilai,50,0) == -1){
		perror("send");
	}
   
    }


}
