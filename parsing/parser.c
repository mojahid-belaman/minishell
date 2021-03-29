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

void    remove_file(int *i, int org, int *j)
{
    t_var *var = get_struc_var(NULL);
    char *str1;
    char *str2;
    int len;

    len = ft_strlen(var->split_pip[*j]);
    str1 = ft_substr(var->split_pip[*j], *i, len);
    var->split_pip[*j][org] = '\0';
    str2 = var->split_pip[*j];
    var->split_pip[*j] = ft_strjoin(str2, str1);
    *i = org - 1;
}

char    *get_filename(int *i, int *j)
{
    int org;
    int start;
    int end;
    char *tmp;
    t_var *var = get_struc_var(NULL);


    org = *i;
    start = 0;
    end = 0;
    *i += var->step;
    while (var->split_pip[*j][*i] == ' ')
    {
        (*i)++;
        start++;
    }
    while (var->split_pip[*j][*i] != ' ' && var->split_pip[*j][*i] &&
            var->split_pip[*j][*i] != '>' && var->split_pip[*j][*i] != '<')
    {
        (*i)++;   
        end++;
    }
    tmp = ft_substr(var->split_pip[*j], org + var->step + start, end);
    remove_file(i, org, j);
    (*i)--;
    return (tmp);
}

void    add_files_tonode(t_files *fil)
{
    t_var *var = get_struc_var(NULL);
    printf("\nfilename=%s|typeRedir=%c|addressNodefile=%p|addressWholeCmd=%p\n", fil->file_name, fil->type ,fil, var->prsTail);
    t_files *curr;
    
    curr = var->prsTail->file_head;
    if (!curr)
        var->prsTail->file_head = fil;
    else
    {
        while (curr->next)
            curr = curr->next;
        curr->next = fil;
    }  
}

void    search_file(int *j)
{
   t_var *var = get_struc_var(NULL);
   t_files *fil;
   int i;

   i = -1;
   fil = (t_files *)malloc(sizeof(t_files));
   fil->next = NULL;
   while (var->split_pip[*j][++i])
   {
       fil->type = '1';
       if (var->split_pip[*j][i] == '>' && var->split_pip[*j][i + 1] == '>')
       {
           fil->type = append;
           var->step = 2;
           fil->file_name = get_filename(&i, j);
       }
       else if (var->split_pip[*j][i] == '>')
       {
           fil->type = right_r;
           var->step = 1;
           fil->file_name = get_filename(&i, j);
       }
       else if (var->split_pip[*j][i] == '<')
       {
           fil->type = left_r;
           var->step = 1;
           fil->file_name = get_filename(&i, j);

       }
       if (fil->type != '1')
       {
           add_files_tonode(fil);
           fil = (t_files *)malloc(sizeof(t_files));
           fil->next = NULL;
       }
   }
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

void    correct_flag_neg()
{
    t_var *var = get_struc_var(NULL);

    t_files *fil;
    int i;
    int j;
    int k;

    fil = var->prsTail->file_head;
    i = -1;
    while (fil)
    {
        j = -1;
        while (fil->file_name[++j])
        {
            if (fil->file_name[j] < 0)
                fil->file_name[j] = -fil->file_name[j];
        }
        fil = fil->next;
    }
    while (var->prsTail->args[++i])
    {
        k = -1;
        while (var->prsTail->args[i][++k])
        {
            if (var->prsTail->args[i][k] < 0)
               var->prsTail->args[i][k] = -var->prsTail->args[i][k]; 
        }
    }
}

void    search_cmd_args(int *j)
{
    t_var *var = get_struc_var(NULL);
    t_parser *node; 

    node = var->prsTail;
    var->split_pip[*j] = ft_strtrim(var->split_pip[*j], " ");
    node->args = ft_split(var->split_pip[*j], ' ');
    correct_flag_neg();
    node->cmd = node->args[0];
}

void	count_node_file()
{
    t_var *var = get_struc_var(NULL);
    t_files *curr;
	int cpt;

	cpt = 0;
    curr = var->prsTail->file_head;
	if (!curr)
		printf("\n%d\n", cpt);
	while (curr)
	{
		cpt++;
		curr = curr->next;
	}
	printf("\ncount files in one node=%d\n", cpt);
}

void	count_node_cmd()
{
    t_var *var = get_struc_var(NULL);

    t_parser *curr;
	int cpt;

	cpt = 0;
    curr = var->prs;
	if (!curr)
		printf("\n%d\n", cpt);
	while (curr)
	{
		cpt++;
		curr = curr->next_prs;
	}
	printf("\ncount big prs node=%d\n", cpt);
}

void createCmdsList(t_parser *node){
     t_var *var = get_struc_var(NULL);

     if (!var->prs){
        var->prs = node;
        var->prsTail = node; 
     }  
    else {
         var->prsTail->next_prs = node;
         var->prsTail =  node;
    }
}

void new_str(char **str, int index)
{
    while ((*str)[index] != '\0')
    {
        (*str)[index] = (*str)[index + 1];
        index++;
    }
}

void    del_sq_dq(char **line, int *i, int *sq, int *dq)
{
    if ((*line)[*i] == '\"' && *sq == 0)
    {
        new_str(line, *i);
        *dq = !(*dq);
        del_sq_dq(line, i, sq, dq);
    }
    if ((*line)[*i] == '\'' && *dq == 0)
    {
        new_str(line, *i);
        *sq = !(*sq);
        del_sq_dq(line, i, sq, dq);
    }
}

// void    replace_dollar(char **line, int *i)
// {

// }

void clear_line(char **line)
{
    int i = -1;
    int dq = 0;
    int sq = 0;
    
    while ((*line)[++i] != '\0')
    {
       del_sq_dq(line, &i, &sq, &dq);
    //    replace_dollar(line, &i);
       if (dq && (*line)[i] == '\\' && ((*line)[i + 1] == '$' || (*line)[i + 1] == '\"' || (*line)[i + 1] == '\\'))
            new_str(line, i);
        if ((dq || sq) && (*line)[i] > 0)
            (*line)[i] = -(*line)[i];
    }
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

void    fill_command()
{
    t_var *var = get_struc_var(NULL);
    t_parser *prs = NULL;
    int i;
    int j;

    i = -1;
    // var->prs = (t_parser *)malloc(sizeof(t_parser));
    // var->prs->next_prs = NULL;
    var->split_sc = ft_split(var->line, ';');
    while (var->split_sc[++i])
    {
        clear_line(&(var->split_sc[i]));
        free_list_cmd(var->prs);
        j = -1;
        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {
            prs = (t_parser *)malloc(sizeof(t_parser));
            prs->file_head = NULL;
            prs->next_prs = NULL;
            createCmdsList(prs);
            search_file(&j);
            search_cmd_args(&j);
            // print_list();
        }
        execute();
        // count_node_cmd();
        // count_node_file();
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

void    recycle_line()
{
    t_var *var = get_struc_var(NULL);

    int i;

    i = -1;
    while (var->line[++i])
    {
        if (var->line[i] == '>' || var->line[i] == '<')
            var->line[i] = -var->line[i];
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
    // print_list_env(var->head_env);
    while (r)
    {
        init_symbol();
        ft_putstr_fd("\033[1;45m$minishell$~> \033[0m", 1);
        get_next_line(0, &var->line);
        syntax_error();
        // recycle_line();
        if (var->error != 0 && !(var->error = 0))
            continue ;
        fill_command();
        // exit(0);
    }

    return (0);
}
