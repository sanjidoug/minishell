#include "../minishell.h"

char	*ft_strjoin_path(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, (char*)s1);
	str[ft_strlen(s1)] = '/';
	str[ft_strlen(s1) + 1] = '\0';
	ft_strcat(str, (char*)s2);
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(*str) * (len + 1));
	if (str == NULL)
		return (NULL);
	ft_strcpy(str, (char*)s1);
	str[ft_strlen(s1) + 1] = '\0';
	ft_strcat(str, (char*)s2);
	return (str);
}