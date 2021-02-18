#include "../headers/minishell.h"


int main()
{
    char *line;
    int status;
    int r;

    line = NULL;
    status = 1;
    while (status)
    {
        r = get_next_line(0, &line);
        
    }
    return (0);    
}
