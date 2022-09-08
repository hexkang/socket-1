#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
 
 int main()
 {
     int fd = socket(AF_INET, SOCK_STREAM, 0);
     if(fd == -1)
     {
         perror(" socket");
         return 1;
     }

    struct sockaddr_in s;
    s.sin_family = AF_INET ;
    s.sin_port = htons(7999);
    s.sin_addr.s_addr = INADDR_ANY  ;                       

    int ret = bind(fd, (struct sockaddr*)&s, sizeof(s));
    if(ret==-1)
    {
        perror("bind") ;
        return 1;
    }
    ret = listen(fd,128);
    if(ret == -1)
    {
        return 1;
    }
    struct sockaddr_in c;
    int clen= sizeof(c);
    int cfd = accept(fd,(struct sockaddr*)&c,  &clen);
    if(cfd ==  -1)
    {
        perror("accept");
        return 1;
    }
    char ip[32];
    inet_ntop(AF_INET,&c.sin_addr.s_addr,ip,sizeof(ip));
    ntohs(c.sin_port);
    while(1)
    {
        char buffffff[1024];
        int len = recv(cfd, buffffff,sizeof(buffffff), 0);
        if(len>0)
        {
            printf("client say: %s\n", buffffff);
            send(cfd,buffffff,len, 0);
        }
        else if (len == 0)
        {
            printf("client lose connect\n") ;break;
        }
        else 
        {
            perror("recv");break;
        }
    }

    
    close(fd);
    close(cfd);
    return 0;
 }
