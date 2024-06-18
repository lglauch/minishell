/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:07:56 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/18 16:15:40 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int sep(char c);

int	is_invalid(char *line)
{
	int	i;
	int x;

	if (!line || !line[0])
		return (0);
	i = -1;
	x = 0;
	while (line[++i])
	{
		if (x > 2 && sep(line[i]) > 2)
			return (i);
		x = sep(line[i]);
		if (x == 1 || x == 2)
		{
			i++;
			while (line[i] && x != sep(line[i]))
				i++;
		}
		else if (x == 3 || x == 4)
			if (x == sep(line[i + 1]))
				i++;
	}
	return (0);
}

void	say_invalid(char *line, int i)
{
	printf("Syntax error near unexpected token '");
	if (i == -1)
		printf("newline");
	else
		printf("%c", line[i]);
	printf("'\n");
}

char	*get_line(void)
{
	char	*line;
	int		inv;

	line = readline("🐚 ");
	if (!line)
		return (NULL);
	line = handle_unclosed_quotes(line);
	line = expand_tokens(line);
	inv = is_invalid(line);
	while (!line || !line[0] || inv)
	{
		free(line);
		if (inv)
			say_invalid(line, inv);
		line = readline("🐚 ");
		if (!line)
			return (NULL);
		line = handle_unclosed_quotes(line);
		line = expand_tokens(line);
		inv = is_invalid(line);
	}
	return (line);
}

int	open_mock(char *str, int mode, int per)
{
	int fd;

	if (per)
		fd = open(str, mode, per);
	else
		fd = open(str, mode);
	printf("\nFile %s opened with code %i\n", str, fd);
	return (fd);
}
int	close_mock(int fd)
{
	int i;

	i = close(fd);
	printf("\nFile %i closed with code %i\n", fd, i);
	return (i);
}
