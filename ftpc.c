#include<string.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<net/if_arp.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
int main()
{
int sd,c,s;
char fname[50],sip[25],op[1000];
struct sockaddr_in caddr;
struct hostent *he;
FILE *fp;
printf("enter the server ip address: ");
scanf("%s",sip);
he=gethostbyname(sip);
sd=socket(AF_INET,SOCK_STREAM,0);
if(sd!=1)
printf("socket created\n");
else
printf("socket is not created\n");
caddr.sin_family=AF_INET;
caddr.sin_port=htons(2580);
caddr.sin_addr=*((struct in_addr*)he->h_addr);
c=connect(sd,(struct sockaddr*)&caddr,sizeof(caddr));
if(c==0)
printf("connected to server\n");
else
printf("connection failed");
printf("enter the file name: ");
scanf("%s",fname);
send(sd,fname,sizeof(fname),0);
fp=fopen(fname,"r");
fread(op,1000,1,fp);
send(sd,op,sizeof(op),0);
fclose(fp);
close(sd);
return 0;
}
