/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:11:40 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/13 14:15:16 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	write_str(int fd, char *str)
{
	int	i;

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
	int		i;
	char	*path_name;
	char	*full_path;

	i = 0;
	path_name = ft_strjoin("/", cmd_name);
	while (path[i])
	{
		full_path = ft_strjoin(path[i], path_name);
		if (access(full_path, X_OK) != -1)
		{
			free(path_name);
			if (nb_cmd == 1)
				(*cmd).path1 = ft_strdup(full_path);
			else
				(*cmd).path2 = ft_strdup(full_path);
			return (free(full_path), 1);
		}
		free(full_path);
		i++;
	}
	return (free(path_name), 0);
}

char	*find_path_env(char **env)
{
	int	i;

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
