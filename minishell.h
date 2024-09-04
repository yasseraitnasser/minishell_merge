#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

extern char **environ;

typedef struct  s_redirection
{
    int redirection_type;
    char *file_limiter;
    struct  s_redirection *next;
} t_redirection;

typedef struct s_line_splited
{
    char    **cmd;
    char    **env;
    t_redirection   *redirection;
    struct s_line_splited *next;
}   t_line_splited;

// set pwd every time 
typedef struct env_track
{
    char **myenv;
    char *pwd;
} t_env_track;


typedef struct Pipe_track
{
    int **fd;
    int i;
    int nb_pipes;
    int cmd_type;
    char *path_variable;
} t_pipe_track;

//parsing
int		parsing(char *line, t_line_splited **head, char **env);
void	display_and_free(t_line_splited *head, char **env);
void	replace_spaces_with_space(char *str);
void	skip_until_find_match(char **str, char c);
int		quote_is_not_closed(char *line);
int		something_is_wrong(char *line);
int		with_pipes(char *line);
int		check_what_is_next(char *str);
int		with_redirections(char *line);
int		redirection_handler(char **str, char c);
char	**ft_split_quotes(char *s, char c);
void	free_matrix(char **line_splited);
void	set_up_for_execution(t_line_splited **head, char *line);
void	*safe_malloc(size_t size);
void	skip_until_find_match_index_version(char *str, int *i, char c);
void	copy_until_find_match(char **str, char c, char *dest, int *index);
// char	*ft_strdup(const char *s1);
void	ft_lstadd_line_splited(t_line_splited **lst, t_line_splited *new);
void	ft_lstadd_redirection(t_redirection **lst, t_redirection *new);
void	ft_extract_redirections_cmd(t_line_splited *empty_node, char *str);
void	redirection_output(char *tmp, t_line_splited *empty_node);
void	redirection_input(char *tmp, t_line_splited *empty_node);
void	fill_up_blank(t_line_splited *empty, int redirection_t, char *tmp);
char	*get_file_limiter(char *tmp);
void	copy_and_blank(char **str, char c, char *dest, int *index);
int		file_limiter_size(char *tmp);
// size_t	ft_strlen(const char *s);
void	free_everything(t_line_splited *head);
void	clean_each_node(t_line_splited *node);
void	free_redirection_list(t_redirection *head);
void	free_line_splited_list(t_line_splited *head);
void	display(t_line_splited *head);
void	expand_rm_quotes(t_line_splited **head, char **env);
void	expand_cmd(char **cmd, char **env);
void	clean_cmd(char **cmd, int index, char **env);
void	single_quotes_handler(char **tmp, char *new, int *i);
void	double_quotes_handler(char **tmp, char **new, int *i, char **env);
void	found_ds_inside_dq(char **tmp, char **new, int *i, char **env);
char	*search_for_value(char *key, char **env);
int		is_alphanumeric(char c);
char	*ft_strjoin_pro(char *s1, char *s2, char *s3);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

//execution 
int list_size(t_line_splited *param);
int ft_strcmp(char *str1, char *str2);
int ft_strncmp(char *str1, char *str2, int n);
char **ft_split(char *str,char c);
int ft_strchr(char *str, char c);
char* return_value(char *full_var);
int check_if_valid(char *new_var, int size, int added);

void ft_putstr(char *str, int fd);
int ft_strlen(char *str);
char *ft_join(char *str1, char *str2);
char *ft_strdup(char *str);
// void free_matrix(char **str);
int check_if_append(char *new_var);
int check_if_add_change_append(t_line_splited *par,char *new_var, int max, int *count);
char **handle_variables(t_line_splited *par);
char *return_key(char* str);
int count_new_variables(t_line_splited *par, int size);
char *to_append(char *str);
char **create_copy(char **str, int *size);
int size_env(char **env);
void loop(t_line_splited *par, int size_env, char **export, char **cpy_env);
char **sort_env(t_line_splited *par, char **export);
void add_var_if_not_exist(char *new_var, int size, int added, int check);
int check_if_var_reapeated(t_line_splited *par, char *new_var);
void ft_putstr_exp(char *str, int fd);
char *add_non_existing_append_var(char *new_var);
void change_or_append_var_value(char *new_var, int check);
void change_value(char *new_var, int i);
void append_value(char *new_var, int i);
char *ft_strncpy(char *str1, char *str2, int n);
char	*get_next_line(int fd);
char	*ft_strcpy(char *dest, const char *src);
char	*free_and_join(char **reserve, char *buff);
int search_cmd(char *cmd, char **path_variable);
void child_process(t_line_splited* par, int infile, int outfile, char *path_variable);
void redirect_cmd(t_line_splited *par, int type, int outfile);
int cmdType(t_line_splited *par);
void ft_echo(t_line_splited *par, int fd);
void ft_env(int fd);
void ft_pwd(int fd);
void ft_unset(t_line_splited *par);
void ft_cd(t_line_splited *par, int output);
void ft_exit();
void ft_export(t_line_splited *par, int foutput);
void allocate_array(t_pipe_track *p);
int parse_files(t_line_splited *par, int *outfile, int *infile);
char	*ft_strchrr(char *s, int c);
int		ft_strncmpp(char *s1, char *s2, unsigned int n);
void execution(t_line_splited *par);
void free_all(t_pipe_track * p_track);
//handle_errors
void free_array(t_pipe_track *p);
int open_heredoc(t_redirection *file);
void close_all(t_pipe_track *p);
void open_pipes(t_pipe_track *p, t_line_splited *head);
void case_failed_parsing_files(t_pipe_track *p_track, t_line_splited **par);
void case_middle_built_in(t_line_splited *par, int infile, int outfile, t_pipe_track *p_track);
void case_middle_executable(t_line_splited *par, int infile, int outfile, t_pipe_track *p_track, char *path_variable);
void case_middle(t_line_splited *par, t_pipe_track *p_track, int infile, int outfile);
void case_last(t_line_splited *par, t_pipe_track *p_track, int infile, int outfile);

#endif
