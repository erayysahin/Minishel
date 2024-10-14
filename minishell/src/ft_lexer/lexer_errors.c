/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:17:41 by erasahin          #+#    #+#             */
/*   Updated: 2024/08/29 13:32:20 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include <stdio.h>

int	handle_syntax_error(t_token_node *head)
{
	while (head)
	{
		if (is_redir(head))
		{
			if (!head->next)
			{
				printf("syntax error near unexpected token newline'\n");
				return (1);
			}
			else if ((is_redir(head->next) || head->next->type == PIPE))
			{
				printf("syntax error near unexpected token ");
				printf("%s'\n", head->next->value);
				return (1);
			}
		}
		else if (head->type == PIPE && (!head->prev || !head->next))
		{
			printf("syntax error near unexpected token %s'\n", head->value);
			return (1);
		}
		head = head->next;
	}
	return (0);
}
