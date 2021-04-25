#include "../headers/minishell.h"

int	ft_isdig(char *s)
{
	if (ft_sign(*s) && ft_isdigit(*(s + 1)))
		s++;
	while (*s)
	{	
		if (ft_isdigit(*s))
			s++;
		else
			return (0);
	}
	return (1);
}

int	ft_sign(char c)
{
	if (c == '-' || c == '+')
		return (1);
	else
		return (0);
}

void	ft_putstr_error(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
}

char	*find_path(t_var *var, char **path)
{
	int			i;
	char		*temp;
	char		*tmp;
	struct stat	buffer;

	i = 0;
	tmp = ft_strdup("");
	while (path[i])
	{
		temp = tmp;
		tmp = ft_strjoin(path[i], "/");
		free(temp);
		tmp = ft_strjoin(tmp, *var->prs->args);
		if (!stat(tmp, &buffer))
			break ;
		i++;
		free(tmp);
		tmp = NULL;
	}
	return (tmp);
}

void	error_command(char *str, t_var *var)
{
	ft_putstr_error("minishell: ", str, ": command not found\n");
	var->status = 127;
	var->error = 1;
}
