/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 14:20:41 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/27 12:09:25 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_pathjoin(char *path, char *cmd)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(cmd) + 2));
	if (!ret)
		return (NULL);
	if (path)
		while (path[j])
			ret[i++] = path[j++];
	j = 0;
	ret[i++] = '/';
	while (cmd[j])
		ret[i++] = cmd[j++];
	ret[i] = '\0';
	return (ret);
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

char	*path_finder(char *command, char *envp)
{
	int		i;
	char	**paths;
	char	*ret;

	if (!command)
		return (ft_strdup("not_found"));
	paths = ft_split(envp, ':');
	if (!paths)
		return (NULL);
	i = ft_countwords(envp, ':');
	while (--i >= 0)
	{
		ret = ft_pathjoin(paths[i], command);
		if (!ret)
			return (ft_splitfree(paths, i), NULL);
		if (access(ret, X_OK) == 0)
		{
			ft_splitfree(paths, i + 1);
			return (ret);
		}
		free(paths[i]);
		free(ret);
	}
	return (free(paths), ft_strdup("not_found"));
}
