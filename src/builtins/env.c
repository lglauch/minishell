/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 12:25:08 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/02 15:31:05 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env_has_value(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=')
		i++;
	i++;
	if (str[i] == 0)
		return (0);
	return (1);
}

int	env_command(void)
{
	char	**list;
	int			i;

	list = *ft_env();
	if (list == NULL)
		return (1);
	i = 0;
	while (list[i])
	{
		if (env_has_value(list[i]) == 1)
			printf("%s\n", list[i]);
		i++;
	}
	return (0);
}
