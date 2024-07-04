/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:57:54 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/28 11:45:20 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_exit(char *line, char **args)
{
	int	i;

	i = -1;
	if (args[1])
		args[1] = remove_quotes(args[1]);
	if (args[1])
	{
		if (args[1][0] == '-')
			i++;
		while (args[1][++i])
			if (!ft_isdigit(args[1][i]))
			{
				ft_perror("exit: ", args[1], ": numeric argument required\n");
				return (*get_exit_status() = 255);
			}
	}
	if (args[1] && !args[2])
		*get_exit_status() = ft_atoi(args[1]);
	free_line(line);
	free_args(args);
	env_free(*ft_env());
	link_free();
	while (*get_exit_status() < 0)
		*get_exit_status() = 256 + *get_exit_status();
	return (*get_exit_status());
}
