
#include "../headers/minishell.h"

void	error_file(char *str, t_var *var)
{
	ft_putstr_error("minishell: ", str, ": No such file or directory\n");
	var->status = 1;
	var->error = 1;
}

void	error_command(char *str, t_var *var)
{
	ft_putstr_error("minishell: ", str, ": command not found\n");
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
			if (files->type == '>' && *files->file_name != token_dollar)
				var->fd[1] = open(files->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			else if (files->type == 'a' && *files->file_name != token_dollar)
				var->fd[1] = open(files->file_name, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else if (*files->file_name == token_dollar)
			{
				*files->file_name = 36;
				ft_putstr_error( "minishell: ", files->file_name, ": ambiguous redirect\n");
				var->error = 1;
				return;
			}
			if (var->fd[1] < 0 && !(stat(files->file_name, &buffer)))
			{
				if (buffer.st_mode & S_IFMT & S_IFDIR)
				ft_putstr_error("minishell:", files->file_name, ": Is a directory\n");
				else if (!(buffer.st_mode & W_OK))
					ft_putstr_error("minishell:", files->file_name, "Permission denied\n");
				var->status = 1;
				var->error = 1;
			}
			dup2(var->fd[1], STDOUT_FILENO);
			close(var->fd[1]);
		}
		else
		{
			var->fd[0] = open(files->file_name, O_RDONLY);
			if (*files->file_name == token_dollar)
			{
				*files->file_name = 36;
				ft_putstr_error( "minishell: ", files->file_name, ": ambiguous redirect\n");
				var->error = 1;
				return;
			}
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
		if (!stat(tmp, &buffer))
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
	char 		*tmp = NULL;
	pid_t		pid;
	char		**path;

	if (!(stat(var->prs->cmd, &buffer)))
	{
		if (buffer.st_mode & S_IFMT & S_IFDIR)
		{
			ft_putstr_error("minishell: ", var->prs->cmd, ": is a directory\n");
			return ;
		}
		else if (buffer.st_mode & X_OK)
			tmp = var->prs->cmd;
	}
	else if (var->prs->cmd[0] == '.' || var->prs->cmd[0] == '/')
	{
		ft_putstr_error("minishell: ", var->prs->cmd, ": No such file or directory\n");
		return ;
	}
	else
	{
		tmp = find_value("PATH", var);
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
			{
				ft_putstr_error("minishell: ", tmp, ": No such file or directory\n");
				free(tmp);
			}
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

void	sys_execution_pipe(t_var *var, char **env)
{
	struct stat buffer;
	char 		*tmp = NULL;
	char		**path;

	if (!(stat(var->prs->cmd, &buffer)))
	{
		if (buffer.st_mode & S_IFMT & S_IFDIR)
		{
			ft_putstr_error("minishell: ", var->prs->cmd, ": is a directory\n");
			return ;
		}
		else if (buffer.st_mode & X_OK)
			tmp = var->prs->cmd;
	}
	else if (var->prs->cmd[0] == '.' || var->prs->cmd[0] == '/')
	{
		ft_putstr_error("minishell: ", var->prs->cmd, ": No such file or directory\n");
		return ;
	}
	else
	{
		tmp = find_value("PATH", var);
		path = ft_split(tmp, ':');
		tmp = find_path(var, path);
		ft_free_args(path);
	}
	if (execve(tmp, var->prs->args, env) < 0)
	{
		if (!(ft_strcmp(tmp, "")))
			ft_putstr_fd("error!", 2);
		else
			error_command(*var->prs->args, var);
		exit(127);
	}
}

void	execute_pipe(t_var *var, char **env)
{
	int i = -1;
	int pipenumber = ft_listsize_prs(var->prs) - 1;
	int	*pipefds = malloc(sizeof(int) * (2 * pipenumber));
	pid_t pid;
	pid_t *p = malloc(sizeof(pid_t) * (2 * pipenumber));
	int j = 0;

	while(++i < pipenumber)
		pipe(pipefds + i * 2);
	i = -1;
	while(var->prs)
	{
		pid = fork();
		if (pid == 0)
		{
			//if not last
			if (var->prs->next_prs)
				dup2(pipefds[j + 1], STDOUT_FILENO);
			//if not first
			if (j != 0)
				dup2(pipefds[j - 2], STDIN_FILENO);
			if (ft_listsize_file(var->prs->file_head) > 0)
				open_file(var);
			while (++i < 2 * pipenumber)
				close(pipefds[i]);	
			i = -1;
			if (builtin(var) < 0 && !var->error)
				sys_execution_pipe(var, env);
			exit(0);
		}
		else if (pid < 0)
		{
			ft_putstr_fd("error1", 2);
			exit(127);
		}
		var->prs = var->prs->next_prs;
		p[j / 2] = pid;
		j+= 2;
	}
	i = -1;
	while(++i < 2 * pipenumber)
		close(pipefds[i]);
	i = -1;
	while(++i < pipenumber + 1)
		waitpid(p[i] ,&var->status, 0);
	var->status = WEXITSTATUS(var->status);
}

void    execution(t_var *var, char **env)
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
	else 
		ft_putstr_error("minishell: ", " ", "command not found\n");
	dup2(var->old_in, STDIN_FILENO);
	dup2(var->old_out, STDOUT_FILENO);
}
