/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:12:37 by knabouss          #+#    #+#             */
/*   Updated: 2021/04/26 15:20:13 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int	echo_option(char *str, int *check)
{
	int	i;

	i = 0;
	if (str[1] == '\0')
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	*check = 1;
	return (1);
}

void	builtin_echo(t_var *var)
{
	int	i;
	int	check;

	i = 1;
	check = 0;
	while (*(var->prs->args + i) && *(var->prs->args + i)[0] == '-' \
	&& echo_option(*(var->prs->args + i), &check))
		i++;
	while (*(var->prs->args + i) && *(var->prs->args + i + 1))
	{
		ft_putstr_fd(*(var->prs->args + i), 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (!(*(var->prs->args + 1)))
		ft_putstr_fd("\n", 1);
	else if (!check)
	{
		ft_putstr_fd(*(var->prs->args + i), 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd(*(var->prs->args + i), 1);
	var->status = 0;
}

void	error_open_file(t_var *var, t_files *files)
{
	struct stat	buff;

	if (!(stat(files->file_name, &buff)))
	{
		if (buff.st_mode & S_IFMT & S_IFDIR)
			no_file(var, files->file_name, "", ": Is a directory\n");
	}
	else
		no_file(var, files->file_name, "", ": No such file or directory\n");
	var->error = 1;
}

void	replace_pwd(t_env *pwd, t_env *oldpwd, char *path)
{
	free(oldpwd->value);
	oldpwd->value = ft_strdup(pwd->value);
	free(pwd->value);
	pwd->value = ft_strdup(path);
}
