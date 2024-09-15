/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkreise <dkreise@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 12:42:43 by dkreise           #+#    #+#             */
/*   Updated: 2023/12/28 17:02:09 by dkreise          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordcnt(char const *s, char c)
{
	int	flg;
	int	cnt;

	cnt = 0;
	flg = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (flg == 1)
				cnt ++;
			flg = 0;
		}
		else
			flg = 1;
		s ++;
	}
	if (flg == 1)
		cnt ++;
	return (cnt);
}

static int	ft_wordlen(char const *s, char c, int i)
{
	int	len;

	len = 0;
	if (s[i] == '\'')
	{
		len ++;
		i ++;
		c = '\'';
	}
	else if (s[i] == '\"')
	{
		len ++;
		i ++;
		c = '\"';
	}
	while (s[i] != c && s[i] != '\0')
	{
		len ++;
		i ++;
	}
	if (s[i] == '\'' || s[i] == '\"')
		len ++;
	return (len);
}

char	**ft_free(char **words, int j)
{
	while (j-- > 0)
		free(words[j]);
	free(words);
	words = NULL;
	return (words);
}

char	*do_substr(char const *s, unsigned int start, size_t len)
{
	if (s[start] == '\'' || s[start] == '\"')
	{
		start ++;
		len -= 2;
	}
	return (ft_substr(s, start, len));
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	int		word_cnt;
	int		i;
	int		j;

	word_cnt = ft_wordcnt(s, c);
	words = malloc((word_cnt + 1) * sizeof(char *));
	if (words == NULL)
		return (0);
	i = -1;
	j = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			words[j] = do_substr(s, i, ft_wordlen(s, c, i));
			if (!words[j])
				return (ft_free(words, j));
			i += ft_wordlen(s, c, i) - 1;
			j ++;
		}
	}
	words[j] = NULL;
	return (words);
}
/*
int main(void)
{
	int i = 0;
	char **ar = ft_split("lorem amet, elit. \'\"Sed non risus\"\' lala", ' ');
	while (ar[i])
	{
		printf("%s\n", ar[i]);
		i ++;
	}
	return (0);
}*/
