/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chchin <chchin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:36:35 by wricky-t          #+#    #+#             */
/*   Updated: 2022/12/11 18:34:26 by brook            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Minishell
 * 
 * 1. Read line from command line
 * 2. Lexical analysis
 * 3. Parser
 * 4. Executer
 */
int	main(int ac, char **av, char **ev)
{
	char		*cmds;
	t_minishell	ms;

	(void)ac;
	(void)av;
	init_minishell(&ms, ev);
	while (1)
	{
		cmds = readline("> ");
		if (cmds == NULL)
			break ;
		add_history(cmds);
		if (!ft_strncmp(cmds, "cd", 2))
			call_cd(&ms, cmds + 3);
		else if (!ft_strncmp(cmds, "pwd", 3))
			call_pwd(&ms);
		else if (!ft_strcmp(cmds, "env"))
			call_env(&ms);
		else if (!ft_strcmp(cmds, "exit"))
			call_exit(&ms, cmds);
		else if (!ft_strncmp(cmds, "unset", 5))
			call_unset(&ms, cmds + 6);
		else if (!ft_strncmp(cmds, "export", 7))
			call_export(&ms, NULL);
		// lexer(&ms, cmds);
		free(cmds);
	}
	return (0);
}
