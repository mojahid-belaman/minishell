#include "../headers/minishell.h"

void    hundel_error(int err)
{
    t_var *var = get_struc_var(NULL);
    
    var->error =  err;
    if (err == token_rl)
        ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
    else if (err == token_rr)
        ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
    else if (err == token_dr)
        ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
    else if (err == token_sc)
        ft_putstr_fd("syntax error near unexpected token `;'\n", 2);
    else if (err == token_pip)
        ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
    else if (err == new_line)
        ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
    else if (err == token_dsc)
        ft_putstr_fd("syntax error near unexpected token `;;'\n", 2);
}
