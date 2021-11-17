#include "../minishell.h"

int ft_is_fill(char *str, char c)
{
	int i;

	i = 0;
	if(!str)
		return(-1);
	if(ft_strlen(str) == 0)
		return(0);
	while(str[i])
	{
		if(str[i] != c)
			return(0);
		i++;
	}
	return(1);
}