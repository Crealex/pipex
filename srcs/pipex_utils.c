/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:11:40 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/11 10:32:15 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	write_str(int fd, char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		 if (!write(fd, &str[i], 1))
		 	return (0);
		i++;
	}
	return (1);
}

int	find_path(char *cmd_name, char **path, t_cmd *cmd, int nb_cmd)
{
	int i;

	i = 0;
	while (path[i])
	{
		if (access(ft_strjoin(path[i], ft_strjoin("/", cmd_name)), X_OK) != -1)
		{
			if (nb_cmd == 1)
				(*cmd).path1 = ft_strjoin(path[i], ft_strjoin("/", cmd_name));
			else
				(*cmd).path2 = ft_strjoin(path[i], ft_strjoin("/", cmd_name));
			return (1);
		}
		i++;
	}
	return (0);
}

char *find_path_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
			return (env[i]);
		i++;
	}
	return (NULL);
}

void	manage_error(t_cmd	*cmd, char **path, t_fd fd, char *mess)
{
	if (path)
		free_split(path);
	if (fd.pipefd[0] > -1)
		close(fd.pipefd[0]);
	if (fd.pipefd[1])
		close(fd.pipefd[1] > -1);
	if (fd.fd1)
		close(fd.fd1 > -1);
	if (fd.fd2)
		close(fd.fd2 > -1);
	if (cmd->cmd1)
		free_split(cmd->cmd1);
	if (cmd->cmd2)
		free_split(cmd->cmd2);
	if (cmd->path1)
		free(cmd->path1);
	if (cmd->path2)
		free(cmd->path2);
	if (mess)
		perror(mess);
	exit (EXIT_FAILURE);
}
