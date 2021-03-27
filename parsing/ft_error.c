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

void    free_list_files(t_parser *prs)
{
    t_files *curr = prs->file_head;
    t_files *next_node = NULL;

    while (curr)
    {
        next_node = curr->next;
        free(curr);
        curr = NULL;
        curr = next_node;
    }
    prs->file_head = NULL;
}

void    free_list_cmd(t_parser *prs)
{
    t_var *var = get_struc_var(NULL);
    t_parser *curr;

    curr = prs;
    while (curr)
    {
        var->prsTail = curr->next_prs;
        free_list_files(curr);
        free(curr);
        curr = NULL;
        curr = var->prsTail;
    }
    var->prs = NULL;
}
