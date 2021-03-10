#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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

void    search_file(char **str)
{
    t_files *fls = get_struct_file(NULL);
    int i;

    i = -1;
    fls = (t_files *)malloc(sizeof(t_files));
    fls->next = NULL;
    while ((*str)[++i])
    {
        
    }
    

}

void    fill_command()
{
    t_var *var = getStruct(NULL);
    int i;
    int j;


    i = -1;
    var->prs = (t_parser *)malloc(sizeof(t_parser));
    var->prs->next = NULL;
    var->split_sc = ft_split(var->line, ';');
    while (var->split_sc[++i])
    {
        j = -1;
        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {   
            search_file(&var->split_pip[j]);
        }
        
    }
    

}

// int main()
// {
//     int r;
//     t_var var;

//     r = 1;
//     getStruct(&var);
//     while (r)
//     {
//         init_symbol();
// 		ft_putstr_fd("\033[1;43m$minishell$~> \033[0m", 1);
//         get_next_line(0, &var.line);
//         syntax_error();
//         if (var.error != 0 && !(var.error = 0))
//             continue ;
//         fill_command();
//     }

// }
