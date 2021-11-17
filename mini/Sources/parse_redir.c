#include "../minishell.h"

char *ft_parse_file(char *str)
{
	int i;
	int j;
	char *ret;

	i = 0;
	j = 2;
	if(!str)
		return(NULL);
	while(str[i] && str[i] != '<' && str[i] != '>')
		i++;
	if(i == 0)
		return(NULL);
	ret = malloc(sizeof(char) * i + 2 + 1);
	ret[0] = '.';
	ret[1] = '/';
	i = 0;
	while(str[i] && str[i] != '<' && str[i] != '>')
		ret[j++] = str[i++];
	ret[j] = '\0';
	return(ret);
}

int ft_delfile(t_parse *parse, int n, int s)
{
	int i;

	i = 0;
	//printf("str = %s ou %s\n", parse->tab_arg[n] + s, parse->tab_arg[n]);
	if(!parse->tab_arg[n] || parse->tab_arg[n][s] == 0)
		return(0);
	//printf("s = %d\n", s);
	if(ft_strchr(parse->tab_arg[n] + s, '>') || ft_strchr(parse->tab_arg[n] + s, '<'))
	{
		while(parse->tab_arg[n][s + i] != '<'  && (parse->tab_arg[n][s + i]) != '>')
		{
			//printf("c = %c\n", parse->tab_arg[n][s + i + 1]);
			ft_delchar(parse->tab_arg[n], s + i);
		}
	}
	else if(s == 0)
		ft_delstr(parse->tab_arg, n);
	else
	{
		while(parse->tab_arg[n][s + i] != '\0')
		{
			//printf("char in = %c\n" ,parse->tab_arg[n][s + i]);
			ft_delchar(parse->tab_arg[n], s + i);
			//i++;
		}
		//printf("char out = %c et i = %d\n" ,parse->tab_arg[n][s] , i);

	}
	//printf("str = %s ou %s\n", parse->tab_arg[n] + s, parse->tab_arg[n]);
	return(1);
	//printf("str = %s ou %s\n", parse->tab_arg[n] + s, parse->tab_arg[n]);
}