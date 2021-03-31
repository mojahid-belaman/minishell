#include "../headers/minishell.h"

void check_allflgs()
{
	t_var *var = get_struc_var(NULL);

	if (var->semi_colomn)
		hundel_error(token_dsc);
	else if (var->semi_colomn || var->redir_left || var->redir_right || var->redir_double || var->pipe || var->double_q || var->single_q)
		hundel_error(new_line);
}

void check_carac(char c)
{
	t_var *var = get_struc_var(NULL);

	if ((var->semi_colomn || var->redir_left || var->redir_right || var->redir_double || var->pipe) && isprint_car(c))
	{
		var->semi_colomn = 0;
		var->redir_left = 0;
		var->redir_right = 0;
		var->redir_double = 0;
		var->pipe = 0;
	}
}

int hund_last_sc(int i)
{
	t_var *var = get_struc_var(NULL);
	if (var->redir_right || var->redir_left || var->redir_double || var->semi_colomn || var->pipe)
		hundel_error(token_sc);
	while (var->line[++i])
		if (isprint_car(var->line[i]) || var->line[i] != '"')
			return (1);
	return (0);
}

void hundel_semicolomne(t_var *var, int i)
{

	if (var->line[0] == ';' && var->line[i + 1] != ';')
		hundel_error(token_sc);
	else if (var->line[i + 1] == ';')
		hundel_error(token_dsc);
	else if (hund_last_sc(i))
		check_semicolomn(i);
}

void off_flags_covneg(t_var *var, int *i)
{
	if (var->redir_right || var->redir_left || var->redir_double || var->semi_colomn)
	{
		var->redir_right = 0;
		var->redir_left = 0;
		var->redir_double = 0;
		var->semi_colomn = 0;
	}
	var->line[*i + 1] = -var->line[*i + 1];
	(*i)++;
}

int hundel_backsl_two(t_var *var, int *i)
{
	if (!var->double_q && var->line[*i] == '\\' &&
		(var->line[*i + 1] == ';' || var->line[*i + 1] == '|' || var->line[*i + 1] == ' ' || var->line[*i + 1] == '>' || var->line[*i + 1] == '<'))
	{
		off_flags_covneg(var, i);
		return (1);
	}
	else if (var->double_q && var->line[*i] == '\\' && (var->line[*i + 1] == ';'))
	{
		var->line[*i + 1] = -var->line[*i + 1];
		return (1);
	}
	else if (var->line[*i] == '\\' && !var->single_q)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

int hundel_backsl_one(t_var *var, int *i)
{
	if (!var->single_q && var->line[*i] == '\\' && var->line[*i + 1] == '`')
	{
		(*i)++;
		return (1);
	}
	else if (!var->single_q && var->line[*i] == '`')
	{
		hundel_error(new_line);
		return (1);
	}
	else if (var->line[*i] == '\\' && !var->line[*i + 1])
	{
		hundel_error(new_line);
		return (1);
	}
	else if (hundel_backsl_two(var, i))
		return (1);
	return (0);
}

int hundel_all_redir(t_var *var, int *i)
{
	if (var->line[*i] == '>' && var->line[*i + 1] == '>')
	{
		check_redir_d(*i);
		*i += 1;
		return (1);
	}
	else if (var->line[*i] == '>')
	{
		check_redir_r(*i);
		return (1);
	}
	else if (var->line[*i] == '<')
	{
		check_redir_l(*i);
		return (1);
	}
	return (0);
}

int hundel_sq_dq_sm(t_var *var, int i)
{
	if (var->line[i] == '\'')
	{
		check_single_q();
		return (1);
	}
	else if (var->line[i] == '"')
	{
		check_double_q();
		return (1);
	}
	else if (var->line[i] == ';')
	{
		hundel_semicolomne(var, i);
		return (1);
	}
	return (0);
}

int hundel_pip_sp(t_var *var, int i)
{
	if (var->line[i] == '|')
	{
		check_pipe(i);
		return (1);
	}
	else if (var->line[i] == ' ')
	{
		conv_neg_space(i);
		return (1);
	}
	else
	{
		check_carac(var->line[i]);
		return (1);
	}
	return (0);
}

void syntax_error(t_var *var, int i)
{
	var->line = ft_strtrim(var->line, " ");
	while (var->line[++i])
	{
		if (hundel_backsl_one(var, &i))
		{
			if (var->error != 0)
				return;
		}
		else if (hundel_sq_dq_sm(var, i))
		{
			if (var->error != 0)
				return;
		}
		else if (hundel_all_redir(var, &i))
		{
			if (var->error != 0)
				return;
		}
		else if (hundel_pip_sp(var, i))
		{
			if (var->error != 0)
				return;
		}
	}
	check_allflgs();
}
