/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytlidi <ytlidi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:41:42 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/06 12:48:46 by ytlidi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef enum s_tokens
{
	TOKEN_WORD,
	TOKEN_S_QUOTE,
	TOKEN_D_QUOTE,
	TOKEN_PIPE,
	TOKEN_RD_IN,
	TOKEN_RD_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_tokens;

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	int						type;
	char					*filename_or_delimiter;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		*rds;
	int					pipe_in;
	int					pipe_out; 
	int					heredoc_fd;
	struct s_command	*next;
	// struct s_command	*prev;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int	last_exit_status;
}	t_shell;

t_token			*ft_lstnew_token(char *token);
t_command		*ft_lstnew_command(char **args);
t_redirection	*ft_lstnew_redirection(int type, char *file);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			ft_lstadd_back_command(t_command **lst, t_command *new);
void			ft_lstadd_back_redirection(t_redirection ***lst, t_redirection *new);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(char *src);
t_command		*parse_input(char *str, t_env *env);
size_t			ft_strlen(const char *s);
char			**ft_split(char const *s, char c);
char			*ft_strjoin(char const *s1, char const *s2);
int				check_cmd(t_command *cmd);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				valid_tokens(t_token *head);
int				check_or_exit(int result, char *msg);
void			setup_redirections(int type, char *filename);
int				execute(t_command *cmd_list, char **envp);
int				ft_strcmp(const char *s1, const char *s2);
t_env			*ft_lstnew(char *key, char *value);
void			ft_lstadd_back(t_env **env, t_env *new);
void			free_split(char **array);
int				print_getcwd_error(char *cmd_name);
int				print_chdir_error(char *path);
void			add_env(t_env **env, char *key, char *value);
int				print_export_error(char *identifier);
t_env			*find_env(t_env *env, char *key);
int				update_env(t_env *env, char *key, char *new_value);
void			print_exit_error(char *arg);
int				setup_pipe(int *pipefd);
t_env			*init_env(char **envp);
int				ft_strcmp_exp(char *s1, char *s2);
t_env			*find_env_exp(t_env *env, char *key);
int				strlen_before_spaces_or_delimiter(char *str);
int				inner_word_or_quote_skipping_condition(char *str, int i, int flag, int type);
void			inner_word_or_quote_skipping(char *str, int *i, int *flag, char *q);
int				add_token_string_to_token_list(char *str, int i, int j, t_token **list);
void			filling_type_pipe_or_rd(t_token *list);
void			filling_type_s_or_d_quote(t_token *list);
int				printing_dollar(char *new_str, int *j, char *str, int *i);
int				expand_to_an_empty_string(char *str, int *i, t_env *env_line);
int				expand_to_a_real_value(char *new_str, int *j, int *i, t_env *env_line);
void			expanding(char *new_str, int *j, char *str_to_add);
int				skipping_if_quote_mark(char *str, int *i, int *flag, char *q);
char			*remove_quote_func_init(int *i, t_token *token, char **new_str, t_env *env);
int				calc_new_str_len(char *str, t_env *env);
int				expand_condition(char *str, int i, int flag, char q);
int				in_case_of_quote_not_closed(char *new_str, int j, int flag);
void			filling_type_pipe_or_rd(t_token *list);
int				inner_pipes_and_rds_tokens(char *str, t_token **list, int **i, int s_or_d);
int				quote_tokens(char *str, t_token **list, int *i);
int				pipes_and_rds_tokens(char *str, t_token **list, int *i);
int				word_tokens(char *str, t_token **list, int *i);
int				words_count(t_token *beginning);
int				calc_new_str_len(char *str, t_env *env);
