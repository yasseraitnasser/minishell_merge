
#include "../minishell.h"

int case_input(t_line_splited *head, int *outfile, int* infile)
{
    if(*infile != 0)
        close(*infile);
    *infile = open(head->redirection->file_limiter, O_RDONLY, 0744);
    if(*infile == -1 )
    {
        while(head->redirection)
        {
            if(head->redirection->redirection_type == 2)//input heredoc
                *infile = open_heredoc(head->redirection);
            head->redirection = head->redirection->next;
            unlink("heredoc");
        }
        perror(NULL); //add filename like bash
        if(*outfile != 1)
            close(*outfile);
        return(-1);
    }
    return(0);
}

int case_heredoc(t_line_splited *head, int *infile)
{
    int fd;

    if(*infile != 0)
        close(*infile);           
    *infile = open_heredoc(head->redirection);
    if(*infile == -1)
    {
        perror(NULL); //add filename like bash
        return(-1);
    }
    close(*infile);
    fd = open("heredoc", O_RDWR, 0744);
    if(fd == -1)
        return(-1);
    return(0);
}

int case_normal_output(t_line_splited *head, int *outfile)
{
    if(*outfile != 1)
        close(*outfile);
    *outfile = open(head->redirection->file_limiter, O_CREAT | O_RDWR | O_TRUNC, 0744);
    if(*outfile == -1)
    {
        perror(NULL); //add filename like bash
        return(-1);
    }
    return(0);
}

int case_append_output(t_line_splited *head, int *outfile)
{
    if(*outfile != 1)
        close(*outfile);
    *outfile = open(head->redirection->file_limiter, O_CREAT | O_RDWR | O_APPEND, 0744);
    if(*outfile == -1)
    {
        perror(NULL); //add filefile_limiter like bash
        return(-1);
    }
    return(0);
}

//if there is input file without < then others with it we take that first
int parse_files(t_line_splited *head, int *outfile, int *infile)
{
    while(head->redirection)
    {
        if(head->redirection->redirection_type == 1)//unput
        {
            if(case_input(head, outfile, infile) == -1)
                return(-1);
        }
        else if(head->redirection->redirection_type == 2)//input heredoc
        {
            if(case_heredoc(head, infile) == -1)
                return(-1);
        }
        else if(head->redirection->redirection_type == 3)//output
        {
            if(case_normal_output(head, outfile) == -1)
                return(-1);
        }
        else if(head->redirection->redirection_type == 4)//output append
        {
            if(case_append_output(head, outfile) == -1)
                return(-1);
        }
        head->redirection = head->redirection->next;
    }
    return(0);
}
