#include "../headers/minishell.h"

char	*join_path(t_var *var)
{
	char	**path;
	char	*tmp;

	tmp = find_value("PATH", var);
	path = ft_split(tmp, ':');
	free(tmp);
	tmp = find_path(var, path);
	ft_free_args(path);
	return (tmp);
}

char	*join_command(t_var *var)
{
	struct stat	buffer;
	char		*tmp;

	tmp = NULL;
	if (!(stat(var->prs->cmd, &buffer)))
	{
		if (buffer.st_mode & S_IFMT & S_IFDIR)
		{
			no_file(var, var->prs->cmd, "", ": is a directory\n");
			return (NULL);
		}
		else if (buffer.st_mode & X_OK)
			tmp = ft_strdup(var->prs->cmd);
	}
	else if (var->prs->cmd[0] == '.' || var->prs->cmd[0] == '/')
	{
		no_file(var, var->prs->cmd, "", ": No such file or directory\n");
		return (NULL);
	}
	else
		tmp = join_path(var);
	return (tmp);
}

void	sys_execution(t_var *var, char **env)
{
	int			err;
	char		*tmp;

	tmp = join_command(var);
	var->status = 0;
	var->pid = fork();
	if (var->pid == 0)
		ft_execve(tmp, var, env);
	else
	{
		free(tmp);
		waitpid(var->pid, &err, 0);
		if (WEXITSTATUS(err))
			var->status = WEXITSTATUS(err);
	}
}

void	ft_execve(char *tmp, t_var *var, char **env)
{
	if (execve(tmp, var->prs->args, env) < 0)
	{
		if (!(ft_strcmp(tmp, "")))
		{
			no_file(var, var->prs->cmd, "", ": No such file or directory\n");
			free(tmp);
		}
		else if (tmp != NULL)
			error_command(*var->prs->args, var);
		exit(127);
	}
}

void	execution(t_var *var, char **env)
{
	if (ft_listsize_prs(var->prs) == 1)
	{
		if (ft_listsize_file(var->prs->file_head) > 0)
			open_file(var);
		if (!var->error)
		{
			if (builtin(var) < 0 && !var->error)
				sys_execution(var, env);
		}
	}
	else if (ft_listsize_prs(var->prs) > 1)
		execute_pipe(var, env);
	dup2(var->old_in, STDIN_FILENO);
	dup2(var->old_out, STDOUT_FILENO);
}
