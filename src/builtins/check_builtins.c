/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:53:59 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/02 15:07:17 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_commands(t_lexer *lexer)
{
	if (lexer && lexer->cmd)
	{
		if (ft_strcmp(lexer->cmd[0], "echo") == 0)
			return (1);
		if (ft_strcmp(lexer->cmd[0], "cd") == 0)
			return (2);
		if (ft_strcmp(lexer->cmd[0], "pwd") == 0)
			return (3);
		if (ft_strcmp(lexer->cmd[0], "export") == 0)
			return (4);
		if (ft_strcmp(lexer->cmd[0], "unset") == 0)
			return (5);
		if (ft_strcmp(lexer->cmd[0], "env") == 0)
			return (6);
	}
	return (0);
}

int	call_functions(t_lexer *lexer)
{
	int	i;
	int	exit_code;

	exit_code = 0;
	i = ft_check_commands(lexer);
	if (i == 1)
		exit_code = echo_command(lexer);
	if (i == 2)
	{
		exit_code = cd_command(lexer);
		return (exit_code);
	}
	if (i == 3)
		exit_code = pwd_command();
	if (i == 4)
	{
		exit_code = export_command(lexer);
		return (exit_code);
	}
	if (i == 5)
		return (exit_code = unset_command(lexer));
	if (i == 6)
		exit_code = env_command();
	exit(exit_code);
}
