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

char * delimit_hostnames(char * names, int len){
    printf("\ndemlimit hostnames: %s", names);
      char *temp = malloc(len);
        int i;
          for (i = 0; i < len; i++){
                  if  (names[i] == ' ') {
                       printf("SPACE");
                     temp[i] = '~';}
                 else { temp[i] = names[i];}
                    }
 printf("\nTEMP: %s", temp );
return temp;
 }

int main(int argc, char *argv[]) {

    int rv, sockfd, port, n, sending, recieving;
      struct addrinfo hints, *servinfo, *p; //new
        char buffer[256], msg_in[1000];
          bzero(msg_in, 1000);

          socklen_t len;

printf("0 %s 1 servername %s 2: port# %s 3: requestID %s 4: hostnames %s", argv[0], argv[1], argv[2], argv[3], argv[4]);


  if (argc != 5)
            printf("ERROR, usage: client servername port operation hostnames");

  message m;
  m.gid = 'E';
   m.requestID = atoi(argv[3]);
 m.hostnames = malloc(strlen(argv[4]));
  m.length=(strlen(argv[4]) + 5);

char *temp;
  temp = delimit_hostnames(argv[4], strlen(argv[4]));
    printf("\n\nAFTER %s", temp);
      strcpy(m.hostnames, temp);
        printf("\nM.Hostnames %s", m.hostnames);

          memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_INET;
              hints.ai_socktype = SOCK_DGRAM;

                if ((rv = getaddrinfo(argv[1], argv[2], &hints, &servinfo))!= 0 ) {
                    printf("Client getaddrinfo error"); exit(0);
                      }

                  for(p = servinfo; p != NULL; p = p->ai_next) {
                            if ((sockfd = socket(p->ai_family, p->ai_socktype,p->ai_protocol)) == -1) {
                                          perror("talker: socket");
                                                      continue;
                                                              }
                                    break;
                                      }


                   if (p == NULL) {printf("\nPROBLEM WITH P");}

                    port = atoi(argv[2]);

                     if ((sending = sendto(sockfd, (char *)&m, m.length, 0, p->ai_addr, p->ai_addrlen )) == -1){
                               printf("CLIENT error sendto"); exit(0);
                                 }
                             printf("\nSENDING = %d. &m = %s", sending, (char *)&m);

                             /*
                              *  //new stuff -- get sockaddr stuff working FIRST
                              *    recieving = recvfrom(sockfd, msg_in, 1000, 0, (struct sockaddr *)&servaddr, &len);
                              *      printf("HERE goes... %d", recieving);
                              *        int i = 0;
                              *              char hex[10];
                              *                    char hexmesg[1000];
                              *                          bzero(hexmesg, 1000);
                              *                                while(i < n) {
                              *                                        sprintf(&hex[0], "%02X", 0xFF & msg_in[i]);
                              *                                                strcat(hexmesg, hex);
                              *                                                        i++;
                              *                                                              }
                              *                                                                    printf("%s", hexmesg);
                              *                                                                    */

                               freeaddrinfo(servinfo);
                                 close(sockfd);


                                   printf("END\n\n");
                                     return 0;
}
