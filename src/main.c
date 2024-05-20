/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/20 11:57:56 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	intro(void)
{
	if (!isatty(fileno(stdin)))
		return ;
	printf("\033[H\033[J");
	printf("   _   _   _   _   _   _   _   _   _   \n");
	printf("  / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ \n");
	printf(" ( M | I | N | I | S | H | E | L | L )\n");
	printf("  \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \n");
	printf("    ********************************\n");
	printf("\n    Welcome to Minishell by \033]8;;https://github.com/lglauch"
		"\alglauch\033]8;;\a && rchavez\n\n");
	printf("    ********************************\n");
}

void	main_loop(void)
{
	char	*line;
	t_lexer	*tokens;

	line = NULL;
	while (*get_run() == 1)
	{
		line = readline("🐚  ");
		if (line == NULL)
		{
			//free because of ctrl + D
			if (line)
				free(line);
			exit (0);
		}
		if (line && ft_strlen(line) > 0)
			add_history(line);
		tokens = tokenize(line);
		if (!tokens)
			printf("Error tokens returned NULL");
		int i = 0;
		int j;
			
        while (i < count_lex(line))
        {
			j = -1;
            while (tokens[i].cmd[++j])
				printf("\nToken %i, command %i: %s\n", i, j, tokens[i].cmd[j]);
			j = -1;
            while (tokens[i].ops[++j])
				printf("\nToken %i, operator %i: %s\n", i, j, tokens[i].ops[j]);
            i++;
        }
		if (ft_strncmp(line, "exit", 4) == 0 && line[4] == 0)
			break ;
	}
	if (line)
		free(line);
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	envp = (void *)envp;
	if (argc != 1)
		return (1);
	// signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	return (0);
}
