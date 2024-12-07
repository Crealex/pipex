/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 18:11:40 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/07 18:18:33 by atomasi          ###   ########.fr       */
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