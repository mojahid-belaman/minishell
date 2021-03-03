#include "../headers/minishell.h"

int	isprint_car(int p)
{
	if (p <= 32 || p >= 127)
		return (0);
	return (1);
}

void    check_allflgs()
{
    t_var *var = getStruct(NULL);

    if (var->semi_colomn || var->redir_left || var->redir_right
        || var->redir_double || var->pipe || var->double_q || var->single_q)
        ft_putstr_fd("minishell: syntax error", 2);
    else
        ft_putstr_fd("line is clean!", 1);
    
}

void    check_carac(char c)
{
    t_var *var = getStruct(NULL);

    if ((var->semi_colomn || var->redir_left || var->redir_right
        || var->redir_double || var->pipe) && isprint_car(c))
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
    t_var *var = getStruct(NULL);
    if (var->redir_right || var->redir_left || var->redir_double || var->semi_colomn || var->pipe)
        hundel_error(token_sc);
    while (var->line[++i])
        if (isprint_car(var->line[i]))
            return (1);
    return (0);
}

void    syntax_error()
{
    t_var *var = getStruct(NULL);
    int i;

    i = -1;
    while (var->line[++i])
    {
        if (var->line[i] == '\'')
            check_single_q();
        else if (var->line[i] == '"')
            check_double_q();
        else if (var->line[i] == ';')
        {
            if (hund_last_sc(i))
                check_semicolomn(i);
        }
        else if (var->line[i] == '>' && var->line[i + 1] == '>')
        {
            i++;
            check_redir_d(&i);
        }
        else if (var->line[i] == '>')
            check_redir_r();
        else if (var->line[i] == '<')
            check_redir_l();
        else if (var->line[i] == '|')
            check_pipe();
        else
        {
            check_carac(var->line[i]);
        }
        
        if (var->error != 0 && !(var->error = 0))
            return ;
    }
    check_allflgs();
}
