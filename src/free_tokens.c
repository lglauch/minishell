/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 14:16:14 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/05/22 15:29:38 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_lexer *tokens, char **args, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = count_lex(line);
	while (i < j)
	{
		free(tokens[i].cmd);
		free(tokens[i].ops);
		free(tokens[i].path);
		i++;
	}
	free(tokens);
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
	free(line);
}
