/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:01:25 by erasahin          #+#    #+#             */
/*   Updated: 2024/10/02 15:36:06 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <unistd.h>

void	update_oldpwd(t_data *data, char *pwd)
{
	t_env	*node;

	node = get_env(data, "OLDPWD");
	if (!node)
	{
		node = gc_malloc(sizeof(t_env));
		node->key = "OLDPWD";
		node->value = pwd;
		node->next = data->env;
		data->env = node;
	}
	else
		node->value = pwd;
}

char	*handle_cd_command(t_data *data, t_token_node *node, char *path)
{
	t_env	*env;

	env = get_env(data, "HOME");
	if (node && is_args(node))
		path = node->value;
	else if (!node && env)
		path = env->value;
	else
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		*get_exit_status() = 1;
		return (0);
	}
	return (path);
}

void	cmd_cd(t_data *data, t_token_node *node, char *path, char *pwd)
{
	if (node)
		node = node->next;
	path = handle_cd_command(data, node, path);
	if (path == 0)
		return ;
	pwd = get_pwd(data)->value;
	if (chdir(path) == -1)
		print_error(node, ": No such file or directory\n", 1);
	else
	{
		update_oldpwd(data, pwd);
		get_pwd(data)->value = getcwd(NULL, 0);
		if (!get_pwd(data)->value)
			perror("minishell");
		add_garbage_c(get_pwd(data)->value);
		*get_exit_status() = 0;
	}
}
