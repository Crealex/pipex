/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:27:00 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/08 22:13:20 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>

int main(void)
{
	pid_t	pid;
	int		pipefd[2];
	char	buff;
	int		fd;

	//test d'appel du commande systeme

	//test pour creer et ecrire directement dans un fichier
	fd = open("./test.txt", O_WRONLY);
	printf("fd : %d\n", fd);
	write_str(fd, "test de ma petite experience pas piquee des hannetons");
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
	}

	return (0);
}
