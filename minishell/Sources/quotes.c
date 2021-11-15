#include "../minishell.h"

int ft_is_quotes(char c)
{
    if (c == '"' || c == 39)
        return (1);
    return (0);
}

int ft_closed_quotes(char *str, int index)
{
    char quotes;

    quotes = str[index];
    index++;
    while (str[index])
    {
        if (str[index] == quotes)
            return (index);
        index++;
    }
    return (0);
}

int ft_check_quotes(t_parse *parse, int i)
{
    int j;
    int index;

    index = 0;
    while (parse->tab_arg[i] != NULL)
    {
        j = 0;
        while (parse->tab_arg[i][j])
        {
            index++;
            if (parse->tab_arg[i][j] == parse->quotes)
                return (i);
            j++;
        }
        i++;
    }
    return (0);
}

void ft_parse_quote(t_parse *parse, t_counter *count, char *str)
{
    char *s;
    int i;
    int j;
    int save_j;

    j = 0;
    parse->str_dollar = malloc(sizeof(char) * 1000);
    while (parse->tab_arg[count->i][count->j])
    {
        if (ft_is_quotes(parse->tab_arg[count->i][count->j]) 
            && ft_closed_quotes(parse->tab_arg[count->i], count->j))
        {
            if (ft_is_quotes(parse->tab_arg[count->i][count->j]))

            parse->quotes = parse->tab_arg[count->i][count->j];
            if (parse->tab_arg[count->i][count->j] == 39)
                parse->tab_simple_quotes[count->k++] = '1';
            else
                parse->tab_simple_quotes[count->k++] = '0';
            count->j++;
            while (parse->tab_arg[count->i][count->j] != parse->quotes 
                && parse->tab_arg[count->i][count->j])
                    str[count->l++] = parse->tab_arg[count->i][count->j++];
        }
        else
        {
            str[count->l++] = parse->tab_arg[count->i][count->j];
            parse->str_dollar[j++] = parse->tab_arg[count->i][count->j];
        }
        parse->str_dollar[j] = '\0';
        count->j++;
    }
}

void ft_quotes(t_parse *parse)
{
    t_counter count;
    char *str;

    count.i = 0;
    count.k = 0;
    parse->tab_simple_quotes = malloc(sizeof(char) * ft_nb_arg(parse->tab_arg) + 1);
    while (parse->tab_arg[count.i] != NULL)
    {
        str = malloc(sizeof(char) * ft_strlen(parse->tab_arg[count.i]) + 1);
        count.j = 0;
        count.l = 0;
        ft_parse_quote(parse, &count, str);
        str[count.l] = '\0';
        free(parse->tab_arg[count.i]);
        parse->tab_arg[count.i] = ft_strdup(str);
        free(str);
        count.i++;
        if (count.k != count.i)
            parse->tab_simple_quotes[count.k++] = '0';
    }
    parse->tab_simple_quotes[count.k] = '\0';
}