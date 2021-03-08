
#include "../headers/minishell.h"
#include <limits.h>

void	builtin_pwd(char **command)
{
	char	pwd[PATH_MAX];
	
	if(!(ft_strncmp("pwd", *command, 3)))
	{
		getcwd(pwd, sizeof(pwd));
    	printf("%s\n", pwd);
	}
}

void	builtin_cd(char **command)
{
	int		cd;

	if (!(ft_strncmp("cd", *command, 2)))
	{
		// need to bring it from the env !!!!!!!!
		if (*(command + 1) == NULL || !(ft_strncmp("~", *(command + 1), 1)))
			*(command + 1) = "/Users/knabouss";
		cd = chdir(*(command + 1));
		if (cd < 0)
			printf("cd %s: No such file or directory\n", *(command + 1));
	}
}

int	builtin_exit(char **command)
{
	if (!(ft_strncmp("exit", *command, 4)))
	{
		printf("%s\n",*command);	
		if (*(command + 1) != NULL && *(command + 2) != NULL)
			printf("minishell: exit: too many arguments\n");
		if (*(command + 1) != NULL)
			if (!(ft_isdigit(**(command + 1))))
			{
				printf("minishell: exit: %s: numeric argument required\n", *(command + 1));
				return (0);
			}
	}
	return (1);
}

int verify_echo_n(char *str)
{
	if (*str != '-')
		return (0);
	str++;
	while(*str)
	{
		if (*str == 'n')
			str++;
		else
			return (0);
	}
	return (1);
}

void builtin_echo(char **command)
{
	int		i;

	if (!(ft_strncmp("echo", *command, 4)))
	{
		if (!(verify_echo_n(*(command + 1))))
		{
			i = 1;
			while(*(command + i + 1))
			{
				printf("%s ", *(command + i));
				i++;
			}
			printf("%s\n", *(command + i));
		}
		else
		{
			i = 2;
			while(*(command + i + 1))
			{
				ft_putstr_fd(*(command + i), 1);
				ft_putchar_fd(' ', 1);
				i++;
			}
			ft_putstr_fd(*(command + i), 1);
		}
	}
}

void builtin_env(char **command, char **envp)
{
	int i;

	i = 0;
	if (!(ft_strncmp("env", *command, 3)))
	{
		while(envp[i])
			printf("%s\n", envp[i++]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**command;

	while(1)
	{
		ft_putstr_fd("\033[1;31m$minishell$~> \033[0m", 1);
		get_next_line(0, &line);
		command = ft_split(line, ' ');
	
		builtin_echo(command);
		builtin_pwd(command);
		builtin_cd(command);
		if (!(builtin_exit(command)))
			break;
		builtin_env(command, envp);
	}
	return (0);
}
