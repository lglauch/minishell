/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:33:05 by leo               #+#    #+#             */
/*   Updated: 2024/07/05 16:48:27 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_command(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		write(2, "pwd: error retrieving current directory\n", 40);
		return (1);
	}
	printf("%s\n", path);
	free_t(path);
	return (0);
}
