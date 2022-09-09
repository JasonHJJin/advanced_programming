/*
 * mdb-lookup-server.c
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

#include "mylist.h"
#include "mdb.h"

#define KeyMax 5

static void die(const char *message)
{
    perror(message);
    exit(1); 
}

int main(int argc, char **argv)
{   
    // ignore SIGPIPE so that we don’t terminate when we call 
    // // send() on a disconnected socket.
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) die("signal() failed");
    
    /*
     * open the database file specified in the command line
     */

    if (argc != 3) {
        fprintf(stderr, "%s\n", "usage: mdb-lookup-server <database_file> <port number>");
        exit(1);
    }
    
    char *filename = argv[1];
    unsigned short portNum = atoi(argv[2]);
    
    // Create a listening socket (also called server socket)

    int servsock;
    if ((servsock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        die("socket failed");

    // Construct local address structure
    
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); //any network interface
    servaddr.sin_port = htons(portNum);

    // Bind to the local address
    
    if (bind(servsock, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
        die("bind failed");

    // Start listening for incoming connections

    if (listen(servsock, 5 /*queue size for connection requests */) < 0)
        die("listen failed");
    
    
    int clntsock;
    socklen_t clntlen;
    struct sockaddr_in clntaddr;
    

    while(1){
        // Beginning of mdb-lookup.c
        
        // Accept and incoming connection
        
        clntlen = sizeof(clntaddr);

        if ((clntsock = accept(servsock, (struct sockaddr *) &clntaddr, &clntlen)) < 0)
            die("accept failed");
        
        
        fprintf(stderr, "Connection Success from client ip: %s\n", inet_ntoa(clntaddr.sin_addr));


        FILE *fp = fopen(filename, "rb");
        if (fp == NULL) 
                die(filename);

        /*
        * read all records into memory
        */

        struct List list;
        initList(&list);

        int loaded = loadmdb(fp, &list);
        if (loaded < 0)
                die("loadmdb");
    

        /*
        * lookup loop
        */
        

        char line[1000];
        char key[KeyMax + 1];
        FILE *input = fdopen(clntsock, "r");
        if (input == NULL)
            die("fdopen failed");


        char buf[1000];
        int characters;

        while (fgets(line, sizeof(line), input) != NULL) {

                // must null-terminate the string manually after strncpy().
                strncpy(key, line, sizeof(key) - 1);
                key[sizeof(key) - 1] = '\0';

                // if newline is there, remove it.
                size_t last = strlen(key) - 1;
                if (key[last] == '\n')
                key[last] = '\0';

                // traverse the list, printing out the matching records
                struct Node *node = list.head;
                int recNo = 1;
                while (node) {
                struct MdbRec *rec = (struct MdbRec *)node->data;
                if (strstr(rec->name, key) || strstr(rec->msg, key)) {
                    //return the number of characters printed
                    characters = snprintf(buf, sizeof(buf), "%4d: {%s} said {%s}\n", recNo, rec->name, rec->msg);           
                    if (send(clntsock, buf, characters, 0) != characters)
                        die("send failed");
                }
                node = node->next;
                recNo++;
                }

                characters = snprintf(buf, sizeof(buf), "\n");
                if (send(clntsock, buf, characters, 0) != characters)
                    die("send failed");

        }

        // see if fgets() produced error
        if (ferror(input)) 
                die("input failed");

        /*
        * clean up and quit
        */

        freemdb(&list);
        fclose(fp);
        // End of mdb-lookup.c
        
        fclose(input);

        fprintf(stderr, "Disconnected from client ip: %s\n", inet_ntoa(clntaddr.sin_addr));
   
    }

   return 0;
}
