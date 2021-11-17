#include "../minishell.h"

int ft_count(char *str, char c)
{
	int i;
	int	j;

	i = 0;
	j = 0;
	while(str[i])
	{
		if(str[i] == c)
			j++;
		i++;
	}
	return(j);
}