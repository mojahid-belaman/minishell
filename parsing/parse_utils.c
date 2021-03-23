#include "../headers/minishell.h"

int	isprint_car(int p)
{
	if (p <= 32 || p >= 127)
		return (0);
	return (1);
}

void    check_allflgs()
{
    t_var *var = get_struc_var(NULL);

    if (var->semi_colomn)
        hundel_error(token_dsc);
    else if (var->semi_colomn || var->redir_left || var->redir_right
        || var->redir_double || var->pipe || var->double_q || var->single_q)
        {
         
        hundel_error(new_line);
        }
}

void    check_carac(char c)
{
    t_var *var = get_struc_var(NULL);

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
    t_var *var = get_struc_var(NULL);
    if (var->redir_right || var->redir_left || var->redir_double
        || var->semi_colomn || var->pipe)
        hundel_error(token_sc);
    while (var->line[++i])
        if (isprint_car(var->line[i]) || var->line[i] != '"')
            return (1);
    return (0);
}

void    syntax_error()
{
    t_var *var = get_struc_var(NULL);
    int i;

    i = -1;
    var->line = ft_strtrim(var->line, " ");
    while (var->line[++i])
    {
        if (var->line[i] == '\\' && !var->single_q)
        {
            // var->line[i] *= -1;
            i++;
        }
        else if (var->line[i] == '\'')
            check_single_q();
        else if (var->line[i] == '"')
            check_double_q();
        else if (var->line[i] == ';')
        {
            if (var->line[0] == ';' && var->line[i + 1] != ';')
                hundel_error(token_sc);
            else if (var->line[i + 1] == ';')
                hundel_error(token_dsc);
            else if (hund_last_sc(i))
                check_semicolomn(i);
        }
        else if (var->line[i] == '>' && var->line[i + 1] == '>')
        {
            check_redir_d(i);
            i += 1;
        }
        else if (var->line[i] == '>')
            check_redir_r(i);
        else if (var->line[i] == '<')
            check_redir_l(i);
        else if (var->line[i] == '|')
            check_pipe(i);
        else if (var->line[i] == ' ')
            conv_neg_space(i);
        else
            //function check is they flags active and after is caractere if true shut down flags
            check_carac(var->line[i]);
        //function check if before function open error set this var and close from func
        if (var->error != 0)
            return ;
    }
    check_allflgs();
}
