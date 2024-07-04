/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 13:07:56 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/04 14:07:26 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_first_pipe(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (0);
	while (is_spc(line[i]))
		i++;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	is_invalid(char *line)
{
	int	i;
	int x;

	if (!line || !line[0])
		return (0);
	i = -1;
	x = 0;
	if (is_first_pipe(line))
		return (-2);
	while (line[++i])
	{
		if (is_spc(line[i]))
			continue ;
		if (x > 2 && sep(line[i]) > 2)
			return (i);
		x = sep(line[i]);
		if ((x == 1 || x == 2) && ++i)
			while (line[i] && x != sep(line[i]))
				i++;
		else if ((x == 3 || x == 4) && x == sep(line[i + 1]))
			i++;
	}
	if (x > 2)
		return (-1);
	return (0);
}

void	say_invalid(char *line, int i)
{
	*get_exit_status() = 2;
	if (!isatty(fileno(stdin)))
		write(2, "bash: line 1: ", 14);
	write(2, "syntax error near unexpected token `", 36);
	if (i == -1)
		write(2, "newline", 7);
	if (i == -2)
		write(2, "|", 1);
	else if ((line[i] == '>' || line[i] == '<') && line[i] == line[i + 1])
		write(2, &line[i], 2);
	else
		write(2, &line[i], 1);
	write(2, "'\n", 2);
	if (!isatty(fileno(stdin)))
	{
		ft_perror("bash: line 1: `", line, "'\n");
		exit(*get_exit_status());
	}
}

char	*rm_nl(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i])
		i++;
	if (i && line[i - 1] == '\n')
		line[i - 1] = '\0';
	return (line);
}

char	*take_in(char *in)
{
	if (isatty(fileno(stdin)))
		return (readline(in));
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		line = rm_nl(line);
		return (line);
	}
}

char	*take_line(int *inv)
{
	char	*line;

	line = take_in("🐚 ");
	if (!line)
		return (NULL);
	line = handle_unclosed_quotes(line);
	if (line && ft_strlen(line) > 0)
		add_history(line);
	line = expand_tokens(line, 0);
	if (!line)
		return (NULL);
	*inv = is_invalid(join_quotes(line));
	if (*last_line())
		free(*last_line());
	*last_line() = ft_strdup(line);
	if (!*last_line())
	{
		free(line);
		ft_error(-1);
	}
	return (line);
}

char	*get_line(void)
{
	char	*line;
	int		inv;

	inv = 0;
	line = take_line(&inv);
	if (!line)
		return (NULL);
	while (!line || !line[0] || inv)
	{
		if (inv)
			say_invalid(line, inv);
		free(line);
		line = take_line(&inv);
		if (!line)
			return (NULL);
	}
	return (line);
}


// echo '' ""
// echo "''$USER''"