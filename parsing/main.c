#include <stdio.h>
#include "../libft/libft.h"


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

void clear_line(char **line)
{
    int i = -1;
    int dq = 0;
    int sq = 0;

    while ((*line)[++i] != '\0')
       del_sq_dq(line, &i, &sq, &dq);
    

}
int main() {

  char *str;
  str = ft_strdup("echo \"'\"");
  clear_line(&str);
  printf("%s", str);
  return 0;
}