#include "../headers/minishell.h"

void    check_single_q()
{
    t_var *var = get_struc_var(NULL);

    if (var->single_q)
        var->single_q = 0;
    else if (!var->double_q && !var->single_q)
        var->single_q = 1;
}

void    check_double_q()
{
    t_var *var = get_struc_var(NULL);
   if (var->double_q)
        var->double_q = 0;
    else if (var->semi_colomn)
        var->semi_colomn = 0;
    else if (!var->double_q && !var->single_q)
        var->double_q = 1;
}

void    check_redir_r()
{
     t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_rr);
    if (!var->double_q && !var->single_q)
        var->redir_right = 1;

}

void    check_redir_l()
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_rl);
    if (!var->double_q && !var->single_q)
        var->redir_left = 1;
}
void    check_redir_d()
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_dr);
    else if (!var->double_q && !var->single_q)
        var->redir_double = 1;
}
void    check_semicolomn(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double || var->semi_colomn || var->pipe)
        hundel_error(token_sc);
    else if (var->double_q || var->single_q)
        var->line[i] *= -1;
    else if (!var->double_q && !var->single_q)
        var->semi_colomn = 1;
}

void    check_pipe()
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double || var->pipe || var->semi_colomn)
        hundel_error(token_pip);
    else if (!var->double_q && !var->single_q)
        var->pipe = 1;
}