/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erasahin <erasahin@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:31:04 by erasahin          #+#    #+#             */
/*   Updated: 2024/10/04 14:32:51 by erasahin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_token_node	*handle_env_variable(char *input, int *i, t_token_node **node)
{
	int		start;
	char	*var_name;

	start = *i;
	if ((!ft_isalnum(input[*i + 1]) && input[*i + 1] != '_' && input[*i
			+ 1] != '?'))
		return (token_word(input, i, node), NULL);
	(*i)++;
	if (input[*i] == '?')
		(*i)++;
	else if (ft_isdigit(input[*i]) && input[*i] != '_')
	{
		(*i)++;
		return (NULL);
	}
	else
		while (ft_isalnum(input[*i]) || input[*i] == '_')
			(*i)++;
	var_name = ft_substr(input, start, *i - start);
	add_garbage_c(var_name);
	return (create_token(ENV_VARIABLE, var_name));
}

t_token_node	*single_quote(char *input, int *i)
{
	int				start;
	char			*var_name;
	t_token_node	*token;

	(*i)++;
	start = *i;
	while (input[*i] != '\'' && input[*i] != '\0')
		(*i)++;
	if (input[*i] == '\0')
	{
		printf("Error: Unmatched single quote\n");
		return (NULL);
	}
	var_name = ft_strdup(input + start);
	add_garbage_c(var_name);
	var_name[*i - start] = '\0';
	token = create_token(SINGLE_QUOTE, var_name);
	(*i)++;
	garbage_collecter(var_name);
	return (token);
}

void	qute_env(char *input, int *i, t_token_node **token_list, int start)
{
	char			*var_name;
	t_token_node	*token;

	var_name = ft_substr(input, start, *i - start);
	add_garbage_c(var_name);
	token = create_token(DOUBLE_QUOTE, var_name);
	add_token_to_list(token_list, token);
	if (input[*i] == '$')
	{
		token = handle_env_variable(input, i, token_list);
		if (token)
			add_token_to_list(token_list, token);
	}
	start = *i;
	garbage_collecter(var_name);
}

void	double_quote(char *input, int *i, t_token_node **token_list)
{
	int				start;
	
	start = *i;
	while (input[*i] != '\"' && input[*i] != '\0')
	{
		if (input[*i] == '$')
		{
			qute_env(input, i, token_list, start);
			start = *i;
		}
		else
			(*i)++;
	}
	if (input[*i] == '\0')
	{
		printf("Error: Unmatched double quote\n");
		return ;
	}
	qute_env(input, i, token_list, start);
	(*i)++;
}
