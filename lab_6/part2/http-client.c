#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>

static void die(const char *s) { perror(s); exit(1); }

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr, "usage: http-client <host name> <port number> <file path>\n");
        fprintf(stderr, "   ex) http-client www.example.com 80 /index.html\n");
        // sample command line looking
        // ./http-client www.gnu.org 80 /software/make/manual/make.html
        exit(1);
    }
    
    char *serverName = argv[1];
    char *portNum = argv[2];
    //unsigned short port = atoi(argv[2]);
    char *path = argv[3];
    
    //filter out fileName
    char *path2 = strrchr(path, '/');
    if(!path2){
        fprintf(stderr, "<file path> error\n");
        exit(1);
    }
    
    char *fileName;
    fileName = path2 + 1;
    
    //Create a socket for TCP connection

    int sock; //socket descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socekt failed");

    struct hostent *he;
    if ((he = gethostbyname(serverName)) == NULL){
        die("gethostbyname failed");
    }
    char *serverIP = inet_ntoa(*(struct in_addr *)he->h_addr);

    // Construct a server address structure
    //get server ip from server name
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr)); //must zero out the structure
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(serverIP);
    
    unsigned short port = atoi(portNum);
    servaddr.sin_port = htons(port); //must be in network byte order

    //Establish a TCP connection to the server

    if (connect(sock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        die("connect failed");

    char buf[4096];
    
    snprintf(buf, sizeof(buf), "GET %s HTTP/1.0\r\n"
                               "Host: %s:%s\r\n"
                               "\r\n", path, serverName, portNum);
    
    if (send(sock, buf, strlen(buf), 0) != strlen(buf)){
        die("send failed");
    }

    //wrap sock
    FILE *input;
    if ((input = fdopen(sock, "r")) == NULL){
        die("fdopen failed");
    }
    
    //check for "200" in the first line
    if(fgets(buf, sizeof(buf), input) == NULL){
        if(ferror(input)){
            die("input failed");        
        }
        fprintf(stderr, "fgets first line failed");
        exit(1);
    }

    if((strncmp("200", buf + 9, 3) != 0)){
        fprintf(stderr, "%s\n", buf);
        exit(1);
    }
    
    //check rest
    while(1){ 
        if(fgets(buf, sizeof(buf), input) == NULL){
            if(ferror(input)){
                die("fgets failed");
            }
            fprintf(stderr, "server terminates");
            exit(1);
        }
        if(strcmp("\r\n", buf) == 0){
            break;
        }
    }

    //read can be image so binary
    FILE *f = fopen(fileName, "wb");

    if(f == NULL){
        die("fopen failed");
    }
    
    size_t characters = 1;

    while(characters > 0){

        characters = fread(buf, 1, sizeof(buf), input);
        //if its not the number of characters read, die
        if(fwrite(buf, 1, characters, f) != characters){
            die("fwrite failed");
        }
    }
    if(ferror(input)){
        die("fread failed");
    }

    fclose(f);
    fclose(input);
    return 0;
}
