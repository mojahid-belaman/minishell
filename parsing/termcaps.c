#include <curses.h>
#include <term.h>
#include <stdlib.h>
#include "../libft/libft.h"
#define hex
void print_escape_sequence(char *str)
{
    unsigned i = 0;

    while (str[i] != '\0')
    {
        if (str[i] == '\x1b')
            printf("ESC");
        else
            putchar(str[i]);

        ++i;
    }

    putchar('\n');
}

int main(void)
{
    int ret;
    struct termios s_termios;
    // function getenv
    char *term_type = getenv("TERM");
    // function tgetent return (1, 0, -1)
    ret = tgetent(NULL, term_type);
    // function tgetnum  permet de récupérer des informations numériques en rapport avec votre terminal.
    int get_line = tgetnum("co");
    int get_column = tgetnum("li");
    // function tgetstr
    // char *cm_cap = tgetstr("AF", NULL);
    // char *reset_cmd = tgetstr("me", NULL);
    // char *underline_cmd = tgetstr("us", NULL);
    // char *buff;
    tcgetattr(0, &s_termios);
    s_termios.c_lflag &= ~(ICANON);
    s_termios.c_lflag &= ~(ECHO);
    tcsetattr(0, 0, &s_termios);
    char answer[20];
    int i;
    ft_putstr_fd("\e[6n", 0);
    ft_bzero(answer, 20);
    i = read(0, answer, 20);
    answer[i] = 0;
    i = 2;
    int row = ft_atoi(answer + i);
    while (ft_isdigit(answer[i]))
        i++;
    int col = ft_atoi(answer + i + 1);
    printf("|%d|%d|\n", row, col);
    // // int l = read(0, str, 4);
    // // printf("|%x||%x|%x|%x|\n", str[0], str[1], str[2], str[3]);
    // // printf("|%d||%d|%d|%d|", str[0], str[1], str[2], str[3]);
    // while (1)
    // {
    //     // ft_putstr_fd(tparm(cm_cap, COLOR_CYAN), 0);
    //     // // ft_putstr_fd(reset_cmd, 0);
    //     // ft_putstr_fd(underline_cmd, 0);
    //     str = malloc(sizeof(char) * 4);
    //     ft_bzero(str, 4);
    //     read(0, str, 4);
    //     printf("str: %d|%d|%d|%d\n", str[0], str[1], str[2], str[3]);
    //     printf("str: %x|%x|%x|%x\n", str[0], str[1], str[2], str[3]);
    // }
    // function tputs
    // char *par = tparm(cl_cap);
    // // affichage
    // printf("|%d|\n", ret);
    // printf("|li=%d|\n|col=%d|\n", get_line, get_column);
    // printf("|%s|\n", cl_cap);
    // printf("|%d|\n", a);
    // ft_fd("|%s|\n", par);
    return (0);
}