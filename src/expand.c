/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:08:57 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/04 15:18:48 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_inject_value(char *str, char *placeholder, char *envp_value)
{
	char	*rtr;
	char	*pos;
	int		str_len;
	int		placeholder_len;
	int		envp_value_len;

	str_len = ft_strlen(str);
	placeholder_len = ft_strlen(placeholder);
	envp_value_len = ft_strlen(envp_value);
	pos = ft_strnstr(str, placeholder, ft_strlen(str));
	if (pos == NULL)
		return (ft_strdup(str));
	rtr = malloc(sizeof(char) * (str_len - placeholder_len
				+ envp_value_len + 1));
	if (rtr == NULL)
		return (NULL);
	ft_strncpy(rtr, str, pos - str);
	rtr[pos - str] = 0;
	ft_strlcat(rtr, envp_value, ft_strlen(rtr) + envp_value_len);
	ft_strlcat(rtr, pos + placeholder_len,
		str_len - (pos - str) - placeholder_len + 1);
	return (rtr);
}

char	*transform_variable(char *str, char *envp_name, char *envp_value)
{
	char	*placeholder;
	char	*new;

	if (envp_value == NULL)
		return (ft_strdup(""));
	placeholder = ft_strjoin("$", envp_name);
	new = ft_inject_value(str, placeholder, envp_value);
	free (placeholder);
	return (new);
}

char	*expand_tokens(char *str)
{
	int		i;
	int		j;
	char	*envp_name;
	char	*envp_value;
	char	*new;

	i = 0;
	new = ft_strdup(str);
	while (str[i])
	{
		if (str[i++] != '$')
			continue ;
		j = 0;
		envp_name = malloc(sizeof(char) * ft_strlen(&str[i]) + 1);
		while (str[i] && str[i] != ' ' && str[i] != '"' && str[i] != '$')
			envp_name[j++] = str[i++];
		envp_name[j] = 0;
		envp_value = env_get_by_name(envp_name);
		if (envp_value == NULL)
			return (new);
		new = transform_variable(str, envp_name, envp_value);
		free (envp_name);
	}
	return (new);
}
