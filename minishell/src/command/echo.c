/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:07:05 by erasahin          #+#    #+#             */
/*   Updated: 2024/09/30 15:32:47 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

int	is_echo(char *str1, char *str2)
{
	int	i;

	i = 0;
	if (!str1 || !str2)
		return (1);
	i = 0;
	while (ft_tolower(str1[i]) && str2[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

int	check_flags(t_token_node *node)
{
	int	i;

	i = 1;
	if ((node->type == WORD && !node->value[0]))
		return (2);
	if (!node->value[i])
		return (0);
	while (node->value[i])
	{
		if (node->value[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	cmd_echo(t_token_node *node)
{
	int	check;

	check = 0;
	if (node)
		node = node->next;
	while (node && ((is_args(node) && *node->value == '-')
			|| (node->type == WORD && !node->value[0])))
	{
		if (!check_flags(node))
			break ;
		check = check_flags(node);
		node = node->next;
	}
	while (node)
	{
		if (is_args(node))
			printf("%s", node->value);
		else
			return ;
		node = node->next;
	}
	if (check != 1)
		printf("s\n");
	*get_exit_status() = 0;
}
