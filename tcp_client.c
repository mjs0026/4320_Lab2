#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

typedef struct Msg{
  short length;
  short reqID;
  char op;
  char *message;
} Msg;

int main(int argc, char *argv[]){

int counter = 0;
  int sockfd, port, n;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char buffer[256];
  printf("1%s 2%s 3%s 4%s 5%s", argv[1], argv[2], argv[3], argv[4], argv[5]);


  if (argc < 5)
        printf("ERROR, usage: client servername port operation message");

   printf("PAST argc");

  Msg m;
  m.reqID = counter++;
  m.op = atoi(argv[4]);
  m.length=(strlen(argv[5]) + 5);
  m.message = malloc(strlen(argv[5]) + 1);
  strcpy(m.message, argv[5]);

  printf("\nPAST MSG. M.message = %s. &M = %s\n", m.message,(char*)&m);


 port = atoi(argv[3]);
 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {printf("\nCLIENT: error with sockfd");}
printf("\nsockfd %d\n", sockfd);



 server = gethostbyname(argv[2]);
 printf("\nserver %s", argv[2]);

 if (server == NULL) {printf("CLIENT: error with hostname");exit(0);}

 serv_addr.sin_port = htons(port);
 bzero((char *) &serv_addr, sizeof(serv_addr));
 serv_addr.sin_family = AF_INET;
 bcopy((char *)server->h_addr,
                      (char *)&serv_addr.sin_addr.s_addr,
                               server->h_length);
 serv_addr.sin_port = htons(port);
 if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
              {printf("\n\nERROR connecting");}
 else {printf("\nConnect: %d", connect);}
  bzero(buffer,256);

  time_t t1, t2;
  t1 = time(0);


  printf("SENDING: %s",(char*) &m);
  ssize_t sending;
  sending = write(sockfd,(char *)&m, m.length);




printf("HERE");
  return 0;
}
