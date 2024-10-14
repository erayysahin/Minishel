/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:37:41 by erasahin          #+#    #+#             */
/*   Updated: 2024/09/30 14:47:45 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	*get_exit_status(void)
{
	static int	exit_status = 0;

	return (&exit_status);
}

int	skip_space(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}
