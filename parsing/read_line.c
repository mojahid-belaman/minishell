#include "../headers/minishell.h"

void my_dll(t_var *var, t_history *list, char *input)
{
    t_history *curr;
    t_history *his;
    int len;

    len = ft_strlen(list->input);
    his = (t_history *)malloc(sizeof(t_history));
    his->next = NULL;
    his->prev = NULL;
    his->cursor = list->cursor;
    his->input = ft_strdup(input);
    if (!var->head_his)
        var->head_his = his;
    else
    {
        curr = var->head_his;
        while (curr->next)
            curr = curr->next;
        his->prev = curr;
        curr->next = his;
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
        free(list->input);
        free(list);
    }
    else
    {
        free(var->head_his->input);
        free(var->head_his);
        var->head_his = NULL;
    }
}

void err_termios(char *err)
{
    ft_putstr_fd(err, 2);
    exit(-1);
}

void termios_config(struct termios *old_attr)
{
    struct termios new_attr;
    char *term_type;
    int ret;

    term_type = getenv("TERM");
    if (term_type == NULL)
        err_termios("\r\033[0KTERM must be set (see 'env').\n");
    ret = tgetent(NULL, term_type);
    if (ret < 0)
        err_termios("\r\033[0KCould not access to the termcap database..\n");
    if (ret == 0)
        err_termios("\r\033[0KTerminal type is not defined in termcap database.\n");
    if (tcgetattr(STDIN_FILENO, old_attr) < 0)
        err_termios("Error tcgetattr\n");
    new_attr = *old_attr;
    new_attr.c_lflag &= ~(ECHO | ICANON | ISIG);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &new_attr) < 0)
        err_termios("\r\033[0KError tcsetattr.\n");
}

t_history *create_node_hist()
{
    t_history *his;

    his = NULL;
    his = (t_history *)malloc(sizeof(t_history));
    his->next = NULL;
    his->prev = NULL;
    his->cursor = 0;
    his->input = NULL;
    return (his);
}

void assign_list(t_var *var, t_history **ls_actual, t_history *his)
{
    t_history *curr;

    if (!(var->head_his))
    {
        var->head_his = his;
        *ls_actual = his;
    }
    else
    {
        curr = var->head_his;
        while (curr->next)
            curr = curr->next;
        his->prev = curr;
        curr->next = his;
        *ls_actual = curr->next;
    }
}

void re_alloc(t_history *ls_actual, int read_press, char *tmp)
{
    int len = 0;
    int i = 0;

    while (ls_actual->input[len])
        len++;
    tmp = (char *)malloc(len + 2);
    i = 0;
    while (i < len)
    {
        tmp[i] = ls_actual->input[i];
        i++;
    }
    free(ls_actual->input);
    tmp[i] = read_press;
    tmp[i + 1] = '\0';
    ls_actual->input = (char *)malloc(len + 2);
    i = 0;
    while (tmp[i])
    {
        ls_actual->input[i] = tmp[i];
        i++;
    }
    ls_actual->input[i] = '\0';
    free(tmp);
}

char *read_line(t_var *var)
{
    t_history *ls_actual;
    t_history *his;
    struct termios old_attr;
    int read_press;
    char *tmp;

    tmp = NULL;
    his = create_node_hist();
    ls_actual = NULL;
    termios_config(&old_attr);
    assign_list(var, &ls_actual, his);
    while (1)
    {
        read_press = 0;
        read(0, &read_press, 4);
        if (read_press > 31 && read_press < 127)
        {
            if (!ls_actual->input)
            {
                ls_actual->input = (char *)malloc(ls_actual->cursor + 2);
                ls_actual->input[ls_actual->cursor] = read_press;
                ls_actual->input[ls_actual->cursor + 1] = '\0';
            }
            else
                re_alloc(ls_actual, read_press, tmp);
            ft_putstr_fd(ls_actual->input + ls_actual->cursor, 1);
            ls_actual->cursor++;
        }
        else if (read_press == key_del)
        {
            if (!ls_actual->cursor)
                continue;
            ls_actual->cursor--;
            ls_actual->input[ls_actual->cursor] = 0;
            ft_putstr_fd("\033[1D\033[K", 1);
        }
        else if (read_press == key_u)
        {
            if (!ls_actual->prev)
                continue;
            ls_actual = ls_actual->prev;
            ft_putstr_fd("\r\033[0K", 1);
            ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
            ft_putstr_fd(ls_actual->input, 1);
        }
        else if (read_press == key_dw)
        {
            if (!ls_actual->next)
                continue;
            ls_actual = ls_actual->next;
            ft_putstr_fd("\r\033[0K", 1);
            ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
            ft_putstr_fd(ls_actual->input, 1);
        }
        else if (read_press == key_en)
        {
            ft_putstr_fd("\n", 1);
            if (!ls_actual->input)
            {
                ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
                continue;
            }
            tmp = ft_strdup(ls_actual->input);
            delete_node(var);
            if (tmp)
                my_dll(var, ls_actual, tmp);
            tcsetattr(STDIN_FILENO, TCSANOW, &old_attr);
            break;
        }
        else if (read_press == CTRL_C)
        {
            delete_node(var);
            his = create_node_hist();
            assign_list(var, &ls_actual, his);
            ft_putstr_fd("\n", 1);
            ft_putstr_fd("\033[1;32mminishell~>\033[0m", 1);
        }
        else if (read_press == CTRL_D)
        {
            if (ls_actual->input)
                continue;
            if (var->status)
            {
                ft_putstr_fd("exit", 1);
                exit(1);
            }
            ft_putstr_fd("exit", 1);
            exit(0);
        }
    }
    return (tmp);
}