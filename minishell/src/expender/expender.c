#include "../../includes/minishell.h"

void	ft_expender(t_data *data, t_token_node *node, char *tmp)
{
	t_env	*tmp_data;

	node->value++;
	tmp_data = data->env;
	while (tmp_data && tmp_data->value)
	{
		if (node->value && tmp_data->key && (ft_strcmp(node->value,
					tmp_data->key) == 0))
		{
			garbage_collecter(node->value);
			tmp = tmp_data->value;
			node->value = ft_strdup(tmp);
			add_garbage_c(node->value);
			break ;
		}
		else if (!tmp_data->next)
		{
			garbage_collecter(node->value);
			node->value = ft_strdup("");
			add_garbage_c(node->value);
			break ;
		}
		tmp_data = tmp_data->next;
	}
	garbage_collecter(tmp_data);
}

void	expander(t_data *data)
{
	t_token_node	*node;
	int				hedir;

	hedir = 0;
	node = data->token;
	while (node)
	{
		if (node->type == HEREDOC)
		{
			node = node->next;
			hedir = 1;
			continue ;
		}
		if (node->type == ENV_VARIABLE && !hedir)
			ft_expender(data, node, NULL);
		node = node->next;
	}
}
