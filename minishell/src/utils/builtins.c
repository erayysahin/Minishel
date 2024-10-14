/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:25:49 by kcevik            #+#    #+#             */
/*   Updated: 2024/10/03 12:33:20 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <unistd.h>

int	builtins(char *path)
{
	if (!is_echo(path, "echo"))
		return (1);
	if (ft_strcmp(path, "cd") == 0)
		return (1);
	if (ft_strcmp(path, "pwd") == 0)
		return (1);
	if (ft_strcmp(path, "export") == 0)
		return (1);
	if (ft_strcmp(path, "unset") == 0)
		return (1);
	if (ft_strcmp(path, "env") == 0)
		return (1);
	if (ft_strcmp(path, "exit") == 0)
		return (1);
	return (0);
}


