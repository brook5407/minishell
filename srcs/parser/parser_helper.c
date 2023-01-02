/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wricky-t <wricky-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:45:50 by wricky-t          #+#    #+#             */
/*   Updated: 2023/01/02 17:56:15 by wricky-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * TODO:
 * 1. Grammar checker
 * 		- check if the token is expected.
 * 			- if it's expected, store to cmd_list
 *          - if not expected, free the current node, move on to the next
 *            command block (look for pipe if have)
 * 2. Builder functions - help building the cmd_list, based on the current
 *    grammar.
 * 	  START: if it's redirection / heredoc, do what POST_RDR do.
 *           if command name, store to cmd name
 *    FREE_FORM: if string, store to argument
 * 				 if it's redirection do what POST_RDR do
 *               if it's cmd/ext cmd, store to argument as well. this is
 *               because it's impossible for the builder to store as cmd name
 *               when in free form.
 *    POST_RDR: if it's heredoc / append mode, need to specify
 *    CMD_ONLY: store to cmd name
*/

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
	{
		perror("Initialize cmd block failed!\n");
		return (NULL);
	}
	cmd->cmd_name = NULL;
	cmd->args = NULL;
	cmd->infile = NULL;
	cmd->outfile = NULL;
	return (cmd);
}

void	free_iofile(void *content)
{
	t_file	*iofile;

	iofile = content;
	free(iofile->name);
}

void	free_arg(void *content)
{
	char	*name;

	name = content;
	free(name);
}

void	free_cmd_block(t_cmd *cmd)
{
	cmd->cmd_name = NULL;
	ft_lstclear(&cmd->args, free_arg);
	ft_lstclear(&cmd->infile, free_iofile);
	ft_lstclear(&cmd->outfile, free_iofile);
}

/**
 * IDEA: PARSER HELPER
 * 1. Need a function to destroy parser
 * 2. Need a function to initialize cmd_block
 * 3. Need a function to free cmd_block
 * 4. Destroy parser when there's syntax error
 * 5. Destroy parser when encounter a pipe
 * 6. Need a function to free the infile/outfile list
 * 7. Free args list = ft_lstiteri(cmd->args, free);
 */

/**
 * @brief Initialize parser helper
 *
 * @param hlpr pointer to parser helper
 */
void	init_parser(t_parser *hlpr, int reset)
{
	hlpr->curr_grammar = START;
	if (reset == 1)
		free_cmd_block(hlpr->cmd);
	hlpr->cmd = init_cmd();
	apply_grammar(hlpr, START);
}
