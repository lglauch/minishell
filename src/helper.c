/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:05:50 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/04 14:45:01 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	make_expand(int quotes)
{
	int	rtr;

	rtr = 0;
	if (!quotes)
	{
		rtr = 1;
	}
	return (rtr);
}

size_t	ft_countwords(char const *s, char c)
{
	size_t	x;
	size_t	i;

	x = 0;
	i = 0;
	if (*s)
		i++;
	while (s[i])
	{
		if (s[i] == c && s[i - 1] != c)
			x++;
		i++;
	}
	if (*s && s[i] == '\0' && s[i - 1] != c)
		x++;
	return (x);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		q;

	i = 0;
	j = 0;
	q = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			q = str[i];
			while (str[++i] && str[i] != q)
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		if (str[i])
			i++;
	}
	str[j] = '\0';
	return (str);
}

void shift_left(char *str, int spc, size_t *p)
{
	size_t	i;

	if (!str || !str[0] || spc)
		return ;
	i = 0;
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] ='\0';
	if (p)
		(*p)--;
}

char	*remove_uquotes(char *str)
{
	size_t	i;
	size_t	q;
	int	spc;

	i = 0;
	q = 0;
	spc = 0;
	while (str && str[i] && ++i)
	{
		if (str[i - 1] == '\'' || str[i - 1] == '\"')
		{
			if (q && str[i - 1] == str[q - 1])
			{
				shift_left(&str[i - 1], spc, &i);
				shift_left(&str[q - 1], spc, &i);
				q = 0;
				spc = 0;
			}
			else if (!q)
				q = i;
		}
		else if(q && (is_spc(str[i - 1]) || str[i - 1] == '$' || sep(str[i - 1])))
			spc = 1;
	}
	return (str);
}

char	*adj_quotes(char *str)
{
	size_t	i;
	char	q;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if	((str[i] == '\'' || str[i] == '\"') && (!i || !is_spc(str[i - 1])) && (!is_spc(str[i + 1])))
		{
			q = str[i];
			shift_left(&str[i], 0, NULL);
			while (str[i] && str[i] != q)
				i++;
			if (str[i])
				shift_left(&str[i], 0, NULL);
		}
		else
			i++;
	}
	return (str);
}

char	*join_quotes(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && (str[i] == str[i + 1]) && !is_quoted(str, i + 1))
		{
			shift_left(&str[i], 0, NULL);
			shift_left(&str[i], 0, NULL);
		}
		i++;
	}
	return (str);
	// return (adj_quotes(str));
}

int	is_forkable(t_lexer *temp)
{
		if (ft_strcmp("cd", temp->cmd[0]) && ft_strcmp("export", temp->cmd[0]) && ft_strcmp("unset", temp->cmd[0]))
			return (1);
		return (0);
}

int	is_quoted(char *str, size_t index)
{
	size_t	i;
	int		sq;
	int		dq;

	sq = 0;
	dq = 0;
	i = 0;
	if (!str || index >= ft_strlen(str))
		return (0);
	while(str[i] && i <= index)
	{
		if (str[i] == '\'' && !dq)
			sq = !sq;
		else if (str[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq)
		return (1);
	if (dq)
		return (2);
	return (0);
}
