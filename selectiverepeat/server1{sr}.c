#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#define W 5
#define p1 50
#define p2 10
#define port 6500
char a[90];
char b[90];

void alp(int z)
{
 int k,i=1,g;
         k=z;
	 b[0]='N';
         while(k>0)
                {
                 i++;
                 k=k/10;
                }
                g=i;
                i--;
         while(z>0)
                {
                 k=z%10;
                 b[i]=k+48;
                 i--;
                 z=z/10;
                }
                b[g]='\0';

}

void alpha(int z)
{
 int k,i=0,g;
         k=z;
         while(k>0)
                {
                 i++;
                 k=k/10;
                }
                g=i;
                i--;
         while(z>0)
                {
                 k=z%10;
                 a[i]=k+48;
                 i--;
                 z=z/10;
                }
                a[g]='\0';

}


int main()
{
int sockfd,confd,i=0,len,c=1,j,f;
struct sockaddr_in servaddr,cliaddr;
unsigned int sr;
char v[90];
printf("SELECTIVE REPEAT SERVER \n");
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(port);
if(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
	 printf("ERROR ON BINDING \n");
	 exit(0);
	}
listen(sockfd,1);
len=sizeof(cliaddr);
confd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
if(confd<0)
	{
	printf("ERROR ON CONNECTION \n");
	exit(0);
	}
printf("CONNECTION ESTABLISHED \n");
sr=(unsigned int ) time(NULL);
srand(sr);
strcpy(v,"TIMEOUT");
recv(confd,a,sizeof(a),0);
 f = atoi(a);
printf("FRAME NUMBER IS %d\n",f);
//fflush(stdout);
while(1)
	{
	 for(i=0;i<W;i++)
		{
		 recv(confd,a,sizeof(a),0);
		  if(strcmp(a,v)==0)
			{
			 printf("SESSION ENDED \n");
			 exit(0);
			}
		}
	i=0;
	 while(i<W)	
		{
		 L: j =rand()%p1;
		 if(j<p2)
			{
			  alp(c);
			  send(confd,b,sizeof(b),0);
			   goto L;	
			}
		  else
			{
			 alpha(c);
			 if(c<=f)
				{
				 printf("FRAME %s RECIEVED\n",a);
				 send(confd,a,sizeof(a),0);
				c++;
				}
			  else
				{
				 break;
				}
			}
			if(c>f)
			{
			 break;
			}
			i++;
		}
	/*if(c>f)
		{
		 break;
		}*/
	}
close(confd);
close(sockfd);
return 0;
}
