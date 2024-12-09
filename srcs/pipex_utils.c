/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:11:40 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/09 21:32:43 by atomasi          ###   ########.fr       */
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

int	find_path(char *cmd_name, char **path, t_cmd *cmd)
{
	int i;
	char *res;

	i = 0;
	while (path[i])
	{
		if (access(ft_strjoin(path[i], ft_strjoin("/", cmd_name)), X_OK) != -1)
		{
			(*cmd).path1 = path[i];
			return (1);
		}
		i++;
	}
	return (0);
}
