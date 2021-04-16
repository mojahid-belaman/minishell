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
