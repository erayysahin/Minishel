/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:08:25 by erasahin          #+#    #+#             */
/*   Updated: 2024/09/30 14:10:58 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	cmd_env(t_data *data, t_token_node *node)
{
	t_env	*env;

	env = data->env;
	if (!node->next)
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->key, env->value);
			env = env->next;
		}
	}
	*get_exit_status() = 0;
}
