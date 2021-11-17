int ft_find_char(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if(str[i] == c)
			return(i);
		i++;
	}
	return (0);
}

int ft_find_next_char(char *str, char c)
{
	int i;

	i = 1;
	if (!str)
		return (0);
	while (str[i])
	{
		if(str[i] == c)
			return(i);
		i++;
	}
	return (0);
}