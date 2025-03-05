#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>


/*
The picoshell function is executed by the original (parent) process. It sets up the pipes,
forks off the child processes to execute the commands, manages the file descriptors,
and then waits for the children to finish. The parent itself doesn’t run the commands
directly; it orchestrates their execution by creating child processes.*/
int    picoshell(char **cmds[])
{
	//we start in parent process
	//I am creating two file descriptors here.
	int pipe_fds[2];
	pid_t pid;
	int i = 0;
	int prev_fd = 0; //To keep track of the previous pipe's read end

	while (cmds[i])
	{
		if (cmds[i + 1]) // if there is another cmd after, pipe
			pipe(pipe_fds);
		pid = fork(); //a new process is called (copy of parent). they now run independently
		if (pid == 0)
		{
			//you are in the child process
			if ((prev_fd)) //this is not the first cmd
			{
				//this is redirection input
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				//this is redirection output
				close(pipe_fds[0]); //Close read end, so it doesn't wait forever
				dup2(pipe_fds[1], STDOUT_FILENO); //Duplicate the write end
				close(pipe_fds[1]); //Close write end, the parent does not write to pipe
			}
			if (execvp(cmds[i][0], cmds[i]) != 1)
				exit (1);
		}
		else
		{
			//we are back in parent process now
			if (prev_fd) //if this is not the first cmd we close prev_fds
			//because we will re-assign it below
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(pipe_fds[1]);
				prev_fd = pipe_fds[0];
			}
		}
		i++;
	}
	while(wait(NULL) > 0)
		;
	//The parent and child processes run in parallel, this makes sure both are executed
	return 0;
}


int     main(int argc, char **argv)
{
    int     cmds_size = 1;
    for (int i = 1; i < argc; i++)
    {
            if (!strcmp(argv[i], "|"))
                    cmds_size++;
    }
    char ***cmds = calloc(cmds_size + 1, sizeof(char **));
    if (!cmds)
    {
           dprintf(2, "Malloc error: %m\n");
            return 1;
    }
    cmds[0] = argv + 1;
    int cmds_i = 1;
    for (int i = 1; i < argc; i++)
    {
            if (!strcmp(argv[i], "|"))
            {
                    cmds[cmds_i] = argv + i + 1;
                    argv[i] = NULL;
                    cmds_i++;
            }
    }
    int ret = picoshell(cmds);
    if (ret)
        perror("picoshell");
    free(cmds);
        return ret;
}

//To track the file descriptors you may use:
//valgrind --track-fds=yes ./your_program