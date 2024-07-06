#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#define port 5035
#define max 60
FILE *f1;
int  main()
{
int sockfd,confd,n;
struct sockaddr_in servaddr, cliaddr;
char send[max],recv[max];
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(port);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
listen(sockfd,5);
int len=sizeof(cliaddr);
confd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
read(confd,recv,max);
printf("FILENAME IS %s\n",recv);
f1=fopen(recv,"r");
while(fgets(send,max,f1)!=NULL)
{
write(confd,send,max);
printf("\n");
}
fclose(f1);
printf("FILE SUCCESFULLY TRANSFERRED\n");
close(confd);
close(sockfd);
return 0;
}
