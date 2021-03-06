
#include "../headers/minishell.h"
#include <limits.h>

int verify_echo_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while(*str)
		if (*str == 'n')
			str++;
		else
			return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**command;
	int		cd;
	char	pwd[PATH_MAX];
	while(1)
	{
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
		get_next_line(0, &line);
		command = ft_split(line, ' ');
		//let's start builtin;

		if(!(ft_strncmp("pwd", *command, 3)))
		{
			getcwd(pwd, sizeof(pwd));
    		printf("%s\n", pwd);
		}
		if (!(ft_strncmp("cd", *command, 2)))
		{
			// need to bring it from the env !!!!!!!!
			if (*(command + 1) == NULL || !(ft_strncmp("~", *(command + 1), 1)))
				*(command + 1) = "/Users/knabouss";
			cd = chdir(*(command + 1));
			if (cd < 0)
				printf("cd %s: No such file or directory\n", *(command + 1));
		}
		if (!(ft_strncmp("exit", *command, 4)))
		{
			printf("%s\n",*command);	
			if (*(command + 1) != NULL)
				if (!(ft_isdigit(**(command + 1))))
					printf("minishell: exit: %s: numeric argument required\n", *(command + 1));
			break;
		}
		if (!(ft_strncmp("echo", *command, 4)))
		{
			if (!(ft_strncmp("-n",)))
		}
	}
	return (0);
}
