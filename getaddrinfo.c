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

int
main(int argc, char **argv){

  char *ptr;
  struct addrinfo hints, *res, *bob;
  int n;
  char addrstring[100];
  
  bzero(&hints, sizeof(hints));
  hints.ai_flags = AI_CANONNAME;
  hints.ai_family = AF_INET;
  
  while (--argc > 0) {
    ptr = *++argv;
    
    if ( (n  = getaddrinfo(ptr, "domain", &hints, &res) ) != 0) {
      fprintf(stderr,"getaddrinfo error for host: %s: %s",ptr, gai_strerror(n));
      continue;
    }
    
    bob = res;
    do {
      inet_ntop(bob->ai_family, &((struct sockaddr_in *)bob->ai_addr)->sin_addr,addrstring,100);
      printf(" hostname: %s %s %d %p\n", bob->ai_canonname,addrstring,bob->ai_protocol, bob->ai_next);
      bob = bob->ai_next;
    } while (bob != NULL );
  }
  
  exit(0);
}
