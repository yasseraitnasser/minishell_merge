 #include "../../minishell.h"

    // si empieza con # no importa lo que viene a continuacion lista los variables
    // si # viene al principio de una variable al centro, guarda los de antes y sale
    // si $ viene al principio y es solo lista export
    // si $ viene con otros variables skip y guarda lo de antes y despues
void ft_export(t_line_splited *par, int foutput)
{
    int i;
    char **export;

    i = 0;
    if(par->cmd[1] == NULL || par->cmd[1][0] == '#')
    {
        export = sort_env(par, environ);
        while(export[i])
        {
            ft_putstr_exp(export[i], foutput);
            write(foutput, "\n", 1);
            i++;
        }
        free_matrix(export);
    }
    else
       environ = handle_variables(par);
}

char **create_copy(char **str, int *size)
{
    int i;
    char **cp;

    while(str[*size])
        (*size)++;
    cp = malloc(sizeof(char *)*(*size+1));
    i = 0;
    while(str[i])
    {
        cp[i]= ft_strdup(str[i]);
        i++;
    }
    cp[i]= NULL;
    return(cp);
}

void loop_over_env(t_line_splited*par, char **cpy_env, char *small, int *index_of_small, int size_env)
{
    int count;
    int i;

    count = 0;
    i = 0;
    (void)par;
    while(i < size_env)
    {
        count++;
        while(cpy_env[i] && cpy_env[i][0] == '0')
            i++;
        if(cpy_env[i] && count == 1)
        {
            *index_of_small = i;
            small = cpy_env[i++];
        }
        if(environ[i] && ft_strcmp(small, cpy_env[i]) > 0 && cpy_env[i][0] != '0')
        {
            small = cpy_env[i];
            *index_of_small = i;
        }
        i++;
    }
}

void loop(t_line_splited *par, int size_env, char **export, char **cpy_env)
{
    int j;
    int index_of_small;
    char *small;

    j = 0;
    small = NULL;
    index_of_small = 0;
    while(j < size_env && environ)
    {
        loop_over_env(par, cpy_env, small, &index_of_small, size_env);
        export[j] = ft_join("declare -x ", environ[index_of_small]);
        free(cpy_env[index_of_small]);
        cpy_env[index_of_small]=ft_strdup("0");
        j++;
    }
}

char **sort_env(t_line_splited *par, char **export)
{
    int size_env;
    char **cpy_env;



    size_env = 0;
    cpy_env = create_copy(environ, &size_env);
    export = malloc(sizeof(char *)*(size_env+1));
    loop(par, size_env, export, cpy_env);
    export[size_env]=NULL;
    free_matrix(cpy_env);
    return(export);
}

