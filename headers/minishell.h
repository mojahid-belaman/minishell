#ifndef MINISHELL_H
#define MINISHELL_H

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <sys/stat.h>
#include "../libft/libft.h"
#include <curses.h>
#include <term.h>
#define key_u 0x415b1b
#define key_dw 0x425b1b
#define key_en 10
#define key_del 127

#define BUFFER_SIZE 1024
#define token_rr 1
#define token_rl 2
#define token_dr 3
#define token_sc 4
#define token_dsc 7
#define token_pip 5
#define new_line 6
#define token_dpip 8
#define append 'a'
#define right_r '>'
#define left_r '<'
#define red `tput setaf 1`
#define reset `tput sgr0`

typedef struct s_history
{
	char input[4096];
	int cursor;
	struct s_history *next;
	struct s_history *prev;
} t_history;

typedef struct s_env
{
	char *key;
	char *value;
	int print;
	struct s_env *next;
} t_env;

typedef struct s_files
{
	char type;
	char *file_name;
	struct s_files *next;
} t_files;

typedef struct s_parser
{
	char *cmd;
	char **args;
	t_files *file_head;
	struct s_parser *next_prs;
} t_parser;

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
	char *line;
	char **split_sc;
	char **split_pip;
	int step;
	char *home;
	int status;
	t_parser *prs;
	t_parser *prsTail;
	t_env *head_env;
	t_history *head_his;
} t_var;

//parsing
int isprint_car(int p);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strchr(const char *s, int c);
char *ft_strdup(const char *src);
size_t ft_strlen(const char *str);
int get_next_line(int fd, char **line);
void syntax_error(t_var *var, int i);
int hund_last_sc(int i);
void check_single_q();
void check_double_q();
void check_redir_r();
void check_redir_l();
void check_redir_d(int i);
void check_semicolomn(int i);
void check_pipe(int i);
void conv_neg_space(int i);
void hundel_error(int err);
void get_env(char **envp);
void ft_lstadd_back(t_env **alst, t_env *news);
t_env *create_node(char **key_value);
char **split_env(char *line);
t_var *get_struc_var(t_var *ptr);
void free_list_cmd(t_parser *prs);
void free_list_files(t_parser *prs);
void add_prs_tonode(t_var *var, t_parser *node);
void add_files_tonode(t_files *fil);
void search_file(t_var *var, int *j);
void search_cmd_args(t_var *var, int *j);
void clear_line(t_var *var, char **line);
int set_index(char *str);
char *get_env_value(char *key);
char *read_line(t_var *var);
//execution
char *get_home();
int get_oldpwd();
void chpwd_env();
char *check_home();
void export_env();
void export_var(int *j);
int echo_option(char *str, int *check);
int ft_listsize();
char *find_value(char *find);
void builtin_cd();
void builtin_pwd();
void builtin_env();
void builtin_unset();
int builtin_exit();
void builtin_echo();
void builtin_export();
void execution();
void execute();
// need to be removed
void print_list_env(t_env *head);
#endif