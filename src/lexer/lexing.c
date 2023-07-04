/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgerguri <dgerguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 15:46:22 by dgerguri          #+#    #+#             */
/*   Updated: 2023/07/04 20:36:46 by dgerguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	count_redirections(char **tokens, int start, char c, int type)
// {
// 	int i;
// 	int	amount;

// 	i = 0;
// 	amount = 0;
// 	while (tokens[start] && tokens[start][i] != '|' && type == 1)
// 	{
// 		if (tokens[start][i] == c && ft_strlen(tokens[start][i]) == 1);
// 			amount++;
// 		i++;
// 	}
// 	while (tokens[start] && tokens[start][i] != '|' && type == 2)
// 	{
// 		if (tokens[start][i] == c && ft_strlen(tokens[start][i]) == 2);
// 			amount++;
// 		i++;
// 	}
// 	return (amount);
// }
// // void	allocation(t_commands *commands, int amount)
// // {
// // 	 = malloc(sizeof(char *) * (word_count + 1));
// // 	if (ret == NULL)
// // 		return (NULL);
// // }
// int	mem_allocation(t_commands *commands, char **tokens, int start)
// {
// 	int	re_input;
// 	int	re_output;
// 	int	here_doc;
// 	int	re_output_append;

// 	while (tokens[start])
// 	{
// 		re_input = count_redirections(tokens, start, '<', 1);
// 		commands->input = malloc(sizeof(char *) * (re_input) + 1);
// 		if (commands->input == NULL)
// 			return (NULL);
// 		re_output = count_redirections(tokens, start, '<', 1);
// 		commands->output = malloc(sizeof(char *) * (re_output) + 1);
// 		if (commands->output == NULL)
// 			return (NULL);
// 		here_doc = count_redirections(tokens, start, '<', 1);
// 		commands->heredoc_delim = malloc(sizeof(char *) * (here_doc) + 1);
// 		if (commands->heredoc_delim == NULL)
// 			return (NULL);
// 	}
// 	return(start);
// }

// t_commands	*command_type(char **tokens)
// {
// 	t_commands	*commands; //change the name
// 	int			array;
// 	int			i;

// 	commands = NULL;
// 	array = 0;
// 	i = 0;

// 	while (tokens[array])
// 	{
// 		while (tokens[array][i] != '|')
// 		{
// 			array = mem_allocation(commands, tokens, array); //change the name!
// 		}
// 		array++;
// 		commands = commands->next;
// 	}
// }

void	lexing(char *command_line, t_lexer *tokens)
{
	t_commands *cmd;

	quote_checker(command_line, tokens);
	tokens->tokens = split_to_tokens(command_line, ' ');
	syntax_checker(tokens->tokens);
	// cmd = command_type(tokens->tokens);   //jhesso I have no idea what to name it :(


	//This is to test the tokens!
	// int i = 0;
	// while (tokens->tokens[i] != NULL)
	// {
	// 	printf("%s\n", tokens->tokens[i]);
	// 	i++;
	// }
}
