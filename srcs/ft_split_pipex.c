/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atomasi <atomasi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 11:42:42 by atomasi           #+#    #+#             */
/*   Updated: 2024/12/10 10:26:06 by atomasi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	counterc_pipex(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i])
				i++;
			if (s[i] == '\'')
			{
				i++;
				while (s[i] != '\'')
					i++;
			}
		}
	}
	return (count);
}

static int count_word_len(const char *s, char c, int *i)
{
	int countl;

	countl = 0;
	while (s[*i] != c && s[*i])
	{
		if (s[*i] == '\'')
			handle_single_quote(s, i, &countl);
		else
		{
			countl++;
			(*i)++;
		}
	}
	return (countl);
}

static int malloc_words_pipex(char **res, const char *s, char c)
{
	int word;
	int countl;
	int i;

	word = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		countl = count_word_len(s, c, &i);
		if (countl > 0)
		{
			res[word] = malloc(countl + 1);
			if (!res[word++])
				return (0);
		}
	}
	res[word] = NULL;
	return (1);
}

static void	fill_pipex(char **res, const char *s, char c)
{
	int	i;
	int	jres;
	int	ires;

	i = 0;
	jres = 0;
	ires = 0;
	while (s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			res[ires][jres] = '\0';
			ires++;
			jres = 0;
			while (s[i] == c)
				i++;
			continue ;
		}
		if (!single_quote(res[ires],(char *)s, &jres, &i))
			res[ires][jres++] = s[i++];
	}
	if (ires < counterc_pipex(s, c))
		res[ires][jres] = '\0';
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**res;
	int		word_count;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	word_count = counterc_pipex(s, c);
	res = malloc(sizeof(char *) * (word_count + 1));
	if (res == NULL)
		return (NULL);
	if (!malloc_words_pipex(res, s, c))
	{
		while (res[i])
		{
			free(res[i]);
			i++;
		}
		free(res);
		return (NULL);
	}
	if (word_count > 0)
		fill_pipex(res, s, c);
	return (res);
}

//Pour les tests
/* int main ()
{
	char *str;
	char **res;
	int i;

	str = "Je teste 'ma fonction' pipex";
	i = 0;
	res = ft_split_pipex(str, ' ');
	while (res[i])
	{
		printf("result %d: %s\n", i, res[i]);
		i++;
	}
	return (0);
} */