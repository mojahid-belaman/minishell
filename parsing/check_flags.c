#include "../headers/minishell.h"

void check_redir_d(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_dr);
    else if (var->double_q || var->single_q)
    {
        while (var->line[i] == '>')
        {
            var->line[i] = -var->line[i];
            i++;
        }
    }
    else if (!var->double_q && !var->single_q)
        var->redir_double = 1;
}

void check_semicolomn(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double || var->semi_colomn || var->pipe)
        hundel_error(token_sc);
    else if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
    else if (!var->double_q && !var->single_q)
        var->semi_colomn = 1;
}

int count_pip(int i)
{
    t_var *var = get_struc_var(NULL);
    int j = 0;
    while (var->line[i] && var->line[i] == '|')
    {
        j++;
        i++;
    }
    return (j);
}

void check_pipe(int i)
{
    t_var *var = get_struc_var(NULL);
    if ((var->line[0] == '|' && var->line[i + 1] != '|') || count_pip(i) == 3)
        hundel_error(token_pip);
    else if ((var->line[0] == '|' && var->line[i + 1] == '|') || count_pip(i) > 3)
        hundel_error(token_dpip);
    else if (var->pipe && count_pip(i) >=2)
        hundel_error(token_dpip);
    else if ((var->redir_right || var->redir_left || var->redir_double || var->semi_colomn) && count_pip(i) > 1)
        hundel_error(token_dpip);
    else if ((var->redir_right || var->redir_left || var->redir_double || var->semi_colomn) && count_pip(i) == 1)
        hundel_error(token_pip);
    else if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
    else if (!var->double_q && !var->single_q)
        var->pipe = 1;
}

void conv_neg_space(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
}