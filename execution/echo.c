/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knabouss <knabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 11:12:37 by knabouss          #+#    #+#             */
/*   Updated: 2021/04/15 11:04:44 by knabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

int     echo_option( char *str, int *check)
{
	int i = 0;
	if (str[1] == '\0')
		return (0);
	while(str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	*check = 1;
	return (1);
}

void    builtin_echo(t_var *var)
{
	int i = 1;
	int check = 0;
	
	while (*(var->prs->args + i) && *(var->prs->args + i)[0] == '-' && echo_option(*(var->prs->args + i), &check))
		i++;
	while(*(var->prs->args + i) && *(var->prs->args + i + 1))
	{
		ft_putstr_fd(*(var->prs->args + i), 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (!(*(var->prs->args + 1)))
		ft_putstr_fd("\n", 1);
	else if (!check)
	{
		ft_putstr_fd(*(var->prs->args + i) , 1);
		ft_putstr_fd("\n", 1);
	}
	else
		ft_putstr_fd(*(var->prs->args + i), 1);
	var->status = 0;
}