#include "../headers/minishell.h"

void	error_file(char *str, t_var *var)
{
	ft_putstr_error("minishell: ", str, ": No such file or directory\n");
	var->status = 1;
	var->error = 1;
}

void	sys_execution(t_var *var, char **env)
{
	int			err;
	char		*tmp;

	tmp = join_command(var);
	g_pid = fork();
	if (g_pid == 0)
		ft_execve(tmp, var, env);
	else
	{
		free(tmp);
		waitpid(g_pid, &err, 0);
		var->status = WEXITSTATUS(err);
	}
}

void	sys_execution_pipe(t_var *var, char **env)
{
	char		*tmp;

	tmp = join_command(var);
	if (!tmp)
		return ;
	ft_execve(tmp, var, env);
}

void	execute_pipe(t_var *var, char **env)
{
	int		i;
	int		pipenumber;
	int		*pipefds;
	int		j;

	j = 0;
	pipenumber = ft_listsize_prs(var->prs) - 1;
	var->tab_pipe = malloc(sizeof(pid_t) * (2 * pipenumber));
	pipefds = malloc(sizeof(int) * (2 * pipenumber));
	i = -1;
	while (++i < pipenumber)
		pipe(pipefds + i * 2);
	pipe_exec(var, pipefds, pipenumber, env);
	i = -1;
	while (++i < 2 * pipenumber)
		close(pipefds[i]);
	i = -1;
	while (++i < pipenumber + 1)
		waitpid(var->tab_pipe[i], &var->status, 0);
	var->status = WEXITSTATUS(var->status);
}

/*void	signal_handler(int signo)0
{
	// if (g_pid == 0)
	// 	exit(0);
	// if (g_pid > 0)
	// {
		// (void )signo;
	
		if (signo == 2)
			ft_putstr_fd("bash\n", 2);
		else if (signo == 3)
			ft_putstr_fd("Quit: 3\n", 2);
	// }
} */

void	execution(t_var *var, char **env)
{
	/* signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler); */
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
