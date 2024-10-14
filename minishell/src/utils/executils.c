#include "../../includes/minishell.h"

t_token_node	*args_to_token(char **args)
{
	t_token_node	*token;
	int		i;

	i = -1;
	token = NULL;
	while (args[++i])
		add_token_to_list(&token, create_token( WORD,args[i]));
	return (token);
}

int	my_builtin(t_data *data, char **args)
{
	t_token_node	*node;

	if (args)
	{
		node = args_to_token(args);
		if (!ft_strcmp(args[0], "cd"))
			return (cmd_cd(data, node->next, NULL, NULL), 1);
		else if (!ft_strcmp(args[0], "pwd"))
			return (cmd_pwd(), 1);
		else if (!is_echo(args[0], "echo"))
			return (cmd_echo(node->next), 1);
		else if (!ft_strcmp(args[0], "env"))
			return (cmd_env(data, node), 1);
		else if (!ft_strcmp(args[0], "export"))
			return (cmd_export(data, node->next), 1);
		else if (!ft_strcmp(args[0], "unset"))
			return (cmd_unset(data, node->next), 1);
		else if (!ft_strcmp(args[0], "exit"))
			return (cmd_exit(node->next), 1);
	}
	return (0);
}
