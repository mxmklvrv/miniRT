#include "minirt.h"

static void	normalize_pos(t_scene *scene);
static int	trace_color(t_point point, t_scene *scene);

void	draw_scene(t_data *data, t_scene *scene)
{
	t_point	point;

	normalize_pos(scene);
	point.y = 0;
	while (point.y < HEIGHT)//TODO: add multi threading
	{
		point.x = 0;
		while (point.x < WIDTH)
		{
			point.color = trace_color(point, scene);
			ft_mlx_put_pixel(data, point);
			point.x++;
		}
		point.y++;
	}
}

static void	normalize_pos(t_scene *scene)
{
	t_olist	*obj_list;
	t_sp	*sp;
	t_cy	*cy;
	t_pl	*pl;

	if (vector_is_zero(scene->cam.view_point))
		return ;
	scene->light.pos = vector_add(scene->cam.view_point, scene->light.pos);
	obj_list = scene->obj_list;
	while (obj_list)
	{
		switch (obj_list->obj_type)
		{
			case SP:
				sp = (t_sp *)obj_list->obj;
				sp->sp_center = vector_add(scene->cam.view_point, sp->sp_center);
				break;
			case CY:
				cy = (t_cy *)obj_list->obj;
				cy->cy_center = vector_add(scene->cam.view_point, cy->cy_center);
				break;
			case PL:
				pl = (t_pl *)obj_list->obj;
				pl->pl_point = vector_add(scene->cam.view_point, pl->pl_point);
				break;
			default:
				break;
		}
		obj_list = obj_list->next;
	}
	vector_to_zero(&scene->cam.view_point);
}

static int	trace_color(t_point point, t_scene *scene)
{
	return (0);
}

