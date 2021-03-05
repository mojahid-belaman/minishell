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
    var->prs->split_sc = NULL;
}

t_var *getStruct(t_var *ptr){
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}


int main(int argc, char **argv, char **envp)
{
    int r;
    t_var var;
    int i;
    int j;


    i = -1;
    j = -1;
    r = 1;
    getStruct(&var);
    while (r)
    {
        init_symbol();
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
        get_next_line(0, &var.line);
        syntax_error();
        var.prs = (t_parser *)malloc(sizeof(t_parser));
        var.prs->split_sc = ft_split(var.line, ';');
        i = -1;
        while (var.prs->split_sc[++i])
        {
            var.prs->split_sc[i] = ft_strtrim(var.prs->split_sc[i], " ");
            printf("--%s--\n", var.prs->split_sc[i]);
            var.prs->split_pip = ft_split(var.prs->split_sc[i], '|');
            j = -1;
            while (var.prs->split_pip[++j])
            {
                var.prs->split_pip[j] = ft_strtrim(var.prs->split_pip[j], " ");
                printf("%s\n", var.prs->split_pip[j]);
            }
            
        }
        
    }

}
