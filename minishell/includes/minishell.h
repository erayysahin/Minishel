#ifndef MINISHELL_H
# define MINISHELL_H
# include "lexer.h"
# include <stdio.h>

# define PROMT_SIG 0
# define HEREDOC_SIG 0
# define EXEC_SIG 0

typedef struct s_malloc
{
	void			*ptr;
	struct s_malloc	*next;
}					t_malloc;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env			*env;
	t_malloc		*malloc;
	t_token_node	*token;
	char			*cmd;
	int				in_fd;
	int				pid;
	int				pipes;
	int				here;
}					t_data;

int					ft_lexer(char *input, t_data *data);
void				print_error(t_token_node *node, char *str, int exit_status);
char				**get_command_args(t_token_node *node);
void				create_env(char **env, t_data *data);
void				gc_free(void);
void				ft_exit(char *str);
void				ft_expender(t_data *data, t_token_node *node, char *tmp);
t_env				*get_env(t_data *data, char *key);
void				handle_child_process(t_data *data, t_token_node *node,
						int pipfd[2], char **env);
t_malloc			*get_garbage_c(void);
void				*gc_malloc(unsigned int size);
void				garbage_collecter(void *ptr);
void				garbage_collecter_token(t_data *data);
void				env_veriable(t_data *data);
void				expander(t_data *data);
void				add_garbage_c(void *ptr);
int					cmd_check(t_token_node *node);
void				update_oldpwd(t_data *data, char *pwd);
void				cmd_cd(t_data *data, t_token_node *node, char *path,
						char *pwd);
char				*finding_path(t_data *data, t_token_node *node);
int					is_echo(char *str1, char *str2);
void				cmd_echo(t_token_node *node);
void				cmd_env(t_data *data, t_token_node *node);
void				cmd_exit(t_token_node *node);
void				update_exit_status(void);
void				cmd_export(t_data *data, t_token_node *node);
int					builtins(char *path);
int					is_path(char *str);
t_env				*get_pwd(t_data *data);
void				cmd_pwd(void);
int					check_valid_key(char *key, t_token_node *node);
void				cmd_unset(t_data *data, t_token_node *node);
void				parser(t_data *data);
int					*get_exit_status(void);
int					skip_space(char *str, int i);
char				**env_to_char(t_data *data, int i);
void				signal_base(void);
t_token_node		*handle_parent_process(t_data *data, int pipfd[2],
						t_token_node *node);
void				qute_env(char *input, int *i, t_token_node **token_list,
						int start);
int					*get_signal(void);
void				close_and_zero(t_data *data, int pipfd[2]);
int					my_builtin(t_data *data, char **args);
void				handle_redirection(t_token_node *node, t_data *data);
void				setup_pipes(t_data *data, t_token_node *node, int pipfd[2]);
void				handle_signal(int signo);

#endif
