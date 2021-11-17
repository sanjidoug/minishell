/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirections_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 16:43:49 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 16:51:18 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	double_redir(t_redo *redin)
{
	read_until(redin->file + 2);
	redin->fd = open(redin->file, O_RDONLY);
	return (1);
}

void	read_until(char *end)
{
	char	*line;
	int		flags;
	int		fd;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(ft_strjoin("/tmp/", end), flags, 0777);
	while (ft_strncmp(line, end, ft_strlen(end))
		|| ft_strlen(line) != ft_strlen(end))
	{
		free(line);
		line = readline("> ");
		if (ft_strncmp(line, end, ft_strlen(end))
			|| ft_strlen(line) != ft_strlen(end))
			ft_putendl_fd(line, fd);
	}
	close(fd);
	free(line);
}

void	ft_fd_out(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->redo[i].append != -100)
	{
		if (parse->redo[i].append > 0)
			parse->redo[i].fd = open(parse->redo[i].file, O_WRONLY
					| O_CREAT | O_APPEND, 0777);
		else
			parse->redo[i].fd = open(parse->redo[i].file, O_WRONLY
					| O_CREAT | O_TRUNC, 0777);
		if (parse->redo[i].fd < 0)
		{
			perror("msh");
			exit(0);
		}
		i++;
	}
	dup2(parse->redo[i - 1].fd, 1);
	i = 0;
	while (parse->redo[i].append != -100)
		free(parse->redo[i++].file);
}

void	ft_fd_in(t_parse *parse)
{
	int	i;

	i = 0;
	while (parse->redin[i].append != -100)
	{
		if (parse->redin[i].append > 0)
		{
			read_until (parse->redin[i].file + 2);
			parse->redin[i].fd = open(ft_strjoin("/tmp/",
						parse->redin[i].file), O_RDONLY);
		}
		else
			parse->redin[i].fd = open(parse->redin[i].file, O_RDONLY);
		if (parse->redin[i].fd < 0)
		{
			ft_putstr_fd(ft_strjoin("msh :", parse->redin[i].file + 2), 2);
			perror(" ");
			exit(1);
		}
		i++;
	}
	dup2(parse->redin[i - 1].fd, 0);
	i = 0;
	while (parse->redin[i].append != -100)
		free(parse->redin[i++].file);
}
