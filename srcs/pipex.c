/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:27:00 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/10 18:39:19 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parsing(char **argv, char **env, t_cmd *cmd)
{
	char	**path;
	char *env_path;

	env_path = find_path_env(env);
	path = ft_split(ft_substr(env_path, 5, 158), ':');
	(*cmd).cmd1 = ft_split_pipex(argv[2], ' ');
	(*cmd).cmd2 = ft_split_pipex(argv[3], ' ');
	if (!find_path((*cmd).cmd1[0], path, cmd, 1))
		perror(RED"mauvais nom de cmd 1"END);
	if (!find_path((*cmd).cmd2[0], path, cmd, 2))
		return (perror(RED"mauvais nom de cmd 2"END), 0);
	if (access(argv[1], R_OK) == -1)
		perror(RED"Imposible de lire fichier 1"END);
	return (1);
}

void	child1_process(t_cmd cmd, t_fd fd, char **env, char *file_path)
{
	fd.fd1 = open(file_path, O_RDONLY);
	if (fd.fd1 < 0)
	{
		perror(RED"impossible d'ouvir file 1"END);
		exit(EXIT_FAILURE);
	}
	close(fd.pipefd[0]);
	dup2(fd.fd1, STDIN_FILENO);
	dup2(fd.pipefd[1], STDOUT_FILENO); // essaye d'inverser les arguements?
	if (execve(cmd.path1, cmd.cmd1, env) == -1)
	{
		perror(RED"Erreur pendant l'execution de la commande 1\n"END);
		exit(EXIT_FAILURE);
	}
}

void	child2_process(t_cmd cmd, t_fd fd, char **env, char *file_path)
{
	fd.fd2 = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0744);
	if (fd.fd2 < 0)
	{
		perror(RED"impossible d'ouvir file 2"END);
		exit(EXIT_FAILURE);
	}
	close(fd.pipefd[1]);
	dup2(fd.fd2, STDOUT_FILENO);
	dup2(fd.pipefd[0], STDIN_FILENO);
	if (execve(cmd.path2, cmd.cmd2, env) == -1)
	{
		perror(RED"Erreur pendant l'execution de la commande 2\n"END);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv, char **env)
{
	t_fd	fd;
	t_cmd	cmd;
	pid_t	pid1;
	pid_t	pid2;

	if (argc == 5)
	{
		pipe(fd.pipefd);
		if (!parsing(argv, env, &cmd))
			return (1);
		pid1 = fork(); // creer l'enfant qui servira pour cmd1
		if (pid1 < 0)
			return (1);
		else if (pid1 == 0)
		{
			child1_process(cmd, fd, env, argv[1]); //execution de la premiere commande dans child 1
		}
		pid2 = fork(); // creer l'enfant qui servira pour cmd2
		if (pid2 < 0)
			return (1);
		else if (pid2 == 0)
		{
			child2_process(cmd, fd, env, argv[4]);
		}
		wait(NULL);
		close(fd.pipefd[0]);
		close(fd.pipefd[1]);
	}
	else
	{
		ft_putendl_fd(RED"Erreur, arguments invalides"END, 2);
		return (1);
	}
}
