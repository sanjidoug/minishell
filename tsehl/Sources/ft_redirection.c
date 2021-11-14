#include "../minishell.h"

int ft_search_redir(t_parse *parse, t_counter *count, int i)
{
	//printf("tes\n");
	while(parse->tab_arg[i] != NULL)
	{
		count->l = 0;
		while(parse->tab_arg[i][count->l])
		{
			//printf("%s\n",parse->tab_arg[i]);
			if(parse->tab_arg[i][count->l] == '>')
			{
				if(ft_redir_out(parse, i, &parse->redo[count->j]))
					return(-1);
				count->j++;
				count->m = -1;
				break;
			}
			else if(parse->tab_arg[i][count->l] == '<')
			{
				ft_redir_in(parse, i, &parse->redin[count->k]);
				count->k++;
				count->m = -1;
				break;
			}
			count->l++;
		}
		if(count->m < 0)
			break;
		i++;
	}
	//printf("tes2\n");
	if(count->m < 0)
		return(1);
	return(0);
}

int ft_redirection(t_parse *parse)
{
	t_counter count;
	init_count(&count);
	while(parse->tab_arg[count.i] != NULL)
	{	
		count.j += ft_count(parse->tab_arg[count.i], '>');
		count.k += ft_count(parse->tab_arg[count.i++], '<');
	}
	parse->redo = malloc(sizeof(t_redo) * (count.j + 1));
	parse->redin = malloc(sizeof(t_redo) * (count.k + 1));
	init_count(&count);
	while(parse->tab_arg[count.i] != NULL)
	{
		//printf("seg\n");
		count.m = 0;
		count.m = ft_search_redir(parse, &count, count.i);
		if (count.m > 0)
			count.i = 0;
		else if (count.m == 0)
			count.i++;
		else
			return(1);
		//printf("seg2 %d\n", count.i);
		/*count.l = 0;
		while(parse->tab_arg[count.i][count.l])
		{
			while(parse->tab_arg[count.i][count.l] && parse->tab_arg[count.i][count.l] != '>' && (parse->tab_arg[count.i][count.l] != '<'))
				count.l++;
			if(parse->tab_arg[count.i][count.l] == '>')
				ft_redir_out(parse, count.i, &parse->redo[count.j++]);
			else if(parse->tab_arg[count.i][count.l] == '<')
				ft_redir_in(parse, count.i, &parse->redin[count.k++]);
			if(parse->tab_arg[count.i][count.l])
				count.l = 0;*/
	}
	parse->redo[count.j].append = -100;
	parse->redin[count.k].append = -100;
	return(0);
	//printf("end ft_redirection\n");
}

void ft_redir_in(t_parse *parse,int index, t_redo *redin)
{
	int i;
	
	i = 0;
	parse->redir_in = 1;
	redin->append = 0;
	while(parse->tab_arg[index][i] != '<')
		i++;
	ft_delchar(parse->tab_arg[index], i);
	if(parse->tab_arg[index][i] == '<')
		redin->append = ft_delchar(parse->tab_arg[index], i);
	if(parse->tab_arg[index][i] == 0)
	{
		if(i == 0)
			ft_delstr(parse->tab_arg, index);
		else
			index++;
		i = 0;
	}
	//printf("fsf\n");
	redin->file = ft_parse_file(parse->tab_arg[index] + i);
	//printf("rdin = %s\n", redin->file);
	ft_delfile(parse, index, i);
	if(!redin->file || redin->file[0] == 0)
		exit(0);
	//printf("end ft_redirin\n");
}


int ft_redir_out(t_parse *parse,int index, t_redo *redo)
{
	int i;
	
	i = 0;
	parse->redir_out = 1;
	redo->append = 0;
	while(parse->tab_arg[index][i] != '>')
		i++;
	ft_delchar(parse->tab_arg[index], i);
	if(parse->tab_arg[index][i] == '>')
		redo->append = ft_delchar(parse->tab_arg[index], i);
	if(parse->tab_arg[index][i] == 0)
	{
		if(i == 0)
			ft_delstr(parse->tab_arg, index);
		else
			index++;
		i = 0;
	}
	redo->file = ft_parse_file(parse->tab_arg[index] + i);
	ft_delfile(parse, index, i);
	//printf("path = %s\n", redo->file);
	if(!redo->file || redo->file[0] == 0)
		return(printf("msh: syntax error near unexpected token `newline'/\n"));
	return(0);
	//printf("end ft_redirout\n");
}

void ft_fd_out(t_parse *parse)
{
	int i;

	i = 0;
	while(parse->redo[i].append != -100)
	{
		if(parse->redo[i].append > 0)
			parse->redo[i].fd = open(parse->redo[i].file, O_WRONLY | O_CREAT| O_APPEND, 0777);
		else
			parse->redo[i].fd = open(parse->redo[i].file, O_WRONLY | O_CREAT| O_TRUNC, 0777);
		if(parse->redin[i].fd < 0)
		{
			//ft_putstr_fd(parse->redin[i].file + 2, 2);
			perror("msh");
			exit(0);
		}
		i++;
	}
	//printf("er  %s\n", parse->redo[0].file);
	dup2(parse->redo[0].fd, 1);
	i = 0;
	while(parse->redo[i].append != -100)
		free(parse->redo[i++].file);
	//printf("der\n");
}

void ft_fd_in(t_parse *parse)
{
	int i;

	i = 0;
	while(parse->redin[i].append != -100)
	{
		//if(parse->redin[i].append > 0)
		parse->redin[i].fd = open(parse->redin[i].file, O_RDONLY);
		if(parse->redin[i].fd < 0)
		{
			ft_putstr_fd(ft_strjoin("msh :",parse->redin[i].file + 2), 2);
			perror(" ");
			//ft_putstr_fd(parse->redin[i].file + 2, 2);
			exit(0);
		}
		i++;
	}
	//printf("i = %d et app = %d", i , parse->redin[i].append);
	dup2(parse->redin[0].fd, 0);
	i = 0;
	while(parse->redin[i].append != -100)
		free(parse->redin[i++].file);
}


/*int free_red(t_parse *parse)
{
	int i;

	i = 0;
	while(parse->redo[i].append != -100)
	{	
		free(parse->redo[i++].file);
	}
	free(parse->redo);
	return (0);
}*/