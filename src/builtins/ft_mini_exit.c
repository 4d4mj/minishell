/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mini_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaterji <akaterji@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:32:00 by akaterji          #+#    #+#             */
/*   Updated: 2024/07/30 09:14:38 by akaterji         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// void print_t_lexer(const t_lexer *lexer) {
//     if (lexer == NULL) {
//         printf("  t_lexer: NULL\n");
//         return;
//     }

//     printf("  t_lexer:\n");
//     printf("    lexer_comp: %s\n", lexer->lexer_comp != NULL
// ? lexer->lexer_comp : "NULL");
//     printf("    token: %d\n", lexer->token);
//     printf("    i: %d\n", lexer->i);
//     printf("    path: %s\n", lexer->path != NULL ? lexer->path : "NULL");
//     printf("    next: %p\n", (void *)lexer->next);
//     printf("    prev: %p\n", (void *)lexer->prev);
// }

// // Function to print t_cmd structure
// void print_t_cmd(const t_cmd *cmd) {
//     if (cmd == NULL) {
//         printf("NULL\n");
//         return;
//     }

//     printf("t_cmd structure:\n");
//     // Print t_cmd fields
//     printf("  commands:\n");
//     if (cmd->commands != NULL) {
//         for (int i = 0; cmd->commands[i] != NULL; i++) {
//             printf("    [%d]: %s\n", i, cmd->commands[i]);
//         }
//     } else {
//         printf("    NULL\n");
//     }
//     printf("  num_commands: %d\n", cmd->num_commands);
//     printf("  input_redir: %d\n", cmd->input_redir);
//     printf("  input_file: %s\n", cmd->input_file != NULL
// ? cmd->input_file : "NULL");
//     printf("  output_redir: %d\n", cmd->output_redir);
//     printf("  output_file: %s\n", cmd->output_file != NULL
// ? cmd->output_file : "NULL");
//     printf("  heredoc: %s\n", cmd->heredoc != NULL ? cmd->heredoc : "NULL");
//     printf("  flags: %d\n", cmd->flags);
//     printf("  next: %p\n", (void *)cmd->next);
//     printf("  prev: %p\n", (void *)cmd->prev);

//     // Print t_lexer structure recursively
//     print_t_lexer(cmd->lexer_list);
// }

int	ft_is_str_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_cmd_delete_prev(t_cmd **cmd_list, t_cmd *next_cmd)
{
	t_cmd	*current_cmd;

	current_cmd = NULL;
	next_cmd = next_cmd->next;
	while (*cmd_list != next_cmd)
	{
		current_cmd = (*cmd_list)->next;
		if ((*cmd_list)->lexer_list != NULL)
			ft_lexer_clear_list(&(*cmd_list)->lexer_list);
		if ((*cmd_list)->commands)
			ft_free_arr((*cmd_list)->commands);
		if ((*cmd_list)->input_file)
			free((*cmd_list)->input_file);
		if ((*cmd_list)->output_file)
			free((*cmd_list)->output_file);
		if ((*cmd_list)->heredoc)
			free((*cmd_list)->heredoc);
		if ((*cmd_list))
			free(*cmd_list);
		*cmd_list = NULL;
		*cmd_list = current_cmd;
	}
	return (0);
}

int	ft_is_exit(t_data *data)
{
	t_cmd	*current_cmd;

	current_cmd = data->cmd_list;
	while (current_cmd)
	{
		if (current_cmd && !ft_strncmp(current_cmd->commands[0],
				"exit", ft_strlen("exit")))
		{
			if (current_cmd->prev == NULL && current_cmd->next == NULL)
				return (2);
			else if (current_cmd->next == NULL && current_cmd->prev != NULL)
				return (1);
			else if (current_cmd->next != NULL)
				return (ft_cmd_delete_prev(&data->cmd_list, current_cmd));
		}
		current_cmd = current_cmd->next;
	}
	return (0);
}

void	ft_mini_exit(t_data *data)
{
	t_lexer	*lexer_list;
	int		exit_code;

	exit_code = ft_is_exit(data);
	if (exit_code == 0)
		;
	else if (exit_code == 1)
		ft_error_exit("terminated with exit code: 1\n", data);
	else if (exit_code == 2)
	{
		lexer_list = data->cmd_list->lexer_list;
		// if (ft_strncmp(lexer_list->lexer_comp, "exit", ft_strlen("exit")) != 0)
		// 	ft_error_exit("terminated with exit code: 2\n", data);
		if (ft_lexer_len(lexer_list) > 2)
			ft_error("exit: too many arguments\n", data);
		else if (lexer_list->next
			&& !ft_is_str_digit(lexer_list->next->lexer_comp))
			ft_error_exit_numeric(lexer_list->next->lexer_comp, data);
		if (lexer_list)
			ft_exit_normal(data, lexer_list);
	}
}
