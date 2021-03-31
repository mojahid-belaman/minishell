#include "../headers/minishell.h"

void remove_file(int *i, int org, int *j)
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
    free(str1);
    free(str2);
    *i = org - 1;
}

char *get_filename(int *i, int *j)
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

void search_file(int *j)
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
    if (fil->next == NULL)
        free(fil);
}