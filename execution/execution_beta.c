
#include "../headers/minishell.h"

void	error_file(char *str, t_var *var)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	var->status = 1;
	var->error = 1;
}

void	error_command(char *str, t_var *var)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
	var->status = 127;
	var->error = 1;
}

void	open_file(t_var *var)
{
	t_files	*files;
	struct stat buffer;

	files = var->prs->file_head;
	while (files)
	{
		if (files->type == '>' || files->type == 'a')
		{
			if (files->type == '>')
				var->fd[1] = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else
				var->fd[1] = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
			if (var->fd[1] < 0 && !(stat(files->file_name, &buffer)))
			{
				// if (S_ISDIR(buffer.st_mode))
				// 	ft_putstr_fd("error, is directory\n", 2);
				if (buffer.st_mode & S_IFMT & S_IFDIR)
					ft_putstr_fd("error, is directory\n", 2);
				else if (!(buffer.st_mode & W_OK))
					ft_putstr_fd("Permission denied\n", 2);
				var->status = 1;
				var->error = 1;
			}
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
	if (!(ft_strncmp("cd", *(var->prs->args), 3)) && !var->error)
		builtin_cd(var);
	else if (!(ft_strncmp("pwd", *(var->prs->args), 4)) && !var->error)
		builtin_pwd(var);
	else if (!(ft_strncmp("env", *(var->prs->args), 4)) && !var->error)
		builtin_env(var);
	else if (!(ft_strncmp("unset", *(var->prs->args), 6)) && !var->error)
		builtin_unset(var);
	else if (!(ft_strncmp("exit", *(var->prs->args), 5)) && !var->error)
		builtin_exit(var);
	else if (!(ft_strncmp("export", *(var->prs->args), 7)) && !var->error)
		builtin_export(var);
	else if (!(ft_strncmp("echo", *(var->prs->args), 5)) && !var->error)
		builtin_echo(var);
	else
		return (-1);
	return (0);
}
char	*find_path(t_var *var, char **path)
{
	int			i;
	char		*temp;
	char		*tmp;
	struct stat buffer;

	i = 0;
	tmp = ft_strdup("");
	while (path[i])
	{
		temp = tmp;
		tmp = ft_strjoin(path[i], "/");
		free(temp);
		tmp = ft_strjoin(tmp, *var->prs->args);
		if (!stat(tmp, &buffer) && (buffer.st_mode & F_OK))
			break;
		i++;
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}
void sys_execution(t_var *var, char **env)
{
	struct stat buffer;
	int			err;
	char 		*tmp;
	pid_t		pid;
	char		**path;

	if (!(stat(var->prs->cmd, &buffer)))
	{
		if (buffer.st_mode & X_OK)
			tmp = var->prs->cmd;
		else 
			ft_putstr_fd("error, here ISDIR\n", 2);
	}
	else
	{
		tmp = find_value("PATH");
		path = ft_split(tmp, ':');
		tmp = find_path(var, path);
		ft_free_args(path);
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(tmp, var->prs->args, env) < 0)
		{
			if (!(ft_strcmp(tmp, "")))
				ft_putstr_fd("error!", 2);
			else
				error_command(*var->prs->args, var);
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
	// pid_t pid;
	// int err;
	if (ft_listsize_prs(var->prs) == 1)
	{
		if (ft_listsize_file(var->prs->file_head) > 0)
			open_file(var);
		if (builtin(var) < 0 && !var->error)
			sys_execution(var, env);
	}
	else
	{
		pipe(var->fdp);
		while (var->prs)
		{
		// pid = fork();
		// if (pid == 0)
		// {
			// dup2(var->fdp[0], STDIN_FILENO);
			// dup2(var->fdp[1], STDOUT_FILENO);
			// close(var->fdp[0]);
			// close(var->fdp[1]);
			if (ft_listsize_file(var->prs->file_head) > 0)
				open_file(var);
			if (builtin(var) < 0 && !var->error)
				sys_execution(var, env);
		// }
		// else
		// {
		// 	waitpid(pid, err, 0);
		// 	var->status = WEXITSTATUS(err);
		// }
		// dup2(var->old_out, STDOUT_FILENO);
		// dup2(var->old_out, STDOUT_FILENO);
		var->prs = var->prs->next_prs;
		}
	}
	close(var->fd[1]);
	dup2(var->old_in, STDIN_FILENO);
	dup2(var->old_in, STDIN_FILENO);
}