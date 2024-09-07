#include "../minishell.h"

void case_first_builtin(t_line_splited *head, int outfile, t_cmd_track *c_track)
{
    if(outfile == 1 && c_track->nb_pipes != 0)
        redirect_cmd(head, c_track->cmd_type, c_track->fd[c_track->i][1], c_track);
    else if(outfile == 1 && c_track->nb_pipes == 0)
        redirect_cmd(head, c_track->cmd_type, 1, c_track);
    else
        redirect_cmd(head, c_track->cmd_type, outfile, c_track);
}

void case_first_executable(t_line_splited *head, int infile, int outfile, t_cmd_track *p_track, char *path_variable)
{
    if(outfile == 1 && p_track->nb_pipes != 0)
        child_process(head, infile , p_track->fd[p_track->i][1], path_variable);
    else if(outfile == 1 && p_track->nb_pipes == 0)
        child_process(head, infile , 1, path_variable);
    else
        child_process(head, infile, outfile, path_variable);
}

void case_first(t_line_splited *head, t_cmd_track *c_track, int infile, int outfile)
{
    char *path_variable;

    path_variable = NULL;
    c_track->cmd_type = cmdType(head);
    if(c_track->cmd_type == 0)
    {
        if(search_cmd(head->cmd[0], &path_variable, c_track) == -1)
        {
            printf("i am exit satus %d\n", c_track->exit_value);
            return;
        }
        case_first_executable(head, infile, outfile, c_track, path_variable);
    }
    else
        case_first_builtin(head, outfile, c_track);
}

void loop_over_nodes(t_cmd_track* c_track, t_line_splited **head, int infile, int outfile)
{
    if(parse_files(*head, &outfile, &infile) == -1)
        case_failed_parsing_files(c_track, head);
    else
    {
        if(c_track->i == 0)
        {
            case_first(*head, c_track, infile, outfile);
            *head= (*head)->next;
        }
        if(c_track->i != c_track->nb_pipes - 1 && c_track->nb_pipes != 0 && head)
        {
            case_middle(*head, c_track, infile, outfile);
            *head= (*head)->next;
        }
        if(c_track->i == c_track->nb_pipes - 1 && c_track->nb_pipes != 0 && head)
        {
            case_last(*head, c_track, infile, outfile);
            *head= (*head)->next;
        }
    }
}

void execution(t_line_splited *head, t_cmd_track *c_track)
{
    int outfile;
    int infile;

    c_track->nb_pipes = list_size(head) - 1;

    if(allocate_array(c_track) == -1)
        return;
    if(open_pipes(c_track) == -1)
        return;
    c_track->i = 0;
    while(head)
    {
        outfile = 1;
        infile = 0;
        loop_over_nodes(c_track, &head, infile, outfile);
        c_track->i++;
    }
    close_all(c_track);
    free_all(c_track);
}