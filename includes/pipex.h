/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:17:03 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/10 11:10:54 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

// COLOR
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define BOLD "\033[1m"
# define END "\033[0m"

typedef struct s_cmd
{
	char	**cmd1;
	char	**cmd2;
	char	*path1;
	char	*path2;
}			t_cmd;

typedef struct s_fd
{
	int	fd1;
	int fd2;
	int	pipefd[2];
}			t_fd;

//utils
int	write_str(int fd, char *str);
int	find_path(char *cmd_name, char **path, t_cmd *cmd);
char *find_path_env(char **env);
//split
char	**ft_split_pipex(char const *s, char c);
//split_aux
void handle_single_quote(const char *s, int *i, int *countl);
int	single_quote(char *res,char *s, int *jres, int *i);

#endif