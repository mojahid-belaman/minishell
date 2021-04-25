#include "../headers/minishell.h"

void	init_symbol(t_var *var)
{
	var->double_q = 0;
	var->single_q = 0;
	var->semi_colomn = 0;
	var->redir_left = 0;
	var->redir_right = 0;
	var->redir_double = 0;
	var->pipe = 0;
	var->back_sl = 0;
	var->error = 0;
	var->step = 0;
	var->line = NULL;
	var->split_sc = NULL;
	var->split_pip = NULL;
	var->prs = NULL;
	var->prsTail = NULL;
	var->exit = 0;
}

void	free_files(t_parser *prs)
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
		curr = next_node;
	}
	prs->file_head = NULL;
}

void	print_list(t_var *var)
{
	t_parser	*curr_prs;
	t_files		*curr_fils;
	int			i;

	curr_prs = var->prs;
	while (curr_prs)
	{
		i = 0;
		curr_fils = curr_prs->file_head;
		printf("\ncommand = |%s|\n", curr_prs->cmd);
		while (curr_prs->args[++i])
			printf("\narg[%d] =  |%s|\n", i, curr_prs->args[i]);
		while (curr_fils)
		{
			printf("\ntype_redirection = |%c|\n", curr_fils->type);
			printf("\nfile_name = |%s|\n", curr_fils->file_name);
			curr_fils = curr_fils->next;
		}
		curr_prs = curr_prs->next_prs;
	}
}

void	ft_free_args(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		free(args[i]);
		args[i] = NULL;
	}
	if (args)
		free(args);
	args = NULL;
}

void	free_list(t_var *var)
{
	t_parser	*curr;

	curr = var->prs;
	while (curr)
	{
		var->prsTail = curr->next_prs;
		if (curr->args)
			ft_free_args(curr->args);
		curr->args = NULL;
		if (curr->file_head)
			free_files(curr);
		free(curr);
		curr = var->prsTail;
	}
	var->prs = NULL;
}

void	ft_free(t_var *var)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (var->split_pip)
	{
		while (var->split_pip[++i])
			free(var->split_pip[i]);
		if (var->split_pip)
			free(var->split_pip);
	}
	if (var->split_sc)
	{
		while (var->split_sc[++j])
			free(var->split_sc[j]);
		if (var->split_sc)
			free(var->split_sc);
	}
	if (var->line)
		free(var->line);
	free_list(var);
}

void	ft_subcmd(t_parser *prs, t_var *var, int *j)
{
	prs = (t_parser *)malloc(sizeof(t_parser));
	prs->file_head = NULL;
	prs->next_prs = NULL;
	add_prs_tonode(var, prs);
	search_file(var, j);
	search_cmd_args(var, j);
}

void	fill_command(t_var *var, char **env)
{
	t_parser	*prs;
	int			i;
	int			j;

	prs = NULL;
	i = -1;
	var->split_sc = ft_split(var->line, ';');
	var->old_out = dup(STDOUT_FILENO);
	var->old_in = dup(STDIN_FILENO);
	while (var->split_sc[++i])
	{
		clear_line(var, &(var->split_sc[i]));
		// printf("{%s}\n", var->split_sc[i]);
		free_list_cmd(var->prs, var);
		j = -1;
		var->split_pip = ft_split(var->split_sc[i], '|');
		while (var->split_pip[++j])
			ft_subcmd(prs, var, &j);
		// (void)env;
		// print_list(var);
		execution(var, env);
		if (var->exit)
			break ;
	}
}

int	main(int ac, char **av, char **env)
{
	t_var	var;
	int		i;
	char	*tmp;

	ac = 1;
	av = NULL;
	get_env(env, &var);
	var.home = find_value("HOME", &var);
	while (1)
	{
		i = -1;
		init_symbol(&var);
		ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
		read_line(&var);
		tmp = var.line;
		var.line = ft_strtrim(var.line, " ");
		free(tmp);
		syntax_error(&var, i);
		if (var.error != 0 && !(var.error = 0))
			continue ;
		fill_command(&var, env);
		ft_free(&var);
	}
	return (0);
}
