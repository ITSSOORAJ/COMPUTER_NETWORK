#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#define port 6500
#define W 5
char a[90];
char b[90];


int mini(int x , int y)
	{
	if(x>y)
		{
		 return y;
		}
	 else
		{
		 return x;
		}
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

int con()
{
int i=1;
char k[9];
while(a[i]!='\0')
	{
	  k[i-1]=a[i];
	  i++;
	}
k[i-1]='\0';
 int r= atoi(k);
return r;
}


int  main()
{
int sockfd,i,w1,c=1,p,f,e,o,s;
struct sockaddr_in servaddr;
sockfd=socket(AF_INET,SOCK_STREAM,0);
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(port);
if(connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
	{
		printf("ERROR ON  CONNECTION \n");
		exit(0);
	}
printf("CONNECTION ESTABLISHED\n");
printf("ENTER THE FRAME NUMBER\n");
scanf("%d",&f);
alpha(f);
send(sockfd,a,sizeof(a),0);
strcpy(b,"TIMEOUT");
 o=f;
 s=W;
w1=W;
while(1)
	{
	  for(i=0;i<W;i++)
		{
		 alpha(c);
		 send(sockfd,a,sizeof(a),0);
		  if(c<=f)
			{
			  //send(sockfd,a,sizeof(a),0);
			  printf("FRAME %d SENDED\n ",c);
			  c++;
			}

		}
	  i = 0;
	  //w1 =W;
		while(i<s)
			{
			   recv(sockfd,a,sizeof(a),0);
			   p=atoi(a);
			   if(a[0]== 'N')
				{
				  e=con();
				   if(e<=f)
					{
						printf("NEGATIVE ACK ON FRAME %d\n",e);
						printf("FRAME %d RESEND\n",e);
						i--;
					}
				}
			  else
				{
					if(p<=f)
					  {
					    printf("ACK RECIEVED FOR FRAME %s\n",a);
					    w1--;
					  }
					else
						{
						 break;
						}

				}
					
				if(p>f)
						{
						 break;
						}
				i++;
			}
		 if(c>f && w1==0)
			{
			 send(sockfd,b,sizeof(b),0);
			 break;
			}
		else
			{
			 c=c-0;
			 //w1=W;
			 o=o-W;
			 s= mini(W,o);
			 w1=o;
			}
	}
 close(sockfd);
return 0;

}
