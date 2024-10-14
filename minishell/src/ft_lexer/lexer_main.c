/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcevik <kcevik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:26:37 by erasahin          #+#    #+#             */
/*   Updated: 2024/10/03 18:35:27 by kcevik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"
#include "../../includes/minishell.h"
#include "../../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>

int	handle_special_char(char *input, int *i, t_token_node **token_list)
{
	t_token_node	*token;

	token = NULL;
	if (input[*i] == '<' && input[*i + 1] == '<')
	{
		token = create_token(HEREDOC, "<<");
		(*i)++;
	}
	else if (input[*i] == '>' && input[*i + 1] == '>')
	{
		token = create_token(APPEND, ">>");
		(*i)++;
	}
	else if (input[*i] == '<')
		token = create_token(REDIRECT_IN, "<");
	else if (input[*i] == '>')
		token = create_token(REDIRECT_OUT, ">");
	else if (input[*i] == '|')
		token = create_token(PIPE, "|");
	else if (input[*i] == ' ')
	{
		token = create_token(WHITESPACE, " ");
		while (input[*i] == ' ')
			(*i)++;
		*i -= 2;
	}
	if (token)
		add_token_to_list(token_list, token);
	(*i)++;
	return (1);
}

void	token_word(char *input, int *i, t_token_node **token_list)
{
	int				start;
	char			*word;
	t_token_node	*token;

	start = *i;
	while (input[*i] && !ft_isspace((unsigned char)input[*i])
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '|'
		&& input[*i] != '\'' && input[*i] != '\"' && input[*i] != '$')
	{
		(*i)++;
	}
	word = ft_strdup(input + start);
	word[*i - start] = '\0';
	token = create_token(WORD, word);
	garbage_collecter(word);
	add_token_to_list(token_list, token);
	if (input[*i] == ' ')
		handle_special_char(input, i, token_list);
}

int	check_token(char *input, int *i, t_token_node **token_list)
{
	t_token_node	*token;

	if (ft_strchr("<>|", input[*i]))
	{
		if (!handle_special_char(input, i, token_list))
			return (1);
	}
	else if (input[*i] == '\'')
	{
		token = single_quote(input, i);
		if (token)
		{
			add_token_to_list(token_list, token);
			if (input[*i] == ' ')
				if (!handle_special_char(input, i, token_list))
					return (1);
		}
	}
	else if (input[*i] == '\"')
	{
		(*i)++;
		double_quote(input, i, token_list);
		if (input[*i] == ' ')
			if (!handle_special_char(input, i, token_list))
				return (1);
	}
	else if (input[*i] == '$')
	{
		token = handle_env_variable(input, i, token_list);
		if (token)
		{
			add_token_to_list(token_list, token);
			if (input[*i] == ' ')
				if (!handle_special_char(input, i, token_list))
					return (1);
		}
	}
	return (0);
}

int	ft_lexer(char *input, t_data *data)
{
	int				i;
	t_token_node	*token_list;

	token_list = NULL;
	i = 0;
	while (input[i] == ' ')
		i++;
	while (input[i])
	{
		if (input[i] == ' ')
			i++;
		else if (ft_strchr("$<>'\"|", input[i]))
		{
			if (check_token(input, &i, &token_list))
				return (1);
		}
		else if (input[i])
			token_word(input, &i, &token_list);
	}
	if (token_list == NULL)
		return (1);
	if (handle_syntax_error(token_list))
		return (0);
	print_token_node_list(token_list);
	data->token = token_list;
	return (0);
}
