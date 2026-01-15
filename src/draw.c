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
	void	*obj;

	if (vector_is_zero(scene->cam.view_point))
		return ;
	obj_list = scene->obj_list;
	while (obj_list)
	{
		switch (obj_list->obj_type)
		{
			case SP:
				(t_sp *)obj = (t_sp *)obj_list->obj;
				obj->sp_center = vector_add(scene->cam.view_point, obj->sp_center);
				break;
			case CY:
				(t_cy *)obj = (t_cy *)obj_list->obj;
				obj->cy_center = vector_add(scene->cam.view_point, obj->cy_center);
				break;
			case PL:
				(t_pl *)obj = (t_pl *)obj_list->obj;
				obj->pl_point = vector_add(scene->cam.view_point, obj->pl_point);
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

