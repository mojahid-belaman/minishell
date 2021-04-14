
#include "../headers/minishell.h"

void	error_file(char *str, t_var *var)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory", 2);
	var->status = 1;
	var->error = 1;
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
				error_file(files->file_name, var);
			else
				dup2(var->fd[0], STDIN_FILENO);
			close(var->fd[0]);
		}
		files = files->next;
	}
}

int	builtin(t_var *var)
{
	if (!(ft_strncmp("cd", *(var->prs->args), 3)))
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
		return (-1);
	return (0);
}

void	sys_execution(t_var *var, char **env)
{
	char		*tmp;
	char		*temp;
	pid_t		pid;
	struct stat buffer;
	int			i;
	int			err;
	char		**path;
	
	if (!(tmp = find_value("PATH")))
	{
		temp = tmp;
		tmp = ft_strdup(*var->prs->args);
		free(temp);
	}
	path = ft_split(tmp, ':');
	i = 0;
	while (path[i])
	{
		temp = tmp;
		tmp = ft_strjoin(path[i], "/");
		free(temp);
		tmp = ft_strjoin(tmp, *var->prs->args);
		if (!stat(tmp, &buffer))
			break;
		i++;
		free(tmp);
		tmp = NULL;
	}
	ft_free_args(path);
	pid = fork();
	if (pid == 0)
	{
		// int i = 0;
		// while (var->key_value[i])
		// {
		// ft_putstr_fd(var->key_value[i], 2);
		// ft_putstr_fd("\n", 2);
		// i++;
		// }
		// execve(tmp, var->prs->args, NULL);
		if (execve(tmp, var->prs->args, env) < 0)
		{
		ft_putstr_fd("command not found\n", 2);
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &err, 0);
		var->status = WEXITSTATUS(err);
	}
}

void    execution(t_var *var, char **env)
{
	if (ft_listsize_file(var->prs->file_head) > 0)
			open_file(var);
	if (builtin(var) < 0)
		sys_execution(var, env);
	close(var->fd[1]);
	dup2(var->old_out, STDOUT_FILENO);
	dup2(var->old_in, STDIN_FILENO);
}