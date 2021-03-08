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
    var->split_sc = NULL;
    var->split_pip = NULL;
}

t_var *getStruct(t_var *ptr){
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

void    fill_command()
{
    t_var *var = getStruct(NULL);
    int i;

    i = -1;
    var->split_sc = ft_split(var->line, ';');
    while (var->split_sc[++i])
    {
        
    }
    

}

int main()
{
    int r;
    t_var var;

    r = 1;
    getStruct(&var);
    while (r)
    {
        init_symbol();
		ft_putstr_fd("\033[1;43m$minishell$~> \033[0m", 1);
        get_next_line(0, &var.line);
        syntax_error();
        if (var.error != 0 && !(var.error = 0))
            continue ;
        fill_command();
    }

}
