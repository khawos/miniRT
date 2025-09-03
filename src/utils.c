#include "miniRT.h"

double	atoi_double(char *str)
{
	double	integer_part;
	double	float_part;
	double	power;
	int		neg;

	integer_part = 0;
	float_part = 0;
	power = 1;
	neg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '-' || *str == '+')
		if (*str++ == '-')
			neg = -1;
	while (*str != '.' && (*str >= '0' && *str <= '9'))
		integer_part = (*str++ - 48) + (integer_part * 10);
	if (*str == '.')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		power /= 10;
		float_part += (*str++ - 48) * power;
	}
	return ((integer_part + float_part) * neg);
}

void	free_double_array(char **dest)
{
	int	i;

	i = 0;
	while (dest[i])
		free(dest[i++]);
	free(dest);
}