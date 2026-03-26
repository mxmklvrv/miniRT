#include "minirt.h"

static void	color_check_value_range(int *value);

int	new_color(int opacity, int red, int green, int blue)
{
	color_check_value_range(&opacity);
	color_check_value_range(&red);
	color_check_value_range(&green);
	color_check_value_range(&blue);
	return ((opacity << 24) + (red << 16) + (green << 8) + blue);
}

static void	color_check_value_range(int *value)
{
	if (*value < 0)
		*value = 0;
	else if (*value > 255)
		*value = 255;
}
