#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"

# define BUFFER_SIZE 1024
# define token_rr 1
# define token_rl 2
# define token_dr 3
# define token_sc 4
# define token_pip 5
# define new_line 6
typedef struct s_files
{
    char type;
    char *file_name;
    struct s_files *next;
}               t_files;


typedef struct s_parser
{
    char *cmd;
    char **args;
    t_files *file;
    struct s_parser *next;
}               t_parser;

typedef struct s_var
{
    int single_q;
    int double_q;
    int semi_colomn;
    int pipe;
    int redir_left;
    int redir_right;
    int redir_double;
    int back_sl;
    int error;
    char ch;
    char *line;
    char **split_sc;
    char **split_pip;
}              t_var;

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);
int		get_next_line(int fd, char **line);
void    syntax_error();
int     hund_last_sc(int i);
t_var   *getStruct(t_var *ptr);
void    check_single_q();
void    check_double_q();
void    check_redir_r();
void    check_redir_l();
void    check_redir_d();
void    check_semicolomn(int i);
void    check_pipe();
void    hundel_error(int err);
t_var   *get_struct_var(t_var *ptr);
t_parser    *get_struct_prs(t_parser *ptr);
t_files *get_struct_file(t_files *ptr);
#endif