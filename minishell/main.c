/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:07:36 by erasahin          #+#    #+#             */
/*   Updated: 2024/10/04 16:18:31 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>

void	initilazor(t_data *data)
{
	data->env = gc_malloc(sizeof(t_env));
	data->token = NULL;
	data->cmd = 0;
	data->in_fd = 0;
	data->pid = 0;
	data->pipes = 0;
	data->here = 0;
}

void	create_env(char **envp, t_data *data)
{
	t_env	*node;
	int		i;
	char	*tmp;

	i = -1;
	node = data->env;
	while (envp[++i])
	{
		tmp = ft_strchr(envp[i], '=');
		data->env->key = ft_substr(envp[i], 0, tmp - envp[i]);
		data->env->value = ft_substr(envp[i], (tmp - envp[i]) + 1,
				ft_strlen(envp[i]));
		add_garbage_c(data->env->key);
		add_garbage_c(data->env->value);
		if (envp[i + 1])
			data->env->next = gc_malloc(sizeof(t_env));
		data->env = data->env->next;
	}
	data->env = node;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	char	*line;

	(void)av;
	if (ac >= 2)
		return (0);
	signal(SIGINT, handle_signal);
	data.env = ft_calloc(1, sizeof(t_env));
	add_garbage_c(data.env);
	initilazor(&data);
	create_env(env, &data);
	while (1)
	{
		line = readline("althe-3.2$ ");
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			ft_lexer(line, &data);
		}
		if (data.token)
		{
			expander(&data);
			print_token_node_list(data.token);
			parser(&data);
		}
		free(line);
		garbage_collecter_token(&data);
	}
	return (0);
}
