int ft_redirection(t_parse *parse)
{
	int i;

	i = 0;
	while(parse->tab_arg[i] != NULL)
	{
		if(!ft_strchr(parse->tab_arg[i], '>'))
		{
			ft_redir_out(parse, i);
		}
		i++;
	}
}

int ft_redir_out(t_parse *parse,int index)
{
	
}