#include "../headers/minishell.h"

void    hundel_error(int err)
{
    t_var *var = getStruct(NULL);
    
    var->error =  err;
    if (err == token_rl)
        ft_putstr_fd("syntax error near unexpected token `<'", 2);
    else if (err == token_rr)
        ft_putstr_fd("syntax error near unexpected token `>'", 2);
    else if (err == token_dr)
        ft_putstr_fd("syntax error near unexpected token `>>'", 2);
    else if (err == token_sc)
        ft_putstr_fd("syntax error near unexpected token `;'", 2);
    else if (err == token_pip)
        ft_putstr_fd("syntax error near unexpected token `|'", 2);
}
