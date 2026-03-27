#include "minirt.h"

/* Get color by adding values of given colors.
 * @param	int	c1	color 1;
 * @param	int	c2	color 2;
 * @returns	int	resulting color.
 */
int	color_add(int c1, int c2)
{
	return (new_color(
		get_opacity(c1) + get_opacity(c2),
		get_red(c1) + get_red(c2),
		get_green(c1) + get_green(c2),
		get_blue(c1) + get_blue(c2)
	));
}

/* Get color by substracting values of color 2 from color 1.
 * @param	int	c1	color 1;
 * @param	int	c2	color 2;
 * @returns	int	resulting color.
 */
int	color_substract(int c1, int c2)
{
	return (new_color(
		get_opacity(c1) - get_opacity(c2),
		get_red(c1) - get_red(c2),
		get_green(c1) - get_green(c2),
		get_blue(c1) - get_blue(c2)
	));
}

/* Get color by multiplying values of given color by scalar.
 * @param	int		c		color;
 * @param	float	scalar	value to multiply by;
 * @returns	int		resulting color.
 */
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
 * @param	int		c2			color 2;
 * @param	float	intencity	intencity of color 2 in range [0, 1]; if out of
 * 								range, returns one of given colors;
 * @returns	int		resulting color.
 */
int	color_mix(int c1, int c2, float intencity)
{
	if (intencity < 0)
		return (c1);
	if (intencity > 1)
		return (c2);
	return(color_add(color_multiply(c1, 1 - intencity), color_multiply(c2,
		intencity)));
}

/* Find the color of surface of color c1 under light og color c2. Black light
 * negates color of surface; black surface negates color of light; white light
 * doesn't change color of surface.
 * @param	int	c1	color 1;
 * @param	int	c2	color 2;
 * @returns	int	resulting color.
 */
int	color_mix_light(int c1, int c2)
{
	return (new_color(
		get_opacity(c1) * get_opacity(c2) / 255,
		get_red(c1) * get_red(c2) / 255,
		get_green(c1) * get_green(c2) / 255,
		get_blue(c1) * get_blue(c2) / 255
	));
}
