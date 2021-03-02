#include "../headers/minishell.h"

void    init_symbol()
{
    t_var *var = getStruct(NULL);

    var->double_q = 0;
    var->single_q = 0;
    var->semi_colomn = 0;
    var->redir_left = 0;
    var->redir_right = 0;
    var->redir_double = 0;
    var->pipe = 0;
    var->back_sl = 0;
    var->line = NULL;
}

t_var *getStruct(t_var *ptr){
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

int main()
{
    int r;
    // char *line;
    t_var var;

    r = 1;
    getStruct(&var);
    while (r)
    {
        init_symbol();
        ft_putstr_fd("\nMinishell~> ", 1);
        get_next_line(0, &var.line);
        syntax_error();
    }

}
