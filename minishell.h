/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-cha <mben-cha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 16:41:42 by ytlidi            #+#    #+#             */
/*   Updated: 2025/07/27 16:05:56 by mben-cha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <termios.h>
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
	int						is_delimiter_quoted;
	char					*filename_or_delimiter;
	int						heredoc_fd;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		*rds;
	int					pipe_in;
	int					pipe_out; 
	struct s_command	*next;
}	t_command;

typedef struct s_arg_word
{
	char	*str;
	int		expanded;
}	t_arg_word;

typedef struct s_parsing
{
	int			j;
	char		*str;
	int			i;
	int			flag;
	int			k;
	t_arg_word	*new_str;
}	t_parsing;

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

typedef struct s_fd_backup
{
    int saved_stdin;
	int	saved_stdout;
	int	has_redirection;
}   t_fd_backup;

typedef struct s_hdpart
{
    char *str;
    int should_expand;
    struct s_hdpart *next;
}	t_hdpart;



t_token			*ft_lstnew_token(char *token);
t_command		*ft_lstnew_command(char **args);
t_redirection	*ft_lstnew_redirection(int type, char *file);
void			ft_lstadd_back_token(t_token **lst, t_token *new);
void			ft_lstadd_back_command(t_command **lst, t_command *new);
void			ft_lstadd_back_redirection(t_redirection ***lst, t_redirection *new);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strdup(char *src);
t_command		*parse_input(char *str, t_env *env, t_shell *shell);
size_t			ft_strlen(const char *s);
char			**ft_split(char const *s, char c);
char			*ft_strjoin_with(char const *s1, char const *s2, char sep);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				valid_tokens(t_token *head, t_shell *shell);
int				check_fail(int result, char *msg);
int				setup_redirections(int type, char *filename);
int				execute(t_command *cmd_list, t_env *env, t_shell *shell);
int				ft_strcmp(const char *s1, const char *s2);
t_env			*ft_lstnew(char *key, char *value);
void			ft_lstadd_back(t_env **env, t_env *new);
int				print_getcwd_error(char *cmd_name);
int				print_chdir_error(char *path);
void			add_env(t_env **env, char *key, char *value);
void			print_shlvl_too_high_error(char *shlvl);
int				print_export_error(char *identifier);
t_env			*find_env(t_env *env, char *key);
int				update_env(t_env *env, char *key, char *new_value);
void			print_exit_error(char *arg);
int				setup_pipe(int *pipefd);
t_env			*init_env(char **envp);
int				ft_strcmp_exp(char *s1, char *s2);
int				strlen_before_spaces_or_delimiter(char *str);
int				inner_word_or_quote_skipping_condition(char *str, int i, int flag, int type);
void			inner_word_or_quote_skipping(char *str, int *i, int *flag, char *q);
int				add_token_string_to_token_list(char *str, int i, int j, t_token **list);
void			filling_type_pipe_or_rd(t_token *list);
void			filling_type_s_or_d_quote(t_token *list);
void			expanding(char *new_str, int *j, char *str_to_add);
int				in_case_of_quote_not_closed(char *new_str, int j, int flag);
void			filling_type_pipe_or_rd(t_token *list);
int				inner_pipes_and_rds_tokens(char *str, t_token **list, int *i, int s_or_d);
int				quote_tokens(char *str, t_token **list, int *i);
int				pipes_and_rds_tokens(char *str, t_token **list, int *i);
int				word_tokens(char *str, t_token **list, int *i);
int				words_count(t_token *beginning);
char			*resolve_command_path(t_command *cmd, t_env *env, t_shell *shell);
int				print_cmd_error(char *cmd, char *msg, int exit_code);
void			ft_putstr_fd(char *s, int fd);
int				env_size(t_env *env);
char			**env_to_array(t_env *env);
int				check_builtin(t_command *comd);
int				execute_builtin(t_command *cmd, t_env *env_list, t_shell *shell);
int				cd(char *path, t_env **env, t_shell *shell);
int				echo(char **args, t_shell *shell);
int				env(t_env *env, t_shell *shell);
int				do_exit(t_command *cmd, t_shell *shell);
int				export(t_env **env, char **args, t_shell *shell);
int				pwd(t_shell *shell);
int				unset(t_env **env, char **args, t_shell *shell);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
void			free_split(char **array);
void			quick_sort_env(t_env **array, int low, int high);
t_env			**get_sorted_env_ptr_array(t_env *env_list);
int				restore_stdio(int saved_stdin, int saved_stdout);
t_fd_backup		*handle_redirections(t_command *cmd);
int				ft_atoi(const char *str);
char			*ft_itoa(int n);
void			prompt_sigint_handler(int sig);
int				set_signal(int signo, void (*handler)(int));
void			remove_quote_func_init(t_parsing *parsing, t_token *token, t_env *env);
int				skipping_if_quote_mark(t_parsing *parsing, char *q);
int				expand_condition(t_parsing *parsing, char q);
int				printing_dollar(t_parsing *parsing, t_env *env_line);
int				expand_to_last_exit_status(t_parsing *parsing, t_shell *shell);
t_env			*find_env_exp(t_env *env, t_parsing *parsing, int i);
int				expand_to_an_empty_string(t_parsing *parsing, t_env *env_line);
int				expand_to_a_real_value(t_parsing *parsing, t_env *env_line);
int				remove_quote_inner_loop(t_token *token, t_env *env, t_shell *shell, t_parsing *parsing);
int				calc_new_str_len(t_parsing *parsing, t_env *env);
char			*ft_strjoin(char const *s1, char const *s2);
int				is_quoted(char *token);
char			*heredoc_expand_line(t_env *env, char *line, t_shell *shell);
void			disable_echoctl(void);
void			restore_termios(void);
void			free_cmd_list(t_command *cmd_list);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			free_list(t_token *list);
