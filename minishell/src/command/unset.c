/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:21:13 by erasahin          #+#    #+#             */
/*   Updated: 2024/10/02 15:38:01 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_valid_key(char *key, t_token_node *node)
{
	int	i;

	i = 0;
	while (key[i] && ((ft_isalnum(key[i]) && !ft_isdigit(key[0]))
			|| key[i] == '_'))
		i++;
	if ((int)ft_strlen(key) != i)
		return (print_error(node, ": not a valid identifier\n", 1), 1);
	return (0);
}

void	unset_organizer(t_data *data, t_env *tmp)
{
	t_env	*prev;

	prev = data->env;
	if (tmp)
	{
		while (prev)
		{
			if (prev->next == tmp)
				break ;
			prev = prev->next;
		}
		if (prev)
			prev->next = tmp->next;
		else
			data->env = tmp->next;
	}
}

void	cmd_unset(t_data *data, t_token_node *node)
{
	t_env	*tmp;
	int		flag;

	flag = 0;
	if (node)
		node = node->next;
	while (node)
	{
		if (check_valid_key(node->value, node))
		{
			node = node->next;
			flag = 1;
			continue ;
		}
		tmp = get_env(data, node->value);
		unset_organizer(data, tmp);
		node = node->next;
	}
	*get_exit_status() = flag;
}
