#include "../headers/minishell.h"

int	fopen_read(t_var *var, t_files *files)
{
	var->fd[0] = open(files->file_name, O_RDONLY);
	if (*files->file_name == token_dollar)
	{
		*files->file_name = 36;
		ft_putstr_error("minishell: ", files->file_name, \
		": ambiguous redirect\n");
		var->error = 1;
		return (0);
	}
	if (var->fd[0] < 0)
	{
		error_file(files->file_name, var);
		return (0);
	}
	else
		dup2(var->fd[0], STDIN_FILENO);
	close(var->fd[0]);
	return (1);
}

void	error_red_app(t_var *var, t_files *files)
{
	struct stat	buffer;

	if (var->fd[1] < 0 && !(stat(files->file_name, &buffer)))
	{
		if (buffer.st_mode & S_IFMT & S_IFDIR)
			no_file(var, files->file_name, "", ": Is a directory\n");
		else if (!(buffer.st_mode & W_OK))
			no_file(var, files->file_name, "", ": Permission denied\n");
		var->error = 1;
	}
}

int	open_files(t_var *var, t_files *files)
{
	if (files->type == '>' && *files->file_name != token_dollar)
	{
		var->fd[1] = open(files->file_name, O_WRONLY \
		| O_CREAT | O_TRUNC, 0666);
	}
	else if (files->type == 'a' && *files->file_name != token_dollar)
		var->fd[1] = open(files->file_name, O_WRONLY \
		| O_CREAT | O_APPEND, 0666);
	else if (*files->file_name == token_dollar)
	{
		*files->file_name = 36;
		no_file(var, files->file_name, "", ": ambiguous redirect\n");
		var->error = 1;
		return (0);
	}
	if (var->fd[1] < 0)
	{
		error_open_file(var, files);
		return (0);
	}
	return (1);
}

void	open_file(t_var *var)
{
	t_files		*files;

	files = var->prs->file_head;
	while (files)
	{
		if (files->type == '>' || files->type == 'a')
		{
			if (!open_files(var, files))
				break ;
			error_red_app(var, files);
			dup2(var->fd[1], STDOUT_FILENO);
			close(var->fd[1]);
		}
		else
			if (!fopen_read(var, files))
				break ;
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
