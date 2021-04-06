#include <curses.h>
#include <term.h>
#include "../libft/libft.h"
#define key_u 0x415b1b
#define key_dw 0x425b1b
#define key_en 10
#define key_del 127

void read_line()
{
    struct termios s_termios;
    int i;
    int row;
    int col;
    int len;
    int cursor;
    int read_press;
    char cmd[4096];

    ft_bzero(cmd, 4096);
    cursor = 0;
    tcgetattr(0, &s_termios);
    s_termios.c_lflag &= ~(ECHO | ICANON);
    char *term_type = getenv("TERM");
    int ret = tgetent(NULL, term_type);
    tcsetattr(0, 0, &s_termios);

    ft_putstr_fd("\033[1;32mreadline~>\033[0m", 1);
    while (1)
    {
        read_press = 0;
        read(0, &read_press, 4);
        col = tgetnum("col");
        row = tgetnum("li");
        if (read_press > 31 && read_press < 127)
        {
            cmd[cursor] = read_press;
            ft_putstr_fd(cmd + cursor, 1);
            cursor++;
        }
        else if (read_press == key_del)
        {
            
        }
        else if (read_press == key_u)
        {
            printf("up\n");
        }
        else if (read_press == key_dw)
        {
            printf("down\n");
        }
        else if (read_press == key_en)
        {
            ft_putstr_fd("\n", 1);
            break ;
        }
    }

}

int main()
{
    while (1)
        read_line();
    return (0);
}