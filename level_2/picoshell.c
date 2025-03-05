#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int    picoshell(char **cmds[])
{
	//I am creating two file descriptors here.
	//pipefd[0] refers to the read end of the pipe. pipefd[1] refers to the write end of the pipe.
	int pipe_fds[2];
	pid_t pid;
	int i = 0;
	int prev_fd = 0; //To keep track of the previous pipe's read end

	while (cmds[i])
	{
		if (cmds[i + 1]) // if there is another cmd after, pipe
			pipe(pipe_fds);
		pid = fork();
		if (pid == 0)
		{
			//you are in the child process
			if ((prev_fd)) //this is not the first cmd
			{
				dup2(prev_fd, STDIN_FILENO);
				close(prev_fd);
			}
			if (cmds[i + 1])
			{
				close(pipe_fds[0]); // Close read end, as the child will write
				dup2(pipe_fds[1], STDOUT_FILENO); //Duplicate the write end
				close(pipe_fds[1]);
			}
			if (execvp(cmds[i][0], cmds[i]) != 1)
				exit (1);
		}
		else
		{
			if (prev_fd) //this is not the first cmd
			{
				close(prev_fd);
			}
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