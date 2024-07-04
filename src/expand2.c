/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 09:47:16 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/04 10:33:36 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*extract_env(char *str, char *buff)
{
	size_t	i;

	i = 1;
	while(str[i] && !is_spc(str[i]) && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		buff[i - 1] = str[i];
		i++;
	}
	buff[i - 1] = '\0';
	return (buff);
}

size_t	expand_len(char *str, char *buff, int mode)
{
	size_t	i;
	size_t	ret;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1]) &&
			(is_quoted(str, i) != 1 || mode)&& str[i + 1] == '?' && ++i)
			ret += 7;
		else if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1]) &&
			(is_quoted(str, i) != 1 || mode))
		{
			ret += ft_strlen(env_get_by_name(extract_env(&str[i], buff)));
			while (str[i + 1] && !is_spc(str[i + 1]) &&
				(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
				i++;
		}
		else
			ret++;
		i++;
	}
	return (ret);
}

void	str_app(char *dst, char *buff, size_t *j)
{
	size_t	i;

	i = 0;
	if (!buff)
		return ;
	while (buff[i])
	{
		dst[i] = buff[i];
		i++;
	}
	*j += ft_strlen(buff);
}

void	str_int(char *dst, size_t *j)
{
	int		i;
	int		len;

	i = *get_exit_status();
	len = 0;
	if (i == 0)
		len = 1;
	else
		while (i)
		{
			len++;
			i = i / 10;
		}
	i = *get_exit_status();
	*j += len;
	while (len)
	{
		dst[len - 1] = i % 10 + '0';
		i = i / 10;
		len--;
	}
}

void	do_expand(char *str, char *buff, char *ret, int mode)
{
	size_t	i;
	size_t	j;

	i = -1;
	j = 0;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1]) &&
			(is_quoted(str, i) != 1 || mode) && str[i + 1] == '?' && ++i)
			str_int(&ret[j], &j);
		else if (str[i] == '$' && str[i + 1] && !is_spc(str[i + 1]) &&
			(is_quoted(str, i) != 1 || mode))
		{
			str_app(&ret[j], env_get_by_name(extract_env(&str[i], buff)), &j);
			while (str[i + 1] && !is_spc(str[i + 1]) &&
				(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
				i++;
		}
		else
			ret[j++] = str[i];
	}
	ret[j] = '\0';
}

char	*expand_tokens(char	*str, int mode)
{
	char	*buff;
	char	*ret;

	if (!str)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!buff)
		return (free(str), NULL);
	ret = (char *)malloc(sizeof(char) * (expand_len(str, buff, mode) + 1));
	if (!ret)
		return (free(str), free(buff), NULL);
	do_expand(str, buff, ret, mode);
	free(str);
	free(buff);
	return (ret);
}
