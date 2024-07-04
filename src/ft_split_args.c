/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:10:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/04 14:47:42 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_splitfree(char **ret, size_t i)
char	**ft_splitfree(char **ret, size_t i)
{
	while (i > 0)
	{
		free(ret[i - 1]);
		i--;
	}
	free(ret);
	return (NULL);
	while (i > 0)
	{
		free(ret[i - 1]);
		i--;
	}
	free(ret);
	return (NULL);
	while (i > 0)
	{
		free(ret[i - 1]);
		i--;
	}
	free(ret);
	return (NULL);
}

int	arg_count(char *s)
{
	int	i;
	int	x;
	int	count;

	i = 0;
	count = 0;
	if (!s || !s[0])
		return (0);
	while (s[i])
	{
		x = sep(s[i]);
		if (i > 0 && (is_spc(s[i]) || x) && !is_spc(s[i - 1]) && !sep(s[i - 1]))
			count++;
		if (x && ++i)
		{
			count++;
			while (s[i] && x != sep(s[i]) && x < 3)
				i++;
		}
		if (s[i] && (x < 3 || x == sep(s[i])))
			i++;
	}
	if (!s[i] && !is_spc(s[i - 1]) && !sep(s[i - 1]) && !x)
		count++;
	return (count);
}

int	ft_arglen(char *arg)
{
	int	i;
	int	x;

	if (!arg || !arg[0])
		return (0);
	i = 0;
	x = sep(arg[i]);
	if (x)
	{
		i++;
		if (x > 2 && x != sep(arg[i]))
			return (i);
		while (arg[i] && x != sep(arg[i + 1]))
			i++;
		if (arg[i])
			i++;
		return (i);
	}
	while (arg[i] && !is_spc(arg[i]) && !sep(arg[i]))
		i++;
	return (i);
}

int	ft_argcpy(char *dst, char *src)
{
	int	i;
	int	x;

	i = -1;
	if (!src || !dst || !src[0])
		return (0);
	x = sep(src[0]);
	if (x && i++)
	{
		dst[i] = src[i];
		if (x > 2 && x != sep(src[i + 1]))
		{
			dst[++i] = '\0';
			return (1);
		}
		while (src[++i] && x != sep(src[i]))
			dst[i] = src[i];
		if (x == sep(src[i++]))
			dst[i - 1] = src[i - 1];
	}
	else
		while (src[++i] && !is_spc(src[i]) && !sep(src[i]))
			dst[i] = src[i];
	dst[i] = '\0';
	return (i);
}

char	**ft_split_args(char *str)
{
	int		i;
	size_t	j;
	int		count;
	char	**ret;

	i = 0;
	j = 0;
	count = arg_count(str);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = NULL;
	while (str && str[j] && i < count)
	{
		while (str[j] && is_spc(str[j]))
			j++;
		ret[i] = (char *)malloc(sizeof(char) * (ft_arglen(&str[j]) + 1));
		if (!ret[i])
			return (ft_splitfree(ret, i));
		j += ft_argcpy(ret[i++], &str[j]);
	}
	return (ret);
}
