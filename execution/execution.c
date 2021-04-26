#include "../headers/minishell.h"

void	error_file(char *str, t_var *var)
{
	no_file(var, var->prs->cmd, "", ": No such file or directory\n");
	var->error = 1;
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

void	sys_execution_pipe(t_var *var, char **env)
{
	var->tmp = join_command(var);
	if (!var->tmp)
		return ;
	ft_execve(var->tmp, var, env);
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
	free(var->tab_pipe);
	free(pipefds);
	// if (var->tmp)
	// 	free(var->tmp);
}

void	signal_handler_c(int signo)
{
	(void)signo;
	if (g_var->pid == 0)
		exit(0);
	ft_putstr_fd("\n", 2);
	g_var->status = 130;
}

void	signal_handler_quit(int signo)
{
	(void)signo;
	ft_putstr_fd("Quit: 3\n", 2);
	g_var->status = 131;
}

// void	execution(t_var *var, char **env)
// {
// 	if (ft_listsize_prs(var->prs) == 1)
// 	{
// 		if (ft_listsize_file(var->prs->file_head) > 0)
// 			open_file(var);
// 		if (!var->error)
// 		{
// 			if (builtin(var) < 0 && !var->error)
// 				sys_execution(var, env);
// 		}
// 	}
// 	else if (ft_listsize_prs(var->prs) > 1)
// 		execute_pipe(var, env);
// 	dup2(var->old_in, STDIN_FILENO);
// 	dup2(var->old_out, STDOUT_FILENO);
// }
