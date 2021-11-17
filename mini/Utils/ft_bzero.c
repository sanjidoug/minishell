void				ft_bzero(void *b, int n)
{
	unsigned char	*dest;
	int			i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}