
#include "../includes/pipex.h"
#include <stdio.h>

int	parsing(char **argv, char **env, t_cmd *cmd)
{
	int i;
	char	str_path;
	char	**path;

	i = 0;
	path = ft_split(ft_substr(env[31], 5, 158), ':');
	(*cmd).cmd1 = ft_split_pipex(argv[2], ' ');
	(*cmd).cmd2 = ft_split_pipex(argv[3], ' ');
	if (!find_path((*cmd).cmd1[0], path, cmd))
		perror("mauvais nom de cmd 1");
	if (!find_path((*cmd).cmd2[0], path, cmd))
		return (perror("mauvais nom de cmd 2"), 0);
	if (access(argv[1], R_OK) == -1)
		perror("Imposible de lire fichier 1");
	if (access(argv[4], R_OK | W_OK) == -1)
		return (perror("Imposible de lire fichier 2"), 0);
	return (1);
}

int main(int argc, char **argv, char **env) //remplacer experience par main si besoin de test des trucs
{
	//pid_t	pid;
	//int		pipefd[2];
	//char	buff;
	//int		fd;
	//char *tab_arg[3];
	char **str;
	int i;
	t_cmd cmd;

	if (!parsing(argv, env, &cmd))
		return (1);
	printf("file name 1 : %s\n", argv[1]);
	printf("cmd 1 : %s\n", cmd.cmd1[0]);
	printf("cmd 2 : %s\n", cmd.cmd2[0]);
	printf("file name 2 : %s\n", argv[4]);
/* 	i = 0;
	str = ft_split(ft_substr(env[31], 5, 158), ':');
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	} */
	//test d'appel du commande systeme
	/* tab_arg[0] = "ls";
	tab_arg[1] = "-l";
	tab_arg[2] = NULL;
	execve("/usr/bin/ls", tab_arg, __environ);
	//test pour creer et ecrire directement dans un fichier
	fd = open("./test.txt", O_WRONLY);
	printf("fd : %d\n", fd);
	ft_putstr_fd("test de ma petite experience pas piquee des hannetons", fd);
	// test des pipes et des forks
	pipe(pipefd);
	pid = fork();
	if (pid == -1)
		return (1);
	else if (pid == 0)
	{
		close(pipefd[1]);
		printf("je suis le fils, mon pid est %d\n", pid);
		printf("ce que j'ai lu dans la pipe :\n");
		while (read(pipefd[0], &buff, 1))
		{
			write(1, &buff, 1);
		}
		write(1, "\n", 1);
		close(pipefd[0]);
	}
	if (pid > 0)
	{
		close(pipefd[0]);
		printf("je suis le daron le pid de mon gosse est %d\n", pid);
		printf("je suis en train d'ecrir un truc dans le pipe...\n");
		write(1, "\n", 1);
		write_str(pipefd[1], "test de mon super pipe!!!!!!\n");
		close(pipefd[1]);
	} */

	return (0);
}