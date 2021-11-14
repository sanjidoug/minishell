char *ft_strcat_cd(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j + 1];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}