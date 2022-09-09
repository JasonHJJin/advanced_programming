/*
 * mdb-lookup-server-nc-2.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

static void die(const char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char **argv)
{
    
//    if (argc != 2) {
//	fprintf(stderr, "usage: %s <port>\n", argv[0]);
//	exit(1);
//    }
    
    pid_t pid;

    while(1){//while begins
        
        pid = waitpid((pid_t)-1, NULL, WNOHANG);

        
        while(pid>0){
	        die("waitpid failed");
	        fprintf(stderr, "[pid=%d] ", (int)pid);
                fprintf(stderr, "mdb-lookup-server terminated\n");
        }
        //to stdout
        printf("port number: ");
        
        char buf[100];
        
        buf[0] = '\0';
        // if(buf[strlen(buf)-1] == '\n'){
        //    buf[strlen(buf)-1] = '\0';
        

        fgets(buf, sizeof(buf), stdin);
        
        
        //parse number out of the string
        int num;
        if(sscanf(buf, "%d", &num) !=1){
            continue;
        }

        sprintf(buf, "%d", num);
        
        pid = fork();
        if (pid < 0) {
	die("fork failed");
        } else if (pid == 0) {
	                // child process
	                fprintf(stderr, "[pid=%d] ", (int)getpid());
	                fprintf(stderr, "mdb-lookup-server started on port %s\n", buf);
	                execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh", buf, (char *)0);
	                die("execl failed");
                
        }
	// parent process
        // Jae from the lecture notes
	//put all in a loop
        //change waitpid so that is nonblocking
        //fgets and use sscanf to parse number out of the string

    }//Keep iterating
    return 0;
}
