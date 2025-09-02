/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:15:36 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/11 22:01:15 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void	ft_putstr_fd(char *c, int fd);

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putstr_fd("\n", fd);
}

/*
int main(void)
{
	char	*str = "J'ai fini les chips";
	int		fd;

	fd = open("chips", O_WRONLY);
	if (fd == -1)
		return (0);
	ft_putendl_fd(str, fd);
	return (0);
}*/
