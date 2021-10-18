#include "../minishell.h"

char	*ft_strdup_env(char *src, t_utils utils)
{
	int		i;
	int 	j;
	int		len;
	char	*str;

	len = 0;
	while (src[len])
		len++;
	str = (char*)malloc(sizeof(*str) * (len - utils.len_bequal));
	i = utils.len_bequal + 1;
	j = 0;
	while (i < len)
	{
		str[j++] = src[i];
		i++;
	}
	return (str);
}