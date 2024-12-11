/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:27:00 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/11 13:57:37 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parsing(char **argv, char **env, t_cmd *cmd, t_fd *fd)
{
	char	**path;
	char *env_path;
	size_t

	fd->pipefd[0] = -1;
	fd->pipefd[1] = -1;
	fd->fd1 = -1;
	fd->fd2 = -1;
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

void	child_process(t_cmd cmd, t_fd fd, char **env, char *file_path)
{
	fd.fd1 = open(file_path, O_RDONLY);
	if (fd.fd1 < 0)
	{
		perror(RED"impossible d'ouvir file 1"END);
		exit(EXIT_FAILURE);
	}
	close(fd.pipefd[0]);
	dup2(fd.fd1, STDIN_FILENO);
	dup2(fd.pipefd[1], STDOUT_FILENO);
	if (execve(cmd.path1, cmd.cmd1, env) == -1)
	{
		perror(RED"Erreur pendant l'execution de la commande 1\n"END);
		exit(EXIT_FAILURE);
	}
}

void	parent_process(t_cmd cmd, t_fd fd, char **env, char *file_path)
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

	if (argc == 5)
	{
		if (!parsing(argv, env, &cmd, &fd))
			return (1);
		if (pipe(fd.pipefd) == -1)
			manage_error(&cmd, NULL, fd, RED"Errror with pipe function!"END);
		pid1 = fork();
		if (pid1 < 0)
			return (1);
		else if (pid1 == 0)
		{
			child_process(cmd, fd, env, argv[1]);
		}
		wait (NULL);
		parent_process(cmd, fd, env, argv[4]);
	}
	else
	{
		ft_putendl_fd(RED"Erreur, arguments invalides"END, 2);
		return (1);
	}
}
