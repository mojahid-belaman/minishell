#include "../headers/minishell.h"

int	ft_isdig(char *s)
{
	if (ft_sign(*s) && ft_isdigit(*(s + 1)))
		s++;
	while(*s)
	{	
		if (ft_isdigit(*s))
			s++;
		else
			return (0);
	}
	return (1);
}

int ft_sign(char c)
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
