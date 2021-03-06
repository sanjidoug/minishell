/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlescart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:59:36 by dlescart          #+#    #+#             */
/*   Updated: 2021/11/17 19:00:15 by dlescart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_bzero(void *b, int n)
{
	unsigned char	*dest;
	int				i;

	dest = b;
	i = 0;
	while (i++ < n)
		*dest++ = 0;
}
