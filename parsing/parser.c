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

char    *get_filename(int *i)
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
    while ((*var->split_pip)[*i] == ' ')
    {
        (*i)++;
        start++;
    }
    while ((*var->split_pip)[*i] != ' ' && (*var->split_pip)[*i] != '>'
            && (*var->split_pip)[*i] != '<' && (*var->split_pip)[*i])
    {
        (*i)++;
        end++;
    }
    tmp = ft_substr(*var->split_pip, org + var->step + start, end);
    return (tmp);
}

void    add_files_tonode(t_parser *prs, t_files *fil)
{
    t_files *curr;
    
    curr = prs->file;
    if (curr == NULL)
        prs->file = fil;
    else
    {
        while (curr->next)
            curr = curr->next;
        curr->next = fil;
    }
    
}

void    search_file()
{
   t_var *var = get_struc_var(NULL);
   t_parser *prs = get_struc_prs(NULL);
   t_files *fls =  get_struc_fils(NULL);
   int i;

   i = -1;
   fls = (t_files *)malloc(sizeof(t_files));
   fls->next = NULL;
   while ((*var->split_pip)[++i])
   {
       fls->type = '1';
       if ((*var->split_pip)[i] == '>')
       {
           fls->type = right_r;
           var->step = 1;
           fls->file_name = get_filename(&i);
       }
       else if ((*var->split_pip)[i] == '<')
       {
           fls->type = left_r;
           var->step = 1;
           fls->file_name = get_filename(&i);

       }
       else if ((*var->split_pip)[i] == '>' && (*var->split_pip)[i + 1] == '>')
       {
           fls->type = append;
           var->step = 2;
           fls->file_name = get_filename(&i);
       }
       if (fls->type != '1')
       {
           add_files_tonode(prs, fls);
       }
   }
}

void    fill_command()
{
    t_var *var = get_struc_var(NULL);
    t_parser *prs = get_struc_prs(NULL);
    int i;
    int j;

    i = -1;
    prs = (t_parser *)malloc(sizeof(t_parser));
    prs->next = NULL;
    var->split_sc = ft_split(var->line, ';');
    while (var->split_sc[++i])
    {
        j = -1;

        var->split_pip = ft_split(var->split_sc[i], '|');
        while (var->split_pip[++j])
        {
            search_file();
        }
    }

}

int main()
{
    int r;
    t_var var;
    t_parser prs;
    t_files fls;

    r = 1;
    get_struc_var(&var);
    get_struc_prs(&prs);
    get_struc_fils(&fls);
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
