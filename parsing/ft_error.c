#include "../headers/minishell.h"

void	hundel_error(int err, t_var *var)
{
	var->error = err;
	var->status = 258;
	free(var->line);
	var->line = NULL;
	if (err == token_rl)
		ft_putstr_fd("minishell:syntax error near unexpected token `<'\n", 2);
	else if (err == token_rr)
		ft_putstr_fd("minishell:syntax error near unexpected token `>'\n", 2);
	else if (err == token_dr)
		ft_putstr_fd("minishell:syntax error near unexpected token `>>'\n", 2);
	else if (err == token_sc)
		ft_putstr_fd("minishell:syntax error near unexpected token `;'\n", 2);
	else if (err == token_pip)
		ft_putstr_fd("minishell:syntax error near unexpected token `|'\n", 2);
	else if (err == token_dpip)
		ft_putstr_fd("minishell:syntax error near unexpected token `||'\n", 2);
	else if (err == new_line)
	{
		ft_putstr_fd("minishell:syntax error near unexpected ", 2);
		ft_putstr_fd("token `newline'\n", 2);
	}
	else if (err == token_dsc)
		ft_putstr_fd("minishell:syntax error near unexpected token `;;'\n", 2);
}

void	free_list_files(t_parser *prs)
{
	t_files	*curr;
	t_files	*next_node;

	curr = prs->file_head;
	next_node = NULL;
	while (curr)
	{
		next_node = curr->next;
		if (curr->file_name)
			free(curr->file_name);
		free(curr);
		curr = NULL;
		curr = next_node;
	}
	prs->file_head = NULL;
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	if (args)
		free(args);
}

void	free_list_cmd(t_parser *prs, t_var *var)
{
	t_parser	*curr;
	int			i;

	i = -1;
	curr = prs;
	if (var->split_pip)
	{
		while (var->split_pip[++i])
			free(var->split_pip[i]);
		free(var->split_pip);
	}
	while (curr)
	{
		var->prsTail = curr->next_prs;
		free_args(curr->args);
		free_list_files(curr);
		free(curr);
		curr = NULL;
		curr = var->prsTail;
	}
	var->prs = NULL;
}
