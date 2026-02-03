#include "libft.h"

/* Returns maximum value from given.
 *
 * @param	int		arg_count number of expected values.
 * @param	int		... values.
 * @returns	int		max value from given or 0.
 */
int	ft_max(int arg_count, ...)
{
	va_list	arg_ptr;
	int		i;
	int		current;
	int		max;

	va_start(arg_ptr, arg_count);
	i = 0;
	max = 0;
	while (i < arg_count)
	{
		current = va_arg(arg_ptr, int);
		if (i == 0 || current > max)
			max = current;
		i++;
	}
	va_end(arg_ptr);
	return (max);
}
