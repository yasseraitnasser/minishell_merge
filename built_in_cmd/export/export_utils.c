 #include "../../minishell.h"



int count_new_variables(t_line_splited *par,int size)
{
    int i;
    int nb;
    int count;
    int check;

    i = 1;
    nb = 0;
    count = 0;
    while(par->cmd[i])
    {
        if(check_if_valid(par->cmd[i], size, 0) == 0)
        {    
            check = check_if_add_change_append(par, par->cmd[i], size, &count);
            if( check == 0  || check == 3)
            {
                printf("i am var %s\n", par->cmd[i]);
                nb++;
            }
        }
        i++;
    }
    printf("i am count: %d\n", count);
    return(nb-(count/2));
}

int size_env(char **env)
{
    int i;

    i = 0;
    while(env[i])
    {
        i++;
    }
    return(i);
}

char *return_key(char* str)
{
    int i;
    char *key;

    i = 0;
    key = malloc(ft_strlen(str)+1);
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        key[i]=str[i];
        i++;
    }
    key[i]= '\0';
    return(key);
}

char *to_append(char *str)
{
    int i;

    i = 0;
    while(str[i] && str[i] != '=')
    {
        i++;
    }
    i++;
    return(str+i);
}

void add_var_if_not_exist(char *new_var, int size, int added, int check)
{
    int i;

    i = 0;
    while(i < size+added)
    {
        i++;
    }
    if(check == 0)
        environ[i] = ft_strdup(new_var);
    else if(check == 3)
        environ[i] = add_non_existing_append_var(new_var);
}

char* return_value(char *full_var)
{
    int i;
    char *value;

    i = 0;
    value = NULL;
    while(!full_var && full_var[i] != '\0' && full_var[i] != '=')
    {
        // printf("%c", full_var[i]);
        i++;
    }
    if( !full_var || full_var[i] == '\0')
        return(NULL);
    return(full_var + i);
}