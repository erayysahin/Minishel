/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 13:44:48 by kcevik            #+#    #+#             */
/*   Updated: 2024/10/04 16:26:32 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <unistd.h>

void	handle_heredoc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		ft_exit(strerror(errno));
	*get_signal() = HEREDOC_SIG;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		add_garbage_c(line);
	}
	close(fd);
}
void	rdir_dup(int fd, int std, t_token_node *node)
{
	if (fd == -1)
	{
		print_error(node, ": No such file or directory\n", 1);
		ft_exit(NULL);
	}
	dup2(fd, std);
	close(fd);
}
void	exec_heredoc(t_token_node *node)
{
	while (node)
	{
		if (node->type == HEREDOC)
			handle_heredoc(node->next->value);
		node = node->next;
	}
}
int	permission_check(t_token_node *node)
{
	if (is_redir(node) == 1)
	{
		if (access(node->next->value, F_OK) == 0)
		{
			if (access(node->next->value, W_OK) != 0)
			{
				print_error(node->next, ": Permission denied\n", 1);
				return (1);
			}
		}
	}
	return (0);
}
void	handle_redirection(t_token_node *node, t_data *data)
{
	if (data->here)
		exec_heredoc(node);
	*get_signal() = EXEC_SIG;
	while (node && (is_redir(node) || is_args(node)))
	{
		if (permission_check(node))
			ft_exit(NULL);
		if (node->type == REDIRECT_OUT)
			rdir_dup(open(node->next->value, O_WRONLY | O_CREAT | O_TRUNC,
					0644), STDOUT_FILENO, node->next);
		else if (node->type == APPEND)
			rdir_dup(open(node->next->value, O_WRONLY | O_CREAT | O_APPEND,
					0644), STDOUT_FILENO, node->next);
		else if (node->type == REDIRECT_IN)
			rdir_dup(open(node->next->value, O_RDONLY), STDIN_FILENO,
				node->next);
		else if (node->type == HEREDOC)
			rdir_dup(open("/tmp/.heredoc_tmp", O_RDONLY), STDIN_FILENO,
				node->next);
		node = node->next;
	}
}
