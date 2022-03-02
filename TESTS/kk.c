
int main(int ac, char **av, char **envp)
{
char *l[5]={"/bin/ls", 0};

execve("bin/ls", l, envp);
return(0);
}
