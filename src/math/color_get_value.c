#include "minirt.h"

static int	color_get_last_byte(int value);

/* Get opacity value of given color.
 * @param	int	c	color ;
 * @returns	int	opacity value.
 */
int	get_opacity(int color)
{
	color = color >> 24;
	return (color_get_last_byte(color));
}

/* Get red value of given color.
 * @param	int	c	color;
 * @returns	int	red value.
 */
int	get_red(int color)
{
	color = color >> 16;
	return (color_get_last_byte(color));
}

/* Get green value of given color.
 * @param	int	c	color;
 * @returns	int	green value.
 */
int	get_green(int color)
{
	color = color >> 8;
	return (color_get_last_byte(color));
}

/* Get blue value of given color.
 * @param	int	c	color;
 * @returns	int	blue value.
 */
int	get_blue(int color)
{
	return (color_get_last_byte(color));
}

/* Get value of last byte of int.
 * @param	int	value	value;
 * @returns	int	value of last byte.
 */
static int	color_get_last_byte(int value)
{
	return (value & 0x0000FF);
}
