#include "../headers/minishell.h"

void	pipe_exec(t_var *var, int *pipefds, int pipenumber, char **env)
{
	int			i;
	int			j;

	j = 0;
	var->parser = var->prs;
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
	var->prs = var->parser;
}

void	pipe_exec_bis(t_parser *prs, int *pipefds, int j)
{
	if (prs->next_prs)
		dup2(pipefds[j + 1], STDOUT_FILENO);
	if (j != 0)
		dup2(pipefds[j - 2], STDIN_FILENO);
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
}
