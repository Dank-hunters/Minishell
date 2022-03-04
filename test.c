# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

int main(int ac, char **av, char **envp)
{
    int i = 0;
    (void)ac;
    (void)av;
    int fd[2] = {0}, pid = 0;
    char *tmp[2] = {0};
    char *cmd[6] = {"/bin/ls", NULL, "/bin/cat", NULL};
    pipe(fd);
    while (cmd[i])
    {
	pid = fork();
	if (pid == 0)
	{
	    if (!i)
	    {
		dup2(STDOUT_FILENO, fd[0]);
	    }
	    else
	    {
		dup2(STDIN_FILENO, fd[1]);
	    }
	    close(fd[0]);
	    close(fd[1]);
	    execve(cmd[i], cmd + i, envp);
	    exit(0);
	    dprintf(1, "lol");
	}
	i += 2;
    }
    close (fd[0]);
    close(fd[1]);
    return 0;
}
