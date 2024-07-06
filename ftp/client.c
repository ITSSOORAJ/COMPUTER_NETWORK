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
int  main()
{
int sockfd,n;
struct sockaddr_in servaddr, cliaddr;
char send[max],recv[max];
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(port);
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
printf("ENTER THE FILE NAME TO BE ACESSED FROM SERVER\n");
scanf("%s",send);
write(sockfd,send,max);
while(n=(read(sockfd,recv,max))!=0)
	{
		printf("_______%s_______\n%s",send,recv);

	}
close(sockfd);
return 0;
}
