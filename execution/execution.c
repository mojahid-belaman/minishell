
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
	char *tmp;
	char **path;
	struct stat buffer;
	int id = 0;
	int		err;
	int i = 0;
	if (!(tmp = find_value("PATH")))
		tmp = *var->prs->args;
	path = ft_split(tmp, ':');
	free(tmp);
	while (path[i] && var->head_env->print == 1)
	{
		tmp = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(tmp, *var->prs->args);
		if (!stat(tmp, &buffer))
			break;
		i++;
		free(tmp);
		tmp = NULL;
	}
	id = fork();
	if (id == 0)
	{
		if (execve(tmp, var->prs->args, NULL) < 0)
			exit(127);
	}
	else
	{
		waitpid(id, &err, 0);
		var->status = WEXITSTATUS(err);
	}
	// if (stat(*(var->prs->args),  &buffer) && (**(var->prs->args) == '.' || **(var->prs->args) == '/'))
	// 	printf("minishell: %s: No such file or directory\n", *(var->prs->args));
	// else if (!(path[i]))
	// 	printf("minishell: %s: command not found\n", *var->prs->args);
}

void	open_file(t_var *var)
{
	t_files	*files;

	files = var->prs->file_head;
	while (files)
	{
		if (files->type == '>' || files->type == 'a')
		{
			if (files->type == '>')
				var->fd[1] = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				var->fd[1] = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
			dup2(var->fd[1], STDOUT_FILENO);
			close(var->fd[1]);
		}
		else
		{
			var->fd[0] = open(files->file_name, O_RDONLY);
			if (var->fd[0] < 0)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(files->file_name, 2);
				ft_putstr_fd(": No such file or directory", 2);
				var->status = 1;
				var->error = 1;
			}
			else
				dup2(var->fd[0], STDIN_FILENO);
			close(var->fd[0]);
		}
		files = files->next;
	}
}

void    execute(t_var *var)
{
	struct stat buffer;
	// while(var->prs)
	// {
		// if (var->prs->next_prs)
		// {
		// 	pipe(var->fd);
		// 	dup2(var->fd[1], STDOUT_FILENO);
		// 	dup2(var->fd[0], STDIN_FILENO);
		// }
		if (ft_listsize_file(var->prs->file_head) > 0)
			open_file(var);
		if (!stat(*(var->prs->args),  &buffer))
		{
			if ((buffer.st_mode & S_IFDIR))
				printf("minishell: %s : is a directory\n", *(var->prs->args));
			else if (!(buffer.st_mode & X_OK))
				printf("minishell: %s: permission denied\n", *(var->prs->args));
			else
				execution(var);
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
		else if (!var->error && !(var->error = 0))
			execution(var);
		// cd , export, unset , exit; 
	// 	var->prs = var->prs->next_prs;
	// }
	close(var->fd[1]);
	dup2(var->old_out, STDOUT_FILENO);
	dup2(var->old_in, STDIN_FILENO);
}

