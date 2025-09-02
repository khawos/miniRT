/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:53:27 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/14 01:37:25 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	int	a;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = n * -1;
		write(fd, "-", 1);
	}
	if (n < 10)
	{
		a = n + 48;
		write(fd, &a, 1);
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}

/*
int	main(void)
{
	int	fd;

	fd = open("chips", O_WRONLY);
	ft_putnbr_fd(-2147483648, fd);
	close(fd);
	return (0);
}*/
