/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipex_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:28:31 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/11 09:57:03 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void handle_single_quote(const char *s, int *i, int *countl)
{
	(*i)++;  // Skip the opening quote
	while (s[*i] != '\'' && s[*i])
	{
		(*countl)++;
		(*i)++;
	}
	(*i)++;  // Skip the closing quote
}

int	single_quote(char *res,char *s, int *jres, int *i)
{
	int si;
	int ri;

	si = *i;
	ri = *jres;
	if (s[si] == '\'')
	{
		si++;
		while (s[si])
		{
			if (s[si] == '\'')
			{
				res[++ri] = '\0';
				*jres = ri;
				*i = si;
				return (1);
			}
			res[ri] = s[si];
			si++;
			ri++;
		}
		return (0);
	}
	else
		return (0);
}

void	free_split(char **res)
{
	int i;

	i = 0;
		while (res[i])
	{
		if (res[i])
			free(res[i]);
		i++;
	}
	free(res);
}
