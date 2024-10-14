#ifndef LEXER_H
# define LEXER_H

# include "../libft/libft.h"

typedef enum e_tokens
{
	WORD,
	WHITESPACE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND,
	PIPE,
	ENV_VARIABLE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
}						t_token_nodes;

typedef struct s_token_node
{
	char				*value;
	t_token_nodes		type;
	struct s_token_node	*next;
	struct s_token_node	*prev;
}						t_token_node;

void					print_token_node_list(t_token_node *head);
t_token_node			*create_token(t_token_nodes type, char *value);
t_token_node			*handle_env_variable(char *input, int *i,
							t_token_node **token_list);
t_token_node			*single_quote(char *input, int *i);
void					double_quote(char *input, int *i,
							t_token_node **token_list);

void					add_token_to_list(t_token_node **head,
							t_token_node *token);
void					token_word(char *input, int *i,
							t_token_node **token_list);
int						handle_special_char(char *input, int *i,
							t_token_node **token_list);
int						check_token(char *input, int *i,
							t_token_node **token_list);

char					*ft_strdup(const char *s1);
char					*ft_strchr(const char *s, int c);
int						handle_syntax_error(t_token_node *head);

int						is_args(t_token_node *node);
int						is_redir(t_token_node *node);

#endif
