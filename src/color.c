#include "minirt.h"

static void	color_check_value_range(int *value);
static int	color_get_last_byte(int value);

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

int	get_opacity(int color)
{
	color = color >> 24;
	return (color_get_last_byte(color));
}

int	get_red(int color)
{
	color = color >> 16;
	return (color_get_last_byte(color));
}

int	get_green(int color)
{
	color = color >> 8;
	return (color_get_last_byte(color));
}

int	get_blue(int color)
{
	return (color_get_last_byte(color));
}

static int	color_get_last_byte(int value)
{
	return (value & 0x0000FF);
}

int	color_add(int c1, int c2)
{
	return (new_color(
		get_opacity(c1) + get_opacity(c2),
		get_red(c1) + get_red(c2),
		get_green(c1) + get_green(c2),
		get_blue(c1) + get_blue(c2)
	));
}

int	color_substract(int c1, int c2)
{
	return (new_color(
		get_opacity(c1) - get_opacity(c2),
		get_red(c1) - get_red(c2),
		get_green(c1) - get_green(c2),
		get_blue(c1) - get_blue(c2)
	));
}

int	color_multiply(int c, float scalar)
{
	return (new_color(
		get_opacity(c) * scalar,
		get_red(c) * scalar,
		get_green(c) * scalar,
		get_blue(c) * scalar
	));
}
/* Find the color of mix of 2 colors.
 * @param	int		c1			color 1;
 * @param	float	intencity_1	intencity of color 1;
 * @param	int		c2			color 2;
 * @param	float	intencity_2	intencity of color 2;
 * @returns	int		resulting color.
 */
int	color_mix(int c1, float intencity_1, int c2, float intencity_2)
{
	float	sum;

	sum = intencity_1 + intencity_2;
	return(color_add(color_multiply(c1, intencity_1 / sum), color_multiply(c2,
		intencity_2 / sum)));
}
