#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int ac, char **av, char **envp)
{
	int pid;
	int status = 0;

	kill(atoi(av[1]), SIGSTOP);
	if (!(pid = fork()))
		execve(av[2], &av[2], envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			kill(atoi(av[1]), SIGCONT);
	}
	return 0;
}
