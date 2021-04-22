#include "../headers/minishell.h"

void	new_str(char **str, int index)
{
	while ((*str)[index] != '\0')
	{
		(*str)[index] = (*str)[index + 1];
		index++;
	}
}

void	del_sq_dq(char **line, int *i, t_var *var)
{
	if ((*line)[*i] == '\"' && var->single_q == 0)
	{
		new_str(line, *i);
		var->double_q = !(var->double_q);
		del_sq_dq(line, i, var);
	}
	if ((*line)[*i] == '\'' && var->double_q == 0)
	{
		new_str(line, *i);
		var->single_q = !(var->single_q);
		del_sq_dq(line, i, var);
	}
}

char	define_type_red(char **line, int *i, char *type)
{
	if ((*line)[*i] == '>' && (*line)[*i - 1] == '>')
		return (*type = 'a');
	else if ((*line)[*i] == '>')
		return (*type = '>');
	else if ((*line)[*i] == '<')
		return (*type = '<');
	return (*type);
}

int	check_empty_dollar(t_var *var, char **line, int *i, char type)
{
	if (!ft_strcmp(var->str_val, "")
		&& (type == 'a' || type == '>' || type == '<'))
	{
		free(var->str_key);
		if (var->i_d != 0)
			(*line)[*i] = token_dollar;
		return (1);
	}
	free(var->str_key);
	return (0);
}
