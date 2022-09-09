/*
 * http-server.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>

//socket -> bind -> listen -> accept -> recv -> send -> read -> close

static void die(const char *s) { perror(s); exit(1);}

static int serverSock(unsigned short serverPort){
    
    // Create a listening socket (also called server socket)
    
    int servsock;
    if ((servsock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        die("socket failed");
    }

    // Construct local address structure

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // any network interface
    servaddr.sin_port = htons(serverPort);

    // Bind to the local address
    if (bind(servsock, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        die("bind failed");
    }

    //listen
    if (listen(servsock, 5 /* queue size for connection requests */ ) < 0){
        die("listen failed"); 
    }

    return servsock;
}

static int mdbsock(unsigned short mdbPort, char *mdbAddr){

    int sock;
    struct sockaddr_in serverAddr;
    struct hostent *he;
    
    //get mdb-lookup-host
    if ((he = gethostbyname(mdbAddr)) == NULL){
        die("gethostbyname failed");
    }    

    char *serverIP = inet_ntoa(*(struct in_addr *)he->h_addr);
    
    //create socket
    if ((sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
        die("socket failed");
    }

    //construct server address
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_port = htons(mdbPort);

    //connect
    if (connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0){
        die("connect failed");
    }

    return sock;
}


ssize_t sendtoSock(int sock, const char *buf){
    
    ssize_t size;
    size = send(sock, buf, strlen(buf), 0);
    if(size != strlen(buf)){
        perror("send() failed");
        return -1;
    }else{
        return size;
    }
}


static struct{
        int status;
        char *message;
} httpstatusmessages[] = { {200, "OK"}, {204, "No Content"}, {301, "Moved Permanently"}, {302, "Moved Temporaily"}, {304, "Not Modified"}, {400, "Bad Request"}, {403, "Forbidden"}, {404, "Not Found"}, {501, "Not Implemented"}, {502, "Bad Gateway"}, {0, NULL} };

static char *message(int statuscode){

    int i = 0;
    while (httpstatusmessages[i].status > 0){
        if (httpstatusmessages[i].status == statuscode){
            return httpstatusmessages[i].message;
        }
        i++;
    }
    return "Unknown statuscode";

}

static void checkandsend(int clntsock, int statuscode){
    
    char buf[1000];
   
    char *getMessage = message(statuscode);

    sprintf(buf, "HTTP/1.0 %d ", statuscode);
    strcat(buf, getMessage);
    strcat(buf, "\r\n\r\n");

    if (statuscode != 200){
       
       char c[1000];
       sprintf(c, "<html><body>\n"
                  "<h1>%d %s</h1>\n"
                  "</body></html>\n", statuscode, getMessage);
      
       strcat(buf, c);
       
    }

    sendtoSock(clntsock, buf); 

}
/**
static void closeFile(FILE *file, char *address, char *method, char *requestURI, char *httpVersion, int statuscode, char *status){

    
    fprintf(stderr, "%s \"%s %s %s\" %d %s\n", address, method, requestURI, httpVersion, statuscode, status);
    fclose(file);

}
**/

int main(int argc, char **argv){
    
    // ignore SIGPIPE so that we don’t terminate when we call 
    // send() on a disconnected socket.

    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR){
        die("signal() failed");
    }

    // ./http-server <server_port> <web_root> <mdb-lookup-host> <mdb-lookup-port>
    
    if (argc != 5){
        fprintf(stderr, "usage: %s <server_port> <web_root> <mdb-lookup-host> <mdb-lookup-port>\n", argv[0]);
        exit(1);
    }
   
    //assign variables
    unsigned short serverPort = atoi(argv[1]);
    char *webRoot = argv[2];
    char *mdbLookupHost = argv[3];
    unsigned short mdbLookupPort = atoi(argv[4]); 
    
    //servSock
    int servSock;
    servSock = serverSock(serverPort);

    //mdbSock
    int mdbSock;
    mdbSock = mdbsock(mdbLookupPort, mdbLookupHost); 
    FILE *mdbWrap = fdopen(mdbSock, "r");
    if(mdbWrap == NULL){
        die("fdopen failed");
    }

    char requestLine[1000];
    char buf[1000];
    socklen_t clntlen;
    struct sockaddr_in clntaddr;

    struct stat st;

    int statuscode;
    //char *status;

    const char *mdb1 = "/mdb-lookup";
    const char *htmllookup = "/mdb-lookup?key=";
    
    while (1) {
        
        // Accept an incoming connection

        clntlen = sizeof(clntaddr); // initializie the in-out parameter
        
        int clntSock = accept(servSock, (struct sockaddr *) &clntaddr, &clntlen);
        if (clntSock < 0) {
            die("accept failed");
        }

        // accept() returned a connected socket (also called client socket)
        // and filled in the client's address into clntaddr
 
        // Wrap clntSock
        FILE *clntWrap = fdopen(clntSock, "r");
        if(clntWrap == NULL){
            die("fdopen failed");
        }
        
        if (fgets(requestLine, sizeof(requestLine), clntWrap) == NULL){
            statuscode = 400;
            goto gotoloop;
        }
        
        //parsing the request line

        char *token_separators = "\t \r\n"; // tab, space, new line 
        char *method = strtok(requestLine, token_separators); // GET 
        char *requestURI = strtok(NULL, token_separators); // cs3157/tng/images/ship.jpg
        char *httpVersion = strtok(NULL, token_separators); // HTTP/1.0
        char *restRequest = strtok(NULL, token_separators);

        if ((!method) || (!requestURI) || (!httpVersion) || restRequest){
            statuscode = 501;
            checkandsend(clntSock, statuscode);
            goto gotoloop;
        }
        //only support the GET method

        if ((strcmp(method, "GET") != 0)){ 
            statuscode = 501;
            checkandsend(clntSock, statuscode);
            goto gotoloop;
        }
        
        if(strcmp(httpVersion, "HTTP/1.0") != 0 && strcmp(httpVersion, "HTTP/1.1")){
            statuscode = 501;
            checkandsend(clntSock, statuscode);
            goto gotoloop;
        }
        // check request URI
        if ((*requestURI != '/')||(!requestURI)){
            statuscode = 400;
            checkandsend(clntSock, statuscode);
            goto gotoloop;
        }
        
        // rest of the header file
        while (1) {
            if (fgets(buf, sizeof(buf), clntWrap) == NULL){
                statuscode = 400;
                goto gotoloop;
            }
            if (strcmp("\n", buf) == 0 || strcmp("\r\n", buf) == 0){
                break;
            }
        }

        const char *form =
            "<html><body>\n"
            "<h1>mdb-lookup</h1>\n" 
                "<p>\n"
                "<form method=GET action=/mdb-lookup>\n"
                "lookup: <input type=text name=key>\n"
                "<input type=submit>\n"
                "</form>\n"
                "<p>\n"
                "</body></html>\n";

        if ((strcmp(requestURI, mdb1) == 0)){
            
            checkandsend(clntSock, statuscode);
            /**
            if (send(clntSock, "HTTP/1.0 200 OK\r\n\r\n", 19, 0) != 19){
                perror("send() failed");
                goto gotoloop;
            }

            **/
            if(sendtoSock(clntSock, form) < 0){
                goto gotoloop;
            }
            /**
            if (send(clntSock, "\r\n\r\n", 4, 0) != 4){
                perror("send() failed");
                goto gotoloop;
            }
            **/

         if (strncmp(requestURI, htmllookup, strlen(htmllookup)) == 0){
                
                size_t len = strlen(requestURI); 
                
                char *meminput = (char *)calloc(1, sizeof(char)*len);
                meminput = requestURI + strlen(htmllookup);
                fprintf(stderr, "looking up [%s]: ", meminput);

                if (send(mdbSock, "\n", 1, 0) != 1){
                    goto gotoloop;
                } 
                
                if (send(mdbSock, meminput, strlen(meminput), 0) != strlen(meminput)){
                    perror("send() failed");
                    goto gotoloop;
                }
                
                //free(meminput);

                /**
                if (send(clntSock, "HTTP/1.0 200 OK\r\n\r\n", 19, 0) != 19){
                    perror("send() failed");
                    goto gotoloop;
                }

                if (send(clntSock, form, strlen(form), 0) != strlen(form)){
                   perror("send() failed");
                   goto gotoloop;
                }

                **/
                
                // Send lookup result table additionally
                // Add first line html
                
                char *firstLine;

                firstLine = "<p><table border>";

                if (send(clntSock, firstLine, strlen(firstLine), 0) != strlen(firstLine)){
                    
                    goto gotoloop;    
                }
                
                int count = 1;
                while (1){
                     
                    if (fgets(buf, sizeof(buf), mdbWrap) == NULL) {
                     
                        if (ferror(mdbWrap)){
                        //not die
                     
                            perror("mdb-lookup-server connection failed");
                     
                        }
                     
                        fprintf(stderr, "\nmdb-lookup-server connection terminated");
                     
                        goto gotoloop; 
                    }

                    if (strcmp(buf, "\n") == 0){
                        break;
                    }
                    
                    char *eachRow; 
                    
                    if (count % 2){
                    
                    
                        eachRow = "\n<tr><td>";
                        count++;
                    
                    }else{
                    
                        eachRow = "\n<tr><td bgcolor =yellow>";
                        count++; 
                    }

                    if (send(clntSock, eachRow, strlen(eachRow), 0) != strlen(eachRow)){
                        goto gotoloop;    
                    } 

                    if (send(clntSock, buf, strlen(buf), 0) != strlen(buf)){
                        goto gotoloop; 
                    }
               
                    char *lastLine = "\n</table>";
                   
                    if (send(clntSock, lastLine, strlen(lastLine), 0) != strlen(lastLine)){
                    
                        goto gotoloop; 
                    }
            
                } // END htmllookup

                char *endForm = "\n</body></html>\n";
            
                if (send(clntSock, endForm, strlen(endForm), 0) != strlen(endForm)){ 
                
                    goto gotoloop; 
                } 
        
            } 
        }else{
            
        // part(a)
        FILE *fp;

            // malloc and open

            char *file = (char *)malloc(strlen(webRoot) + strlen(requestURI) + 100);
            
            if (file == NULL){
                die("malloc failed");
            }

            // insert

            strcpy(file, webRoot);
            strcat(file, requestURI);

            if (file[strlen(file)-1] == '/'){
                
                strcat(file, "index.html");

            }

            char line[4096];
            
            if ((stat(file, &st) == 0) && (S_ISDIR(st.st_mode))){
                
                statuscode = 403;
                checkandsend(clntSock, statuscode);
                
                goto closeFree;
            }
                    

            fp = fopen(file, "rb");
            
            if (fp == NULL){
                
                // unable to open the requested file

                statuscode = 404;
                checkandsend(clntSock, statuscode);
                
                free(file);
                fclose(fp);                
            }
            
            statuscode = 200;
            checkandsend(clntSock, statuscode);
            
            // fread
            size_t bytes;
            while ((bytes = fread(line, 1, sizeof(line), fp)) > 0 ){
                
                if (send(clntSock, line, bytes, 0) != bytes){
                    
                    perror("send failed");
                    break;

                }

            }

            if (ferror(fp)){
                perror("fread failed");
            }
                 
      closeFree:
                free(file);
                if(fp)
                    fclose(fp);
                goto gotoloop;
      }

      gotoloop:
                fprintf(stderr, "%s \"%s %s %s\" %d %s\n", inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, statuscode, message(statuscode));
                fclose(clntWrap);

                //closeFile(clntWrap, inet_ntoa(clntaddr.sin_addr), method, requestURI, httpVersion, statuscode, status);
    
    } //END while
    return 0;
}
