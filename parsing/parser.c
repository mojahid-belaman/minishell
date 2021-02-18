#include "../headers/minishell.h"


int main()
{
    int r;
    char *line;

    r = 1;
    while (1)
    {
        r = get_next_line(0, &line);
        break ;
    }
    
}
