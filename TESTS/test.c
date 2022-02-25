#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int lol = 1;

void	sighandler(int sig)
{
	if (sig == SIGSTOP)
	{
		lol = 0;
		write(1, "STOPPED\n", 8);
	}
	else if (sig == SIGCONT)
	{
		dprintf(1, "CONTINUED ... BUT EXIT LOL\n");
		//exit(0);
	}
}

int		main(int ac, char **av, char **envp)
{
	int pid;
	int status = 0;
	struct sigaction sga;

	sigemptyset(&sga.sa_mask);
	sga.sa_flags = 0;
	sga.sa_handler = &sighandler;
	sigaction(SIGSTOP, &sga, 0);
	sigaction(SIGCONT, &sga, 0);

	dprintf(1, "%d", getpid());
	if (!(pid = fork()))
		execve(av[1], &av[1], envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			while (1)
				if (lol)
					write(1, "0\n", 2);
	}
	return 0;
}
