/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:06:07 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/11 22:01:48 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
	{
		write(fd, &*s, 1);
		s++;
	}
}

/*
int	main(void)
{
	int		fd;
	char 	*str = "Salut la team";
	
	fd = open("chips", O_WRONLY);
	if (fd == -1)
		return (0);
	ft_putstr_fd(str, fd);
	return (0);
}*/
