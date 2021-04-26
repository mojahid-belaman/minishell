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
			tmp = var->prs->cmd;
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

void	pipe_exec_bis(t_parser *prs, int *pipefds, int j)
{
	if (prs->next_prs)
		dup2(pipefds[j + 1], STDOUT_FILENO);
	if (j != 0)
		dup2(pipefds[j - 2], STDIN_FILENO);
}

void	pipe_exec(t_var *var, int *pipefds, int pipenumber, char **env)
{
	int		i;
	int		j;

	j = 0;
	while (var->prs)
	{
		i = -1;
		var->pid = fork();
		if (var->pid == 0)
		{
			pipe_exec_bis(var->prs, pipefds, j);
			if (ft_listsize_file(var->prs->file_head) > 0)
				open_file(var);
			while (++i < 2 * pipenumber)
				close(pipefds[i]);
			if (builtin(var) < 0 && !var->error)
				sys_execution_pipe(var, env);
			exit(0);
		}
		var->prs = var->prs->next_prs;
		var->tab_pipe[j / 2] = var->pid;
		j += 2;
	}
}
