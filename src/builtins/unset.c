/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:46:15 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/02 15:15:04 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_command(t_lexer *temp)
{
	char	*name;
	char	**env;
	int		i;

	name = temp->cmd[1];
	if (!name)
		return (0);
	env = *ft_env();
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], name, ft_strlen(name)))
		{
			free(env[i]);
			while (env[++i])
				env[i - 1] = env[i];
			env[i - 1] = NULL;
			return (0);
		}
	}
	return (0);
}
