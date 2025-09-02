/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbayonne <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 20:00:06 by jbayonne          #+#    #+#             */
/*   Updated: 2024/11/12 22:18:00 by jbayonne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <string.h>
#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_cmp;	
	unsigned char	*s2_cmp;

	s1_cmp = (unsigned char *) s1;
	s2_cmp = (unsigned char *) s2;
	if (n == 0)
		return (0);
	n -= 1;
	while (n--)
	{
		if (*s1_cmp != *s2_cmp)
			return (*s1_cmp - *s2_cmp);
		s1_cmp++;
		s2_cmp++;
	}
	return (*s1_cmp - *s2_cmp);
}

/*
int main(void)
{
	const char tmp[5] = {'i','o', 'n', 'u', 't'};
	const char tmp2[5] = {'i','a', 'n', 'u', 't'};
	const int arr[20] = {0,1,2,4,4,5,6,7,8,9,10,11,12,13};
	const int arr1[20] = {0,1,2,4,4,5,6,7,8,9,10,11,12};
	const	char *str = "Je su9s une array de char et voila la suite iiiipgalement";
	const	char *str1 = "Je suis une array de char et voila la suite";

	printf("ft_memcmp :%d\n", ft_memcmp(arr, arr1, sizeof(int) * 10));
	printf("   memcmp :%d\n\n", memcmp(arr, arr1, sizeof(int) * 10));

	printf("ft_memcmp :%d\n", ft_memcmp(str, str1, 0));
	printf("   memcmp :%d\n", memcmp(str, str1, 0));
	printf("ft_memcmp :%d\n", ft_memcmp(tmp, tmp2, sizeof(char) * 5));
	printf("   memcmp :%d\n", memcmp(tmp, tmp2, sizeof(char)*5));

}*/	
