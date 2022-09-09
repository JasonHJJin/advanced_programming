
/*
 * mdb-lookup-server-nc-1.c
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
    
    if (argc != 2) {
	fprintf(stderr, "usage: %s <port>\n", argv[0]);
	exit(1);
    }

    char buf[100];

    while(fgets(buf, sizeof(buf), stdin)!=NULL){
    

    //new line to null at the end of each line
   // if(buf[strlen(buf)-1] == '\n'){
   //     buf[strlen(buf)-1] = '\0';
   // }
    
    sscanf(buf,"%s", buf); 
        
    pid_t pid = fork();
    if (pid < 0) {
	die("fork failed");
    } else if (pid == 0) {
	// child process
	fprintf(stderr, "[pid=%d] ", (int)getpid());
	fprintf(stderr, "mdb-lookup-server started on port %s\n", argv[1]);
	execl("./mdb-lookup-server-nc.sh", "mdb-lookup-server-nc.sh", 
		argv[1], (char *)0);
	die("execl failed");
    } else {
	// parent process
        // Jae from the lecture notes
	//put all in a loop
        //change waitpid so that is nonblocking
        //fgets and use sscanf to parse number out of the string
        
        if(waitpid(pid,
           NULL, // no status
              0) // no options	 
            != pid){
	        die("waitpid failed");
	        fprintf(stderr, "[pid=%d] ", (int)pid);
	        fprintf(stderr, "mdb-lookup-server terminated\n");
        }      
        
    } 

    }
    return 0;
}

