#include "../headers/minishell.h"

// void init_cursor(int *row, int *col)
// {
//     char answer[20];
//     int i;

//     ft_putstr_fd("\e[6n", 0);
//     ft_bzero(answer, 20);
//     i = read(0, answer, 20);
//     answer[i] = 0;
//     i = 2;
//     *row = ft_atoi(answer + i);
//     while (ft_isdigit(answer[i]))
//         i++;
//     *col = ft_atoi(answer + i + 1);
// }

void my_dll(t_var *var, t_history *list)
{
    t_history *curr;
    t_history *his;
    int len;

    len = ft_strlen(list->input);
    his = (t_history *)malloc(sizeof(t_history));
    his->next = NULL;
    his->prev = NULL;
    his->cursor = list->cursor;
    ft_memcpy(his->input, list->input, len);
    his->input[len] = 0;
    if (!var->head_his)
    {
        var->head_his = his;
        // printf("str : |%s|\n", var->head_his->input);
    }
    else
    {
        curr = var->head_his;
        while (curr->next)
            curr = curr->next;
        his->prev = curr;
        curr->next = his;
        // printf("prev : |%s| now |%s|\n", his->prev->input, his->input);
    }
}

void delete_node(t_var *var)
{
    t_history *list;
    t_history *prev;

    list = NULL;
    prev = NULL;
    list = var->head_his;
    while (list->next)
    {
        prev = list;
        list = list->next;
    }
    if (prev)
    {
        prev->next = NULL;
        free(list);
    }
    else
    {
        free(var->head_his);
        var->head_his = NULL;
    }
}

char *read_line(t_var *var)
{
    struct termios s_termios;
    t_history *list;
    t_history *his;
    t_history *curr;
    // int i;
    // int row;
    // int len;
    // int cursor;
    int read_press;

    his = (t_history *)malloc(sizeof(t_history));
    his->next = NULL;
    his->prev = NULL;
    his->cursor = 0;
    his->input[0] = 0;
    list = NULL;

    if (tcgetattr(0, &s_termios) < 0)
        ft_putstr_fd("error\n", 2);
    s_termios.c_lflag &= ~(ECHO | ICANON);
    char *term_type = getenv("TERM");
    int ret = tgetent(NULL, term_type);
    if (ret == -1)
        ft_putstr_fd("error\n", 2);
    if (tcsetattr(0, TCSANOW, &s_termios) < 0)
        ft_putstr_fd("error\n", 2);
    ft_putstr_fd("\033[1;32mreadline~> \033[0m", 1);
    if (!(var->head_his))
    {
        var->head_his = his;
        list = his;
    }
    else
    {
        curr = var->head_his;
        while (curr->next)
            curr = curr->next;
        his->prev = curr;
        curr->next = his;
        list = curr->next;
    }
    while (1)
    {
        read_press = 0;
        read(0, &read_press, 4);
        if (read_press > 31 && read_press < 127)
        {
            list->input[list->cursor] = read_press;
            ft_putstr_fd(list->input + list->cursor, 1);
            list->cursor++;
        }
        else if (read_press == key_del)
        {
            if (!list->cursor)
                continue;
            list->cursor--;
            list->input[list->cursor] = 0;
            ft_putstr_fd("\033[1D\033[K", 1);
        }
        else if (read_press == key_u)
        {
            if (!list->prev)
                continue;
            list = list->prev;
            ft_putstr_fd("\r\033[0K", 1);
            ft_putstr_fd("\033[1;32mreadline~> \033[0m", 1);
            ft_putstr_fd(list->input, 1);
        }
        else if (read_press == key_dw)
        {
            if (!list->next)
                continue;
            list = list->next;
            ft_putstr_fd("\r\033[0K", 1);
            ft_putstr_fd("\033[1;32mreadline~> \033[0m", 1);
            ft_putstr_fd(list->input, 1);
        }
        else if (read_press == key_en)
        {
            ft_putstr_fd("\n", 1);
            delete_node(var);
            if (list->input[0] != 0)
                my_dll(var, list);
            break;
        }
    }
    return (list->input);
}

int main()
{
    t_var var;
    var = (t_var){0};
    while (1)
        read_line(&var);
    return (0);
}