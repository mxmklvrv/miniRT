#include "minirt.h"

static int	color_get_last_byte(int value);

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
