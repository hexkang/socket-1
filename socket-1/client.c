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
    inet_pton(AF_INET,"192.168.93.128",&s.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr*)&s, sizeof(s));
    if(ret==-1)
    {
        perror("connect") ;
        return 1;
    }
    
    int num = 0;
    while(1)
    {
        char buffffff[1024];
        sprintf(buffffff, "hello my friend %d\n",num++);
        send(fd,buffffff,strlen(buffffff),0);
        memset(buffffff,0,sizeof(buffffff));
        int len = recv(fd, buffffff,sizeof(buffffff), 0);
        if(len>0)
        {
            printf("Server say: %s\n", buffffff);
        }
        else if (len == 0)
        {
            printf("server lose connect\n") ;break;
        }
        else 
        {
            perror("recv");break;
        }
        sleep(1);
    }

    close(fd);
    return 0;
 }
