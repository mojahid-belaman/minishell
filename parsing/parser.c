#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../headers/minishell.h"

void    init_symbol()
{
    t_var *var = get_struc_var(NULL);
    var->double_q = 0;
    var->single_q = 0;
    var->semi_colomn = 0;
    var->redir_left = 0;
    var->redir_right = 0;
    var->redir_double = 0;
    var->pipe = 0;
    var->back_sl = 0;
    var->error = 0;
    var->step = 0;
    var->line = NULL;
    var->split_sc = NULL;
    var->split_pip = NULL;
    var->prs = NULL;
    var->prsTail = NULL;
}

void    print_list()
{
    t_var *var = get_struc_var(NULL);
    t_parser *curr_prs;
    t_files *curr_fils;

    curr_prs = var->prs;
    curr_fils = var->prs->file_head;
    int i = 0;
    while (curr_prs)
    {
        printf("\ncommand = |%s|\n", curr_prs->cmd);
        while (curr_prs->args[++i])
            printf("\narg[%d] = |%s|\n",i, curr_prs->args[i]);
        while (curr_fils)
        {
            printf("\ntype_redirection = |%c|\n", curr_fils->type);
            printf("\nfile_name = |%s|\n", curr_fils->file_name);
            curr_fils = curr_fils->next;
        }
        curr_prs = curr_prs->next_prs;  
    }
}


// void	count_node_file()
// {
//     t_var *var = get_struc_var(NULL);
//     t_files *curr;
// 	int cpt;

// 	cpt = 0;
//     curr = var->prsTail->file_head;
// 	if (!curr)
// 		printf("\n%d\n", cpt);
// 	while (curr)
// 	{
// 		cpt++;
// 		curr = curr->next;
// 	}
// 	printf("\ncount files in one node=%d\n", cpt);
// }

// void	count_node_cmd()
// {
//     t_var *var = get_struc_var(NULL);

//     t_parser *curr;
// 	int cpt;

// 	cpt = 0;
//     curr = var->prs;
// 	if (!curr)
// 		printf("\n%d\n", cpt);
// 	while (curr)
// 	{
// 		cpt++;
// 		curr = curr->next_prs;
// 	}
// 	printf("\ncount big prs node=%d\n", cpt);
// }

void    fill_command()
{
    t_var *var = get_struc_var(NULL);
    t_parser *prs = NULL;
    int i;
    int j;

    i = -1;
    var->split_sc = ft_split(var->line, ';');
    while (var->split_sc[++i])
    {
        clear_line(&(var->split_sc[i]));
        if (var->error != 0 )
            return ;
        free_list_cmd(var->prs);
        j = -1;
        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {
            prs = (t_parser *)malloc(sizeof(t_parser));
            prs->file_head = NULL;
            prs->next_prs = NULL;
            add_prs_tonode(prs);
            search_file(&j);
            search_cmd_args(&j);
            print_list();
        }
        execute();
    }
}

// void    print_list_env(t_env *head)
// {
//     t_env *curr;

//     curr = head;
//     while (curr)
//     {
//         printf("|%s||%s|\n", curr->key, curr->value);
//         curr = curr->next;
//     }
    
// }

void    verify_bs_with_split()
{
    t_var *var = get_struc_var(NULL);
    int i = -1;
    while (var->line[++i])
    {
        if (var->line[i] == '\\' && (var->line[i + 1] == ';'))
            var->line[i + 1] = -var->line[i + 1];
    }
}

int main(int ac, char **av, char **env)
{
    int r;
    t_var *var;

    r = 1;
    ac = 1;
    av = NULL;
    var = (t_var *)malloc(sizeof(t_var));
    get_struc_var(var);
    get_env(env);
    var->home = find_value("HOME");
    while (r)
    {
        init_symbol();
        ft_putstr_fd("\033[1;45m$minishell$~> \033[0m", 1);
        get_next_line(0, &var->line);
        syntax_error();
        verify_bs_with_split();
        if (var->error != 0 && !(var->error = 0))
            continue ;
        fill_command();
    }
    return (0);
}
