/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:37:28 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/14 09:04:46 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	ft_count_nico(char const *lastring, char c)
{
	int	k;
	int	c_nico;

	c_nico = 0;
	while (*lastring)
	{
		k = 1;
		while (*lastring && *lastring == c)
			lastring++;
		while (*lastring && *lastring != c)
		{
			lastring++;
			if (k == 1)
			{
				k = 0;
				c_nico++;
			}
		}
	}
	return (c_nico);
}

static int	safe_malloc(char **nico, int i, int tchico)
{
	nico[i] = malloc(sizeof(char) * tchico + 1);
	if (!nico[i])
	{
		while (i >= 0)
			free(nico[i--]);
		free(nico);
		return (1);
	}
	return (0);
}

static int	catnico(const char *lastring, char **nico, int i, int tchico)
{
	int	j;

	j = 0;
	if (safe_malloc(nico, i, tchico))
		return (1);
	while (tchico)
	{
		nico[i][j] = *lastring;
		tchico--;
		lastring++;
		j++;
	}
	nico[i][j] = '\0';
	return (0);
}

static int	fill_nico(char const *lastring, char **nico, char c)
{
	int	i;	
	int	tchico;

	i = 0;
	while (*lastring)
	{
		tchico = 0;
		while (*lastring && *lastring == c)
			lastring++;
		while (*lastring && *lastring != c)
		{
			tchico++;
			lastring++;
		}
		if (tchico)
		{
			if (catnico(lastring - tchico, nico, i, tchico))
				return (1);
			i++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**nico;
	int		len_nico;

	len_nico = ft_count_nico(s, c);
	nico = malloc(sizeof(char *) * (len_nico + 1));
	if (!nico)
		return (NULL);
	if (fill_nico(s, nico, c))
		return (NULL);
	nico[len_nico] = 0;
	return (nico);
}

/*
int	main(void)
{
	char	**array;
	char	list[] = "  salut la team c'est nico  ";

	array = ft_split(list, ' ');
	for (int i = 0; array[i]; i++)
		printf("%s\n", array[i]);
	return (0);
}*/
