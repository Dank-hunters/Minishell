#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

void	sighandler(int sig)
{
	if (sig == SIGSTOP)
		dprintf("STOPPED\n");
	else
	{
		dprintf("CONTINUED ... BUT EXIT LOL\n");
		exit(0);
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
	dprintf(1, "%d", getpid());
	if (!(pid = fork()))
		execve(av[1], &av[1], envp);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			while (1)
				dprintf(1, "0\n");
	}
	sigaction(SIGSTOP, 0, &sga);
	sigaction(SIGCONT, 0, &sga);
	return 0;
}
