/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 17:17:03 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/09 16:29:52 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../libft/libft.h"

int	write_str(int fd, char *str);
//split_aux
static void handle_single_quote(const char *s, int *i, int *countl);
static int	single_quote(char *res,char *s, int *jres, int *i);

#endif