#include "../headers/minishell.h"

void    off_redir()
{
    t_var *var =  get_struc_var(NULL);
    if (var->redir_left || var->redir_right || var->redir_double)
    {
       var->redir_left = 0; 
       var->redir_right = 0; 
       var->redir_double = 0; 
    }
    else if (var->semi_colomn)
        var->semi_colomn = 0;
}
void    check_single_q()
{
    t_var *var = get_struc_var(NULL);
    off_redir();
    if (var->single_q)
        var->single_q = 0;
    else if (!var->double_q && !var->single_q)
        var->single_q = 1;
    if (var->semi_colomn)
        var->semi_colomn = 0;
}

void    check_double_q()
{
    t_var *var = get_struc_var(NULL);
    off_redir();
   if (var->double_q)
        var->double_q = 0;
    // else if (var->semi_colomn)
    //     var->semi_colomn = 0;
    else if (!var->double_q && !var->single_q)
        var->double_q = 1;
}

void    check_redir_r(int i)
{
     t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_rr);
    else if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
    else if (!var->double_q && !var->single_q)
        var->redir_right = 1;

}

void    check_redir_l(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_left)
        hundel_error(new_line);
    else if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_rl);
    else if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
    else if (!var->double_q && !var->single_q)
        var->redir_left = 1;
}
void    check_redir_d(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double)
        hundel_error(token_dr);
    // condition check double redirection which is d_quote or s_quote
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

void    check_semicolomn(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double || var->semi_colomn || var->pipe)
        hundel_error(token_sc);
    else if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
    else if (!var->double_q && !var->single_q)
        var->semi_colomn = 1;
}

void    check_pipe(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->redir_right || var->redir_left || var->redir_double || var->pipe || var->semi_colomn)
        hundel_error(token_pip);
    else if (var->double_q || var->single_q)
        var->line[i] = -var->line[i];
    else if (!var->double_q && !var->single_q)
        var->pipe = 1;
}

void    conv_neg_space(int i)
{
    t_var *var = get_struc_var(NULL);

    if (var->double_q || var->single_q)
        var->line[i] = -var->line[i]; 
}