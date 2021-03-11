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

// char *get_file_name(char **str, int *index, int count)
// {
// 	int save = *index;
// 	int index_s = 0;
// 	int index_e = 0;

// 	*index += count;
// 	char *tmp;
// 	while ((*str)[*index] == ' ')
// 	{
// 		(*index)++;
// 		index_s++;
// 	}
// 	while ((*str)[*index] != '\0' && (*str)[*index] != '>' && (*str)[*index] != '<' && (*str)[*index] != ' ')
// 	{
// 		(*index)++;
// 		index_e++;
// 	}
// 	tmp = ft_substr(*str, save + count + index_s, index_e);
// 	// printf("file name:|%s|\n", tmp);
// 	char *tmp1 = ft_substr(*str, *index, ft_strlen(*str));
// 	(*str)[save] = '\0';
// 	char *tmp2 = *str;
// 	*str = ft_strjoin(tmp2, tmp1);

// 	// printf("new str:|%s|\n", *str);
// 	// free(tmp1); ///////// showen err break Point: freed was not allocated
// 	// free(tmp2);
// 	// tmp1 = tmp2 = NULL;
// 	*index = save - 1;
// 	return (tmp);
// }