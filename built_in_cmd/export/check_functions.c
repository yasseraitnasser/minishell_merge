 #include "../../minishell.h"

//0 es decir append
int check_if_append(char *new_var)
{
    int i;

    i = 0;
    while(new_var[i])
    {
        if(new_var[i] == '+' && new_var[i+1] == '=')
            return(0);
        i++;
    }
    return(-1);
}

//0 es decir add
//1 es decir change
//2 es decir append
//3 si escribimos una variable asi u+=value pero noexite antes
int check_if_add_change_append(t_line_splited *par, char *new_var, int max, int *count)
{
    int i;
    int check;
    char *keyenv;
    char *keyvar;

    i = 0;
    check = 0;
    keyvar = return_key(new_var);
    while(i < max)
    {
        if(new_var[0] == '$')
            return(-1);
        keyenv = return_key(environ[i]);
        if(ft_strcmp(keyenv, keyvar) == 0)
        {
            free(keyenv);
            check = 1;
            break;
        }
        i++;
    free(keyenv);
    }
    free(keyvar);
    if(check == 0 && check_if_append(new_var) != 0) //add
    {
        if(check_if_var_reapeated(par, new_var) == 1)
        {
            printf("wakwaaaak\n");
            (*count)++;
        }
        return (0);
    }
    else if(check == 0 && check_if_append(new_var) == 0) //add
        return(3);
    else if(check == 1 && check_if_append(new_var) != 0)
    {
        return(1);
    }
    else if(check == 1 && check_if_append(new_var) == 0)
    {

        return(2);
    }

    return(-1);
}
int is_var_value_present(char *value, int size, int added)
{
    int i;
    char *env_value;

    i = 0;
    while(i < size + added)
    {
        // printf("%s\n", par->env[i]);
        env_value = return_value(environ[i]);
        if(ft_strcmp(env_value, value) == 0)
            return(1);
        i++;
    }
    return(-1);
}

// si es valido returna 0 sino returna -1
//si puedes arreglar el caso /
int check_if_valid(char *new_var, int size, int added) //!rje3
{
    int i;

    i = 0;
    while(new_var[i] == ' ')
        i++;
    if(new_var[i] == '#')
        return(-3);
    // else if(new_var[i] == '$')
    //     return(-2);
    else if(is_var_value_present(new_var, size, added) == 1)
        return(-1);
    else if((new_var[i] < 'a' || new_var[i] > 'z') && (new_var[i] != '_') )
    {
        if(new_var[i] < 'A' || new_var[i] > 'Z')
            return(-1);
    }
    return(0);
}

int check_if_var_reapeated(t_line_splited *par, char *new_var)
{
    int i;
    char *key_cmd;
    char *key_new_var;

    i = 1;
    key_new_var = return_key(new_var);
    while(par->cmd[i])
    {
        key_cmd = return_key(par->cmd[i]);
        if(ft_strcmp(new_var, par->cmd[i]) == 0)
        {
            i++;
            free(key_cmd);
            if(par->cmd[i])
                key_cmd = return_key(par->cmd[i]);
            else
                break;
        }
        if(par->cmd[i] && ft_strcmp(key_cmd, key_new_var) == 0 )
        {
            printf("i am new var : %s i am test : %s\n", key_new_var, key_cmd); 
            free(key_cmd);
            free(key_new_var);
            return(1);
        }
        if(!par->cmd[i])
        {
            free(key_cmd);
            break;
        }
        i++;
        free(key_cmd);
    }
    free(key_new_var);
    return(0);
}
