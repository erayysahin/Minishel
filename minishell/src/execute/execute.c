/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:39:22 by kcevik            #+#    #+#             */
/*   Updated: 2024/10/03 15:59:36 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

t_env	*get_env(t_data *data, char *key)
{
	t_env	*node;

	node = data->env;
	while (node)
	{
		if (!ft_strcmp(node->key, key))
			return (node);
		node = node->next;
	}
	return (NULL);
}

char	*path_while(char **path, t_token_node *node)
{
	char	*tmp;
	int		i;

	i = -1;
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		add_garbage_c(tmp);
		free(path[i]);
		path[i] = ft_strjoin(tmp, node->value);
		add_garbage_c(path[i]);
		garbage_collecter(tmp);
		if (!access(path[i], F_OK))
		{
			if (!access(path[i], X_OK))
				return (path[i]);
			else
				return (NULL);
		}
	}
	return (NULL);
}

int	is_directory(char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (0);
	return (S_ISDIR(path_stat.st_mode));
}

char	*handle_executable_file(t_token_node *node, char *path)
{
	char	*tmp;

	if (is_directory(path))
	{
		print_error(node, ": is a directory\n", 126);
		return (NULL);
	}
	else if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			tmp = ft_strdup(path);
			add_garbage_c(tmp);
			return (tmp);
		}
		print_error(node, ": Permission denied\n", 126);
		return (NULL);
	}
	print_error(node, ": No such file or directory\n", 127);
	return (NULL);
}
int	is_path(char *str)
{
	return ((str[0] == '.' && str[1] == '/') || str[0] == '/');
}

char	*finding_path(t_data *data, t_token_node *node)
{
	t_env	*env;
	char	**path;
	
	if (!node)
		return (NULL);
	if (!(*node->value))
		return (print_error(data->token, ": command not found\n", 127), NULL);
	if (builtins(node->value))
		return (NULL);
	if (is_path(node->value))
		return (handle_executable_file(node, node->value));
	env = get_env(data, "PATH");
	if (!env)
	{
		return (NULL);
	}
	path = ft_split(env->value, ':');
	add_garbage_c(path);
	return (path_while(path, node));
}

int	how_much_cmd(t_data *data)
{
	t_token_node	*node;

	node = data->token;
	if ((is_args(node) && !node->next))
		return (1);
	else
	{
		while (node)
		{
			if (node->type == PIPE || is_redir(node))
				return (0);
			node = node->next;
		}
		return (1);
	}
	return (0);
}

char	**env_to_char(t_data *data, int i)
{
	t_env	*node;
	char	**env;
	char	*tmp;

	node = data->env;
	while (++i, node)
		node = node->next;
	env = gc_malloc(sizeof(char *) * (i + 1));
	i = -1;
	node = data->env;
	while (++i, node->next)
	{
		tmp = ft_strjoin(node->key, "=");
		add_garbage_c(tmp);
		if (node->value)
		{
			env[i] = ft_strjoin(tmp, node->value);
			add_garbage_c(env[i]);
			garbage_collecter(tmp);
		}
		else
			env[i] = tmp;
		node = node->next;
	}
	return (env[i] = NULL, env);
}

char	**get_command_args(t_token_node *node)
{
	t_token_node	*tmp;
	char			**args;
	int				i;

	i = 0;
	tmp = node;
	while (tmp && (is_args(tmp) || is_redir(tmp) == 1))
	{
		if (is_args(tmp) == 1 && (!tmp->prev || (tmp->prev
					&& !is_redir(tmp->prev))))
			i++;
		tmp = tmp->next;
	}
	args = gc_malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (node && (is_args(node) || is_redir(node) == 1))
	{
		if (is_args(node) == 1 && (!node->prev || (node->prev
					&& !is_redir(node->prev))))
			args[i++] = node->value;
		node = node->next;
	}
	args[i] = NULL;
	return (args);
}

void	use_execve(t_data *data, t_token_node *node)
{
	pid_t	pid;
	char	**env;
	char	*path;
	char	**args;

	signal_base();
	env = env_to_char(data, -1);
	if (is_args(data->token))
	{
		path = finding_path(data, data->token);
		if (!path)
			return ;
		args = get_command_args(data->token);
		while (node->next && is_args(node->next))
			node = node->next;
		pid = fork();
		if (pid == 0)
			if (execve(path, args, env) == -1)
				return (exit(1), ft_putendl_fd("Execve failed", 2));
		waitpid(pid, get_exit_status(), 0);
		update_exit_status();
	}
}

void	pars_single_cmd(t_data *data)
{
	if (is_args(data->token))
	{
		while (data->token && *data->token->value == '\0'
			&& data->token->type == WORD)
			data->token = data->token->next;
		if (!data->token)
			return ;
		if (!ft_strcmp(data->token->value, "cd"))
			cmd_cd(data, data->token->next, NULL, NULL);
		else if (!ft_strcmp(data->token->value, "pwd"))
			cmd_pwd();
		else if (!ft_strcmp(data->token->value, "echo"))
			cmd_echo(data->token->next);
		else if (!ft_strcmp(data->token->value, "env"))
			cmd_env(data, data->token);
		else if (!ft_strcmp(data->token->value, "export"))
			cmd_export(data, data->token->next);
		else if (!ft_strcmp(data->token->value, "unset"))
			cmd_unset(data, data->token->next);
		else if (!ft_strcmp(data->token->value, "exit"))
			cmd_exit(data->token->next);
		else
			use_execve(data, data->token);
	}
}
// pipe
void	pars_multiple(t_data *data)
{
	t_token_node	*node;
	char			**env;
	int				pipfd[2];

	env = env_to_char(data, -1);
	node = data->token;
	while (node)
	{
		if (is_args(node) || is_redir(node))
		{
			if (data->pipes)
				if (pipe(pipfd) == -1)
					ft_exit(strerror(errno));
			data->pid = fork();
			if (data->pid == 0)
				handle_child_process(data, node, pipfd, env);
			else
				node = handle_parent_process(data, pipfd, node);
		}
		if (node)
			node = node->next;
	}
	while (wait(NULL) > 0)
		;
	close_and_zero(data, pipfd);
}
void	pars_multiple_cmd(t_data *data)
{
	t_token_node	*node;

	node = data->token;
	while (node)
	{
		if (is_redir(node) == 2)
			data->here = 1;
		if (node->type == PIPE)
			data->pipes = 1;
		node = node->next;
	}
	pars_multiple(data);
}

void	parser(t_data *data)
{
	if (how_much_cmd(data) == 1)
		pars_single_cmd(data);
	else
		pars_multiple_cmd(data);
}
