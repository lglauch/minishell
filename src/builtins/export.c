/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:35:28 by leo               #+#    #+#             */
/*   Updated: 2024/07/04 12:32:39 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_len(char **env)
{
	int i;

	i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i + 1);
}

int	env_cmp(char *s1, char *s2)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (!s1 || !s2)
		return (0);
	while(s1[i] && s2[i] && s1[i] != '=' && s2[i] != '='
		&& s1[i] != '+' && s2[i] != '+')
	{
		if (s1[i] != s2[i])
			ret = s1[i] - s2[i];
		i++;
	}
	if (!ret)
		ret = s1[i] - s2[i];
	if (s1[i] == '=' || s1[i] == '+')
		ret -= s1[i];
	if (s2[i] == '=' || s2[i] == '+')
		ret += s2[i];
	return (ret);
}

int	env_pos(char **env, char *cmd)
{
	int	i;

	i = 0;
	if (!env)
		return (-1);
	while (env[i])
	{
		if (!env_cmp(env[i], cmd))
			return (i);
		i++;
	}
	return (-1);
}

int	envp_add(char **env, char *cmd, int pos, char *eq)
{
	char	**new;
	int		i;

	new = (char **)malloc(sizeof(char *) * (env_len(env) + 1));
	if (!new)
		return (-1);
	if (eq && eq != cmd && *(eq - 1) == '+')
	{
		eq--;
		while (*(++eq))
			*(eq - 1) = *(eq);
		*(eq - 1) = '\0';
	}
	i = -1;
	while (env[++i])
		new[i] = env[i];
	new[i] = ft_strdup(cmd);
	if (!new[i])
		return (free(new), -1);
	new[++i] = NULL;
	*ft_env() = new;
	if (pos >= 0)
		free(env);
	return (*get_exit_status() = 0);
}

int	envp_update_value(char **env, char *cmd, int pos, char *eq)
{
	char	*new;

	new = NULL;
	if (eq && eq != cmd && *(eq - 1) == '+' && *(eq + 1))
		new = ft_strjoin(env[pos], (eq + 1));
	else if (eq)
		new = ft_strdup(cmd);
	else
		return (0);
	if (!new)
		return (-1);
	free(env[pos]);
	env[pos] = new;
	return (*get_exit_status() = 0);
}

char	*get_ev(int *v)
{
	int		i;
	char	*line;
	char	*ev;

	i = 0;
	line = remove_uquotes(join_quotes(*last_line()));
	while (line[i] && is_spc(line[i]))
		i++;
	if (ft_strncmp("export", &line[i], 6))
	{
		*v = 0;
		while (line[i] && ft_strncmp("export", &line[i], 6))
			i++;
	}
	else
		*v = 1;
	line[i] = 'D';
	i += 6;
	while (line[i] && is_spc(line[i]))
		i++;
	ev = remove_quotes(&line[i]);
	return (ev);
}

int	export_command(t_lexer *lexer)
{
	char	*ev;
	char	*eq;
	int		pos;
	int		v;

	ev = get_ev(&v);
	eq = ft_strchr(ev, '=');
	pos = env_pos(*ft_env(), ev);
	if (!ev && eq)
	{
		write(2, "export : INVALID USAGE\n", 23);
		return (*get_exit_status() = 0);
	}
	if (eq && (eq == ev || (ft_strchr(ev, '-') && ft_strchr(ev, '-') < eq)
		|| is_spc(*(eq - 1))))
	{
		ft_perror_spc("export : '", ev, "' : not a valid identifier\n");
		return (*get_exit_status() = 1);
	}
	if (lexer->next || !eq || !v)
		return (*get_exit_status() = 0);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else
		return (envp_add(*ft_env(), ev, pos, eq));
}
