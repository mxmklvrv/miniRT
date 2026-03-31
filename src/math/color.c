#include "minirt.h"

static void	color_check_value_range(int *value);

/* Get color with given values in range [0, 255].
 * @param	int	opacity	opacity value;
 * @param	int	red		red value;
 * @param	int	green	green value;
 * @param	int	blue	blue value;
 * @returns	int	resulting color.
 */
int	new_color(int opacity, int red, int green, int blue)
{
	color_check_value_range(&opacity);
	color_check_value_range(&red);
	color_check_value_range(&green);
	color_check_value_range(&blue);
	return ((opacity << 24) + (red << 16) + (green << 8) + blue);
}

/* Check that value is in range [0, 255]; if not, set it to 0 or 255.
 * @param	int	*value	value;
 */
static void	color_check_value_range(int *value)
{
	if (*value < 0)
		*value = 0;
	else if (*value > 255)
		*value = 255;
}
