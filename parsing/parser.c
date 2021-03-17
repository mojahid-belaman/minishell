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
    var->line = NULL;
    var->split_sc = NULL;
    var->split_pip = NULL;
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

void    add_files_tonode(t_parser *prs, t_files *fil)
{
    printf("\nfilename=%s|typeRedir=%c|addressNodefile=%p|addressWholeCmd=%p\n", fil->file_name, fil->type ,fil, prs);
    t_files *curr;
    
    curr = prs->head;
    if (curr == NULL)
        prs->head = fil;
    else
    {
        while (curr->next)
            curr = curr->next;
        curr->next = fil;
    }  
}

void    search_file(int *j, t_parser *prs)
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
           add_files_tonode(prs, fil);
           fil = (t_files *)malloc(sizeof(t_files));
           fil->next = NULL;
       }
   }
}

void    print_list(t_parser *prs)
{
    t_files *curr = prs->head;
    t_parser *curr_prs = prs;
    int i = 0;
    while (curr_prs)
    {
        printf("\ncommand = |%s|\n", prs->cmd);
        while (prs->args[++i])
            printf("\narg[%d] = |%s|\n",i, prs->args[i]);
        while (curr)
        {
            printf("\ntype_redirection = |%c|\n", prs->head->type);
            printf("\nfile_name = |%s|\n", prs->head->file_name);
            curr = curr->next;
        }
        curr_prs = curr_prs->next;
        
    }
}

void    correct_flag_neg(t_parser *prs)
{
    t_files *fil;
    int i;
    int j;
    int k;

    fil = prs->head;
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
    while (prs->args[++i])
    {
        k = -1;
        while (prs->args[i][++k])
        {
            if (prs->args[i][k] < 0)
               prs->args[i][k] = -prs->args[i][k]; 
        }
    }
}

void    search_cmd_args(int *j, t_parser *prs, t_var *var)
{
    var->split_pip[*j] = ft_strtrim(var->split_pip[*j], " ");
    prs->args = ft_split(var->split_pip[*j], ' ');
    correct_flag_neg(prs);
    prs->cmd = prs->args[0];
    print_list(prs);
}

void    add_cmd_node(t_parser *prs, t_var *var)
{
    t_parser *curr;

    curr = var->head;
    curr->next = NULL;
    if (curr == NULL)
        var->head = prs;
    else 
    {
        while (curr->next)
            curr = curr->next;
        curr->next = prs;
    }
}

void    fill_command()
{
    t_var *var = get_struc_var(NULL);
    t_parser *prs = get_struc_prs(NULL);
    int i;
    int j;

    i = -1;
    var->split_sc = ft_split(var->line, ';');
    while (var->split_sc[++i])
    {
        j = -1;
        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {
            prs = (t_parser *)malloc(sizeof(t_parser));
            prs->head = NULL;
            prs->next = NULL;
            search_file(&j, prs);
            search_cmd_args(&j, prs, var);  
        }
    }
}

int main()
{
    int r;
    t_var var;
    t_parser prs;

    r = 1;
    get_struc_var(&var);
    get_struc_prs(&prs);
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
