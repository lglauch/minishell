/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:51:05 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/18 13:59:35 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	*ft_strncpy(char *dest, char *src, size_t len)
{
	size_t	i;

	i = 0;
	if (!src)
		return (0);
	while (src[i] && i < len)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int			j;
	int			i;

	i = 0;
	j = ft_strlen((char *)s);
	while (i <= j)
	{
		if (s[i] == (char)c)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if ((char)c == 0)
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2[0] * -1);
	if (!s2)
		return (s1[0]);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_quote_strip(char *s)
{
	int	i;
	int	j;

	if (ft_strcmp(s, "") == 0)
		i = 0;
	else
		i = ft_strlen(s);
	j = 0;
	if (s && (s[0] == '\"' || s[0] == '\'') && (s[i - 1] == s[0]))
	{
		while (j < i)
		{
			s[j] = s[j + 1];
			j++;
		}
		s[i - 2] = '\0';
	}
	return (s);
}
