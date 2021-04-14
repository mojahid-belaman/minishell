#include "../headers/minishell.h"

void init_symbol()
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
    var->exit = 0;
}

void print_list(t_var *var)
{
    t_parser *curr_prs;
    t_files *curr_fils;

    curr_prs = var->prs;
    int i;
    while (curr_prs)
    {
        i = 0;
        curr_fils = curr_prs->file_head;
        printf("\ncommand = |%s|\n", curr_prs->cmd);
        while (curr_prs->args[++i])
            printf("\narg[%d] =  |%s|\n", i, curr_prs->args[i]);
        while (curr_fils)
        {
            printf("\ntype_redirection = |%c|\n", curr_fils->type);
            printf("\nfile_name = |%s|\n", curr_fils->file_name);
            curr_fils = curr_fils->next;
        }
        curr_prs = curr_prs->next_prs;
    }
}

void free_files(t_parser *prs)
{
    t_files *curr = prs->file_head;
    t_files *next_node = NULL;

    while (curr)
    {
        next_node = curr->next;
        if (curr->file_name)
            free(curr->file_name);
        free(curr);
        curr = next_node;
    }
    prs->file_head = NULL;
}

void ft_free_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    if (args)
        free(args);
}

void free_list(t_var *var)
{
    t_parser *curr;

    curr = var->prs;
    while (curr)
    {
        var->prsTail = curr->next_prs;
        if (curr->args)
            ft_free_args(curr->args);
        if (curr->file_head)
            free_files(curr);
        free(curr);
        curr = var->prsTail;
    }
    var->prs = NULL;
}

void ft_free(t_var *var)
{
    int i = -1;
    int j = -1;

    if (var->split_pip)
    {
        while (var->split_pip[++i])
            free(var->split_pip[i]);
        if (var->split_pip)
            free(var->split_pip);
    }
    if (var->split_sc)
    {
        while (var->split_sc[++j])
            free(var->split_sc[j]);
        if (var->split_sc)
            free(var->split_sc);
    }
    if (var->line)
        free(var->line);
    free_list(var);
}

void fill_command(t_var *var)
{
    t_parser *prs = NULL;
    int i;
    int j;

    i = -1;
    var->split_sc = ft_split(var->line, ';');
    var->old_out = dup(STDOUT_FILENO);
    var->old_in = dup(STDIN_FILENO);
    while (var->split_sc[++i])
    {
        clear_line(var, &(var->split_sc[i]));
        if (!var->split_sc[0][0])
            return;
        if (var->error != 0)
            return;
        free_list_cmd(var->prs);
        j = -1;
        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {
            prs = (t_parser *)malloc(sizeof(t_parser));
            prs->file_head = NULL;
            prs->next_prs = NULL;
            add_prs_tonode(var, prs);
            search_file(var, &j);
            search_cmd_args(var, &j);
        }
        // print_list(var);
        execute(var);
        if (var->exit)
            break;
    }
}

int main(int ac, char **av, char **env)
{
    int r;
    int i;
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
        i = -1;
        init_symbol();
        ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
        var->line = read_line(var);
        syntax_error(var, i);
        if (var->error != 0 && !(var->error = 0))
            continue;
        fill_command(var);
        ft_free(var);
    }
    return (0);
}
