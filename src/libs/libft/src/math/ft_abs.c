#include "libft.h"

/* Returns absolute value of an int argument. Returns 0 for INT_MIN.*/
int	ft_abs(int num)
{
	if (num == INT_MIN)
		return (0);
	if (num < 0)
		return (-num);
	return (num);
}
