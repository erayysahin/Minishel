/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:31:59 by erasahin          #+#    #+#             */
/*   Updated: 2024/10/02 15:42:49 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

t_token_node	*create_token(t_token_nodes type, char *value)
{
	t_token_node	*token;

	token = (t_token_node *)gc_malloc(sizeof(t_token_node));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	add_garbage_c(token->value);
	return (token);
}

void	add_token_to_list(t_token_node **token_list, t_token_node *new_token)
{
	t_token_node	*new_node;
	t_token_node	*last;

	new_node = (t_token_node *)gc_malloc(sizeof(t_token_node));
	if (!new_node)
		return ;
	new_node = new_token;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (*token_list == NULL)
		*token_list = new_node;
	else
	{
		last = *token_list;
		while (last->next != NULL)
			last = last->next;
		last->next = new_node;
		new_node->prev = last;
	}
}

void	print_token_node_list(t_token_node *head)
{
	while (head)
	{
		switch (head->type)
		{
		case WORD:
			printf("WORD :%s\n", head->value);
			break ;
		case WHITESPACE:
			printf("SPACE :s%ss\n", head->value);
			break ;
		case REDIRECT_IN:
			printf("IN :%s\n", head->value);
			break ;
		case REDIRECT_OUT:
			printf("OUT :%s\n", head->value);
			break ;
		case PIPE:
			printf("PIPE :%s\n", head->value);
			break ;
		case ENV_VARIABLE:
			printf("ENV :%s\n", head->value);
			break ;
		case SINGLE_QUOTE:
			printf("SINGLE :%s\n", head->value);
			break ;
		case DOUBLE_QUOTE:
			printf("DUBLE :%s\n", head->value);
			break ;
		case HEREDOC:
			printf("HERE :%s\n", head->value);
			break ;
		case APPEND:
			printf("APPEND :%s\n", head->value);
			break ;
		default:
			printf("UNKNOWN TYPE");
			break ;
		}
		head = head->next;
	}
	printf("\n");
}

int	is_args(t_token_node *node)
{
	if (node->type == WHITESPACE)
		return (2);
	return (node->type == DOUBLE_QUOTE || node->type == SINGLE_QUOTE
		|| node->type == WORD || node->type == ENV_VARIABLE);
}

int	is_redir(t_token_node *node)
{
	if (node->type == HEREDOC)
		return (2);
	return (node->type == APPEND || node->type == REDIRECT_IN
		|| node->type == REDIRECT_OUT);
}
