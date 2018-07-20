#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#ifdef DOMAIN_INET
#include<netinet/in.h>
#include<arpa/inet.h>
#endif

#ifdef DOMAIN_UNIX
#include<sys/un.h>

#define SOCK_PATH "server_socket"
#endif

int main() {
    int sockfd;
    int len;
    int result;
    char ch = 'A';

#ifdef DOMAIN_INET
    struct sockaddr_in address;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;
#endif 

#ifdef DOMAIN_UNIX
    struct sockaddr_un address;
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, SOCK_PATH);
#endif 

    len = sizeof(address);
    result = connect(sockfd, (struct sockaddr*)&address, len);
    if(result == -1){
	perror("oops: client1");
	exit(1);
    }
    write(sockfd, &ch, 1);
    printf("char send to server = %c\n", ch);
    read(sockfd, &ch, 1);
    printf("char from server = %c\n", ch);
    close(sockfd);
    exit(0);
}
