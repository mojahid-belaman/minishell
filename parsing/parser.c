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
    
    curr = var->prsTail->head;
    if (!curr)
        var->prsTail->head = fil;
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

void    print_list(t_parser *prs)
{
    t_files *curr_fils = prs->head;
    t_parser *curr_prs = prs;
    int i = 0;
    while (curr_prs)
    {
        printf("\ncommand = |%s|\n", prs->cmd);
        while (prs->args[++i])
            printf("\narg[%d] = |%s|\n",i, prs->args[i]);
        while (curr_fils)
        {
            printf("\ntype_redirection = |%c|\n", prs->head->type);
            printf("\nfile_name = |%s|\n", prs->head->file_name);
            curr_fils = curr_fils->next;
        }
        curr_prs = curr_prs->next;
        
    }
}

void    correct_flag_neg()
{
    t_var *var = get_struc_var(NULL);

    t_files *fil;
    int i;
    int j;
    int k;

    fil = var->prsTail->head;
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
    print_list(node);
}

// void    add_cmd_node(t_parser *prs, t_var *var)
// {
//     t_parser *curr;

//     curr = var->prs;
//     curr->next = NULL;
//     if (curr == NULL)
//         var->prs = prs;
//     else 
//     {
//         while (curr->next)
//             curr = curr->next;
//         curr->next = prs;
//     }
// }
void	count_node_file()
{
    t_var *var = get_struc_var(NULL);


    t_files *curr;
	int cpt;

	cpt = 0;
    curr = var->prsTail->head;
	if (!curr)
		printf("\n%d\n", cpt);
	while (curr)
	{
		cpt++;
		curr = curr->next;
	}
	printf("\n%d\n", cpt);
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
		curr = curr->next;
	}
	printf("\n%d\n", cpt);
}

// void    clear_line(char **line)
// {
//     int i;

//     i = -1;
//     while ((*line)[++i] != '\0')
//     {
        
//     }
    
// }

void createCmdsList(t_parser *node){
     t_var *var = get_struc_var(NULL);

     if (!var->prs){
        var->prs = node;
        var->prsTail = node; 
     }  
    else {
         var->prsTail->next = node;
         var->prsTail =  node;
    }
}

void    clear_line(char **line)
{
    int i;
    int sq;
    int dq;

    i = -1;
    dq = 0;
    sq = 0;
    while ((*line)[++i] != '\0')
    {  

    }
}

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
        j = -1;
        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {
            prs = (t_parser *)malloc(sizeof(t_parser));
            prs->head = NULL;
            prs->next = NULL;
            createCmdsList(prs);
            search_file(&j);
            search_cmd_args(&j);
            // add_cmd_node(var->prs, var);
            // print_list(var->prs);
            // count_node_file();
        }
        // count_node_cmd();
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
