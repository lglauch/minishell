/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:25:12 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/02 15:23:16 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_free_envp(t_envp *head)
{
	t_envp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}

char	*ft_envp_get_value(char *envp)
{
	int		i;
	int		j;
	int		len;
	char	*value;

	value = NULL;
	i = 0;
	j = 0;
	if (!envp)
		return (0);
	while (envp[i] != '=' && envp[i] != 0)
		i++;
	while (envp[j] != 0)
		j++;
	if (envp[i] == 0)
		return (NULL);
	len = j - i;
	value = malloc(sizeof(char) * (len + 1));
	if (!value)
		return (NULL);
	j = 0;
	while (envp[++i])
		value[j++] = envp[i];
	value[j] = 0;
	return (value);
}

char	*ft_envp_get_name(char *envp)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	if (!envp)
		return (0);
	while (envp[i] != '=' && envp[i] != 0)
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	i = 0;
	while (envp[i] != '=' && envp[i] != 0)
	{
		name[i] = envp[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

t_envp	*ft_create_envp(char **envp)
{
	t_envp	*head;
	t_envp	*current;
	t_envp	*new_node;
	int		j;

	j = -1;
	head = NULL;
	current = NULL;
	while (envp[++j])
	{
		new_node = malloc(sizeof(t_envp));
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		if (!new_node)
			return (ft_free_envp(head), NULL);
		new_node->name = ft_envp_get_name(envp[j]);
		new_node->value = ft_envp_get_value(envp[j]);
		if (!new_node->name || !new_node->value)
			return (ft_free_envp(head), NULL);
		current = new_node;
	}
	return (head);
}

void	env_free(char **ret)
{
	int	i;

	i = 0;
	if (!ret)
		return ;
	while (ret[i])
		free (ret[i++]);
	free(ret);
}

char	**ft_make_envp(char **ret)
{
	char	buffer[4096];

	ret[0] = ft_strdup(ft_strjoin("PWD=", getcwd(buffer, sizeof(buffer))));
	if (!ret[0])
	{
		free(ret);
		return (0);
	}
	ret[1] = ft_strdup("SHLVL=0");
	if (!ret[1])
	{
		free(ret[0]);
		free(ret);
		return (0);
	}
	ret[2] = ft_strdup("_=");
	if (!ret[2])
	{
		free(ret[0]);
		free(ret[1]);
		free(ret);
		return (0);
	}
	ret[3] = NULL;
	return (ret);
}

char	**init_env(char **env)
{
	int		i;
	char	**ret;

	i = 0;
	while (env[i])
		i++;
	if (env && env[0])
		ret = (char **)malloc(sizeof(char *) * (i + 1));
	else
		ret = (char **)malloc(sizeof(char *) * (3 + 1));
	if (!ret)
		return (NULL);
	if (!env || !env[0])
		return (ft_make_envp(ret));
	i = 0;
	while (env[i])
	{
		ret[i] = ft_strdup(env[i]);
		if (!ret[i])
			return (env_free(ret), NULL);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
