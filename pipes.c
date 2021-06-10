#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {

    // 1) In the main() function, create a pipe using the pipe() function.

    int p[2]; // Array of two ints for the pipe.

    int r = pipe(p);  // Takes an array of two ints as an argument. It connects two file descriptors and returns  
              // them in the array (source: https://beej.us/guide/bgipc/html/multi/pipes.html)
    if (r < 0) {
        fprintf(stderr, "pipe failed\n\n");
        exit(3);
    }

    // 2) Then creates two child processes with fork().

    int pid = fork();
   
   if (pid > 0) { // Parent process
        pid = fork();
        
        if(pid > 0) { 

            close(p[0]);
            close(p[1]);
            
            waitpid(-1, NULL, 0); // 1 wait process for each child
            waitpid(-1, NULL, 0);

        }
        else if (pid == 0) { // Child process 2

        // 4) Child 2 redirects its input from stdin (0) to the read end of the pipe, then it executes the "sort -r -n -k 5" command.

            dup2(p[0], 0);
            close(p[1]);
            execlp("/usr/bin/sort", "sort", "-r", "-n", "-k", "5", NULL); // Takes the input from ps -aux and sorts it.
        }
    }
    else if (pid == 0) { // Child process 1

        // 3) Child 1 redirects stdout (1) to the write end of the pipe and then executes with execlp() the "ps -aux" command. 
     
            dup2(p[1], 1); // forces file descriptor 1 to be the writing end of the pipe
            close(p[0]);
            execlp("/usr/bin/ps" ,"ps", "-aux", NULL);   // executes "ps -aux" command

        }

    
    // 5) After creating both children, the parent process waits for them to terminate before it can exit. Note that you may 
    //    have to create Child 2 first, followed by Child 1. The parent program does the same thing as a shell that runs the 
    //    command "ps -aux | sort -r -n -k 5". 
 
    return 0;
}