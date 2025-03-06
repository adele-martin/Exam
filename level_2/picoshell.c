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
			if ((prev_fd)) //You need the input from last command
			{
				//this is redirection input
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				//this is redirection output
				close(pipe_fds[0]); //When the next command tries to read from the pipe, it will never see EOF because the read end is still open.
				dup2(pipe_fds[1], 1); //Duplicate the write end
				close(pipe_fds[1]); //Close write end, because we duplicated it
			}
			//execvp inherits the file descriptors that were set up before it was called.
			//This is why using dup2 always affects the execve function
			if (execvp(cmds[i][0], cmds[i]) != 1)
				exit (1);
		}
			waitpid(pid, NULL, 0);
			if (prev_fd) //if this is not the first cmd we close prev_fds
			//because we will re-assign it below
				close(prev_fd);
			if (cmds[i + 1])
			{
				close(pipe_fds[1]); //signal to child no more data will be written to this specific pipe
				//Important to close it for next command to detect the praen't has received the last cmd's input
				prev_fd = pipe_fds[0];
			}
			//no need to close pipe for the last cmd because there is no next child process
		i++;
	}
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


/*
Main process executes
-first command
-second command
-fork a pipe

We need to take the stdout of the first command as stdin to pipe.
We are simulating the shell's file descriptors stdin and stdout.

Since the first command is happening in the main process
we ought to tweak it to it doesnt output in the stdout.
So we have to dup2()!

*/