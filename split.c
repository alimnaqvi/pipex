/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anaqvi <anaqvi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 12:53:55 by anaqvi            #+#    #+#             */
/*   Updated: 2024/11/26 13:58:21 by anaqvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_in_quotes(char const **s, size_t *count, int *in_word,
		char *quote_char)
{
	if (!*in_word)
	{
		*in_word = 1;
		*quote_char = **s;
		(*count)++;
	}
	else if (*quote_char == **s)
	{
		*in_word = 0;
		*quote_char = 0;
	}
}

static size_t	count_words(char const *s, char c)
{
	size_t	count;
	int		in_word;
	char	quote_char;

	count = 0;
	in_word = 0;
	quote_char = 0;
	while (*s)
	{
		if (*s == '\'' || *s == '\"')
			handle_in_quotes(&s, &count, &in_word, &quote_char);
		else if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c && !quote_char)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*get_next_word(char const **s, char c)
{
	char		*word;
	size_t		len;
	char const	*start;
	char		quote_char;

	start = *s;
	len = 0;
	quote_char = 0;
	while (**s && (**s != c || quote_char))
	{
		if (**s == '\'' || **s == '\"')
		{
			if (!quote_char)
				quote_char = **s;
			else if (quote_char == **s)
				quote_char = 0;
		}
		len++;
		(*s)++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word)
		ft_strlcpy(word, start, len + 1);
	return (word);
}

static char	**free_result(char **result, size_t i)
{
	while (i > 0)
	{
		i--;
		free(result[i]);
	}
	free(result);
	return (NULL);
}

char	**ft_split_with_quotes(char const *s, char c)
{
	char	**result;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			result[i] = get_next_word(&s, c);
			if (!result[i])
				return (free_result(result, i));
			i++;
		}
		else
			s++;
	}
	result[i] = NULL;
	return (result);
}
