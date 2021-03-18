#include <stdio.h>


void override_str(char **str, int index)
{
    while ((*str)[index] != '\0')
    {
        (*str)[index] = (*str)[index + 1];
        index++;
    }
}

int check_for_simple_double(char **line, int *i, int *s, int *d)
{
    int x = 0;

    if ((*line)[*i] == '\"' && *s == 0)
    {
        override_str(line, *i);
        *d = !(*d);
        x = 1;
    }
    // if ((*line)[*i] == '\'' && *d == 0)
    // {
    //     override_str(line, *i);
    //     (*s) = !(*s);
    //     if (*s == 0)
    //         (*i)--;
    //     x = 1;
    // }
    return (x);
}

void clear_line(char **line)
{
    int i = -1;
    int d = 0;
    int s = 0;

    while ((*line)[++i] != '\0')
    {
        while (check_for_simple_double(line, &i, &s, &d))
            ;
    }

}
int main() {

  char *str = "echo \"hello\" > \"f1\"";
  clear_line(&str);
  printf("%s", str);
  return 0;
}