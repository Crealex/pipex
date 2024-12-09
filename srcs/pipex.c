/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:27:00 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/09 21:59:12 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

void	child1_process(t_cmd cmd, t_fd fd)
{
	close(fd.pipefd[1]);

}

int main(int argc, int **argv, char **env)
{
	t_fd	fd;
	t_cmd	cmd;
	int		pid1;
	int		pid2;

	if (argc == 5)
	{
		fd.fd1 = open(argv[1], O_RDONLY);
		fd.fd2 = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0744);
		if (parsing(argv, env, &cmd))
			return (1);
		pid1 = fork; // creer l'enfant qui servira pour cmd1
		if (pid1 < 0)
			return (1);
		if (pid1 == 0)
		{
			//execution de la premiere commande dans child 1
			dup2(fd.fd1, STDIN_FILENO);
			//fini par execve la commande et donc ecrase le reste du programme
		}
		pid2 = fork(); // creer l'enfant qui servira pour cmd1
		if (pid2 < 0)
			return (1);
		else if (pid2 == 0)
		{
			dup2(STDOUT_FILENO, fd.fd2);
			//execution de la deuxieme commande dans child2
			//fini par execve la deuxieme commande et donc ecrase le reste du programme
		}
		// finir proprement le porgramme parent (fermer les fichier, free des trucs, etc...)
	}
	else
		perror("Erreur, arguments invalides");
}
