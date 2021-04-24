#include "../headers/minishell.h"

void    chpwd_bis(t_env *pwd, t_env *oldpwd, char *path)
{
    if (oldpwd->print == 1 && pwd->print == 1)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(path);
	}
	else if (oldpwd->print == 2 && pwd->print == 1)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(path);
		oldpwd->print = 3;
	}
	else if (oldpwd->print == 1 && pwd->print == 2)
	{
		oldpwd->value = ft_strdup("");
		pwd->value = ft_strdup(path);
		oldpwd->print = 2;
	}
	else if (oldpwd->print == 2 && pwd->print == 2)
	{
		oldpwd->value = ft_strdup(pwd->value);
		pwd->value = ft_strdup(path);
	}
	free(path);
}

