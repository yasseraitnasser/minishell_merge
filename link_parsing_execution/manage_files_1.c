#include "../minishell.h"

int open_heredoc(t_redirection *file)
{
    int fd;
    char *str;

    file->file_limiter = ft_join(file->file_limiter, "\n");
    fd = open("heredoc", O_CREAT | O_TRUNC | O_RDWR, 0644);
    if(fd == -1)
    {
        perror(NULL);
        return(-1);
    }
    while(1)
    {
        str = get_next_line(STDIN_FILENO);
        if(ft_strcmp(str, file->file_limiter) == 0 || str == NULL)
        {
            free(str);
            free(file->file_limiter);
            return(fd);
        }
        ft_putstr(str, fd);
        free(str);
    }
    return(fd);
}

void close_all(t_cmd_track *c_track)
{
    int i;

    i = 0;
    if(c_track->nb_pipes == 0)
        return;
    while(i < c_track->nb_pipes - 1)
    {
        close(c_track->fd[i][0]);
        close(c_track->fd[i][1]);
        i++;
    }
}

int open_pipes(t_cmd_track *c_track)
{
    int i;
    
    i = 0;
    while(i != c_track->nb_pipes)
    {
        if(pipe(c_track->fd[i]) == -1)
        {
            printf("error in while opening a pipe\n");
            c_track->exit_value = -1;
            return(-1);       
        }
        i++;
    }
    return(0);    
}
