#include "../minishell.h"

//pay attention to leak join
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

void close_all(t_pipe_track *p)
{
    int i;

    i = 0;
    if(p->nb_pipes == 0)
        return;
    while(i < p->nb_pipes - 1)
    {
        close(p->fd[i][0]);
        close(p->fd[i][1]);
        i++;
    }
}

void    close_previous_pipes_and_free(t_pipe_track *p, int i)
{
    int j;

    j = 0;
    while (j < i)
    {
        close(p->fd[i][0]);
        close(p->fd[i][1]);
        free(p->fd[i]);
        j++;
    }
    free(p->fd);
    free(p);
}

void open_pipes(t_pipe_track *p, t_line_splited *head)
{
    int i;
    
    i = 0;
    while(i != p->nb_pipes)
    {
        if(pipe(p->fd[i]) == -1)
        {
            free_everything(head);
            close_previous_pipes_and_free(p, i);
            printf("pipe failed\n");
            exit(-1);
        }
        i++;
    }
}
