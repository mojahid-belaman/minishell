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
		free_list_cmd(var->prs, var);
		j = -1;
		var->split_pip = ft_split(var->split_sc[i], '|');
		while (var->split_pip[++j])
			ft_subcmd(prs, var, &j);
		(void)env;
		print_list(var);
		execution(var, env);
		if (var->exit)
			break ;
	}
}

void	ft_newline(t_var *var, char *tmp)
{
	read_line(var);
	tmp = var->line;
	var->line = ft_strtrim(var->line, " ");
	free(tmp);
}

int	main(int ac, char **av, char **env)
{
	t_var	var;
	int		i;
	char	*tmp;

	ac = 1;
	av = NULL;
	tmp = NULL;
	get_env(env, &var);
	var.home = find_value("HOME", &var);
	g_var = &var;
	signal(SIGINT, signal_handler_c);
	signal(SIGQUIT, signal_handler_quit);
	while (1)
	{
		i = -1;
		init_symbol(&var);
		ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
		ft_newline(&var, tmp);
		syntax_error(&var, i);
		if (var.error != 0)
		{
			var.error = 0;
			continue ;
		}
		fill_command(&var, env);
		ft_free(&var);
	}
	return (0);
}
