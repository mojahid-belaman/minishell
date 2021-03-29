#include "../headers/minishell.h"

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

void    replace_dollar(char **line, int *i, int *sq)
{
    int index_dollar;
    char *str_after_doll;
    char *str_value_doll;

    if ((*line)[*i] == '$' && *sq == 0)
    {
        index_dollar = set_index((*line) + *i + 1);
        str_after_doll = ft_substr((*line) + *i + 1, 0, index_dollar);
        str_value_doll = get_env_value(str_after_doll);
        if (index_dollar != 0)
        {
            str_after_doll = ft_strjoin(str_value_doll, (*line) + *i + 1 + index_dollar);
            (*line)[*i] = '\0';
            str_value_doll = ft_strjoin((*line), str_after_doll);
            (*line) = str_value_doll;
        }
    }
}

void clear_line(char **line)
{
    int i = -1;
    int dq = 0;
    int sq = 0;

    while ((*line)[++i] != '\0')
    {
       del_sq_dq(line, &i, &sq, &dq);
       replace_dollar(line, &i, &sq);
       if (dq == 1 && (*line)[i] == '\\' && ((*line)[i + 1] == '$' || (*line)[i + 1] == '\"' || (*line)[i + 1] == '\\' || (*line)[i + 1] == '`'))
            new_str(line, i);
        if ((dq || sq) && (*line)[i] > 0)
            (*line)[i] = -(*line)[i];
        if (dq == 0 && sq == 0 && (*line)[i] == '\\' && (*line)[i + 1] == '\\')
        {
            new_str(line, i);
            (*line)[i] = -(*line)[i];
        }
        if (dq == 0 && sq == 0 && (*line)[i] == '\\')
        {
            if ((*line)[i + 1] == '\0')
            {
                hundel_error(new_line);
                return ;
            }
            new_str(line, i);
            if ((*line)[i] == '\'' || (*line)[i] == '\"')
                (*line)[i] = -(*line)[i];
        }
    }
}