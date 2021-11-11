#include "../minishell.h"

static int	count_strs(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			count++;
			while (*s != '\0' && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

char	**ft_split_custom(char const *s, char c, t_parse *parse)
{
	int		len;
	int i;
	int cpt;
	int	index;
	int is_not_space;
	int *tab_spaces;
	const char	*start;
	char		**split;

	split = (char **) malloc(((count_strs(s, c)) + 1) * sizeof(*split));
	if (!split)
		return (0);
	index = 0;
	parse->tab_spaces = malloc(sizeof(int) * 500);
	i = 0;
	is_not_space = 0;
	while (*s != '\0')
	{
		cpt = 0;
		if (*s != ' ')
			is_not_space = 1;
		while (*s && *s == c)
		{
			if (c == ' ' && is_not_space)
				cpt++;
			s++;
		}
		if (cpt != 0)
			parse->tab_spaces[i++] = cpt;
		is_not_space = 1;
		start = s;
		len = 0;
		while (*s && *s != c)
		{
			s++;
			len++;
		}
		if (*(s - 1) != c)
			split[index++] = ft_substr(start, 0, len);
	}
	parse->tab_spaces[i] = -1;
	split[index] = 0;
	return (split);
}