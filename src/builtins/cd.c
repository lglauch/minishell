/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 13:13:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/03 09:53:58 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_cwd(void)
{
	char	buff[4100];
	char	*ev;
	char	*eq;
	int		pos;

	ft_strcpy(buff, "PWD=");
	getcwd(&buff[4], 4096);
	ev = &buff[0];
	eq = &buff[3];
	pos = env_pos(*ft_env(), ev);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else
		return (envp_add(*ft_env(), ev, pos, eq));
}

int	update_ocwd(void)
{
	char	buff[4103];
	char	*ev;
	char	*eq;
	int		pos;

	ft_strcpy(buff, "OLDPWD=");
	getcwd(&buff[7], 4096);
	ev = &buff[0];
	eq = &buff[6];
	pos = env_pos(*ft_env(), ev);
	if (pos >= 0)
		return (envp_update_value(*ft_env(), ev, pos, eq));
	else
		return (envp_add(*ft_env(), ev, pos, eq));
}

int	cd_command(t_lexer *lexer)
{
	char	*path;

	if (lexer->next)
		return (0);
	if (update_ocwd() < 0)
		return (-1);
	if (lexer->cmd[1] == NULL)
	{
		path = env_get_by_name("HOME");
		if (!path || !path[0])
			write(2, "cd: HOME not set\n", 17);
		else if (chdir(path) == -1)
			ft_perror("cd: ", path, ": No such file or directory\n");
		return (1);
	}
	else if (chdir(lexer->cmd[1]) == -1)
	{
		ft_perror("cd: ", lexer->cmd[1], ": No such file or directory\n");
		return (1);
	}
	if (update_cwd() < 0)
		return (-1);
	return (0);
}
