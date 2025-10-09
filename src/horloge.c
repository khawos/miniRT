/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horloge.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <jbayonne@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-10-09 13:57:25 by jbayonne          #+#    #+#             */
/*   Updated: 2025-10-09 13:57:25 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

unsigned long	chrono(void)
{
	struct timeval	tv;
	unsigned long	time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000000 + tv.tv_usec;
	return (time / 1000);
}

unsigned long	current_time(unsigned long start)
{
	return (chrono() - start);
}