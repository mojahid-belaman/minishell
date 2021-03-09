#include "../headers/minishell.h"

t_var *get_struc_var(t_var *ptr)
{
    static t_var *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

t_parser *get_struc_prs(t_parser *ptr)
{
    static t_parser *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}

t_files *get_struc_fils(t_files *ptr)
{
    static t_files *tmp;

    if (ptr)
        tmp = ptr;
    return (tmp);
}