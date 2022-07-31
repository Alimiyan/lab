#include<string.h>
#include<sys/ioctl.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<net/if_arp.h>
int main()
{
int sd,b,cd;
char fname[50],op[1000];
struct sockaddr_in caddr,saddr;
FILE *fp;
socklen_t clen=sizeof(caddr);
sd=socket(AF_INET,SOCK_STREAM,0);
if(sd!=-1)
printf("socket is created\n");
else
printf("socket is not created\n");
saddr.sin_family=AF_INET;
saddr.sin_port=htons(2580);
saddr.sin_addr.s_addr=htonl(INADDR_ANY);
b=bind(sd,(struct sockaddr*)&saddr,sizeof(saddr));
if(b==0)
printf("binded successfully\n");
else
printf("binding failed\n");
listen(sd,5);
cd=accept(sd,(struct sockaddr*)&caddr,&clen);
recv(cd,fname,sizeof(fname),0);
fp=fopen(fname,"w");
recv(cd,op,sizeof(op),0);
fwrite(op,strlen(op),1,fp);
printf("%s",op);
printf("the file has been transferred\n");
close(sd);
close(cd);
fclose(fp);
return 0;
}
