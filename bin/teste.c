#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#define LEN_PARAMS 10
#define LEN_COMMAND 64

int main(void)
{
    char command[LEN_COMMAND + 1] = "./helloshell", *parameters[LEN_PARAMS];
    int status = 0;
    
    /*
    while(1)
    {
        scanf("%s");

        if(fork() != 0)
        {
            waitpid(-1, &status, 0);
        }else
        {
            execve(command, parameters, 0);
        }
        
    }*/

    return 0;
}