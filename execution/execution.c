
#include "../headers/minishell.h"

void print_list_env(t_env *head)
{
	t_env *curr;

	curr = head;
	if (!curr)
		puts("failed");
	while (curr)
	{
		printf("|%s||%s|\n", curr->key, curr->value);
		curr = curr->next;
	}
}

void execution(t_var *var)
{
	char *tmp = find_value("PATH");
	char **path;
	char *tmep;
	struct stat buffer;
	int id = 0;
	int i = 0;
	path = ft_split(tmp, ':');
	free(tmp);
	id = fork();
	if (id == 0)
	{
		// free(tmp);
		while (path[i])
		{
			tmp = ft_strjoin(path[i], "/");
			tmep = tmp;
			tmp = ft_strjoin(tmp, *var->prs->args);
			free(tmep);
			if (!stat(tmp, &buffer))
				execve(tmp, var->prs->args, NULL);
			i++;
			free(tmp);
			tmp = NULL;
		}
		if (stat(*(var->prs->args),  &buffer) && (**(var->prs->args) == '.' || **(var->prs->args) == '/'))
			printf("minishell: %s: No such file or directory\n", *(var->prs->args));
		else if (!(path[i]))
			printf("minishell: %s: command not found\n", *var->prs->args);
		exit(0);
	}
	else
		wait(NULL);
	ft_free_args(path);
}

void	open_file()
{
	t_var *var = get_struc_var(NULL);
	t_files	*files;
	// struct stat buffer;
	files = var->prs->file_head;
	while (files)
	{
		var->fd[0] = open(files->file_name, O_RDWR | O_CREAT, 0666);
		files = files->next;
	}
}

void    execute(t_var *var)
{
	struct stat buffer;
	if (ft_listsize_file(var->prs->file_head) > 0)
		open_file();
	if (!stat(*(var->prs->args),  &buffer))
	{
		// need to specify the type
		printf("minishell: %s: is a directory\n", *(var->prs->args));
	}
	else if (!(ft_strncmp("cd", *(var->prs->args), 3)))
		builtin_cd(var);
	else if (!(ft_strncmp("pwd", *(var->prs->args), 4)))
		builtin_pwd(var);
	else if (!(ft_strncmp("env", *(var->prs->args), 4)))
		builtin_env(var);
	else if (!(ft_strncmp("unset", *(var->prs->args), 6)))
		builtin_unset(var);
	else if (!(ft_strncmp("exit", *(var->prs->args), 5)))
		builtin_exit(var);
	else if (!(ft_strncmp("export", *(var->prs->args), 7)))
		builtin_export(var);
	else if (!(ft_strncmp("echo", *(var->prs->args), 5)))
		builtin_echo(var);
	else
		execution(var);
}

