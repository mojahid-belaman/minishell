
#include "../headers/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**command;
	t_env	*head;
	t_envar	*en_var;

	head = get_env(envp);
	en_var = get_envar(head);
	while(1)
	{
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
		get_next_line(0, &line);
		command = ft_split(line, ' ');
		builtin(command, &head, en_var);
		/* need a beta version!! complete mess!!!!!
		builtin_cd(command, head);
		builtin_pwd(command, head);
		builtin_env(command, head);
		builtin_echo(command);
		if (!(builtin_exit(command)))
			break;
		*/
	}
	return (0);
}
