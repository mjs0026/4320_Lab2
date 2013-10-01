#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


typedef struct message{
        short length;
        char checksum;
        char gid;
        char requestID;
        char *hostnames;
} message;



int main(int argc, char *argv[]) {

  int counter = 0;
  int sockfd, port, n, rv, sending;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  struct addrinfo hints, *servinfo, *p; //new
  char buffer[256];
  printf("0 %s 1 servername %s 2: port# %s 3: requestID %s 4: hostnames %s", argv[0], argv[1], argv[2], argv[3], argv[4]);


  if (argc != 5)
        printf("ERROR, usage: client servername port operation hostnames");

  message m;
  m.gid = 'E';
  m.requestID = atoi(argv[3]);
  m.hostnames = malloc(strlen(argv[4]));
  strcpy(m.hostnames, argv[4]); //add strcat for ~s
  m.length=(strlen(argv[4]) + 5);
  printf("\nM.hostnames %s", m.hostnames);
memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;

  if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo))!= 0 ) {
  printf("Client getaddrinfo error"); exit(0);
  }


    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                p->ai_protocol)) == -1) {
            perror("talker: socket");
            continue;
        }

        break;
    }

 port = atoi(argv[2]);
 if (p == NULL) {printf("\nPROBLEM WITH P");}

  if ((sending = sendto(sockfd, (char *)&m, m.length, 0, p->ai_addr, p->ai_addrlen )) == -1){
        printf("CLIENT error sendto"); exit(0);
  }
        printf("\nSENDING = %d. &m = %s", sending, (char *)&m);

    freeaddrinfo(servinfo);
    close(sockfd);
  printf("END\n\n");
  return 0;
}