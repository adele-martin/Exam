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
	pipe(pipe_fds);
	pid_t pid = fork();

	if (pid == 0)
	{
		 //You are inside the child process
	}
	else if (pid > 0)
	{
		//You are in the parent process
	}
	else
	{
		perror("forking process failed");
	return 1;
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