/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/05/14 13:38:50 by lglauch          ###   ########.fr       */
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
		"\alglauch\033]8;;\a && ...\n\n");
	printf("    ********************************\n");
}

void	main_loop(void)
{
	char	*line;
	char	**tokens;

	line = NULL;
	while (*get_run() == 1)
	{
		line = readline("🐚  ");
		if (!line)
			break ;
		if (line && ft_strlen(line) > 0)
			add_history(line);
		tokens = tokenizer(line);
		if (!tokens)
			printf("Error tokens returned NULL");
		int i = 0;
        while (tokens[i] != NULL)
        {
            printf("tokens[%d] = %s\n", i, tokens[i]); //delete later just a tester
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
	intro();
	main_loop();
	printf("exit\n");
	return (0);
}
