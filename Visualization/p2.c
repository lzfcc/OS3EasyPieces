//5.2 Adding wait() System Call
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    }
    else
    { // parent goes down this path (main)
        int stat;
        int wc = wait(&stat);
        if (WIFEXITED(stat))
            printf("Exit status: %d\n", WEXITSTATUS(stat));
        else if (WIFSIGNALED(stat))
            psignal(WTERMSIG(stat), "Exit signal");
        // int wc = wait(NULL);

        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid());
    }
    return 0;
}