void	draw_scene(t_data *data, t_scene *scene)
{
	t_pixel	pixel;
	//t_ray	ray;

	scene->cam.zoom = get_zoom(scene->cam);//Doesn't change ever(?)
	scene->cam.angle = get_camera_angle(scene->cam);//Can change with movement
	printf("Zoom: %f\nAngle:\nx = %f\ny = %f\nz = %f\n", scene->cam.zoom, 
		scene->cam.angle.x, scene->cam.angle.y, scene->cam.angle.z);
	pixel.j = 0;
	while (pixel.j < HEIGHT)//TODO: add multi threading
	{
		pixel.i = 0;
		while (pixel.i < WIDTH)
		{
			//ray = get_ray_for_position(pixel, scene->cam);
			//pixel.color = trace_color(ray, scene);
			ft_mlx_put_pixel(data, pixel);
			pixel.i++;
		}
		pixel.j++;
	}
}

t_ray	get_ray_for_position(t_pixel pixel, t_cam cam)
{
	t_ray	ray;
	t_vec3	position;
	float	position_width;
	float	position_heigth;

	position_width = (float)(pixel.i - WIDTH / 2) * cam.zoom;
	position_heigth = (float)(pixel.j - HEIGHT / 2) * cam.zoom;
	position.x = position_width * cam.angle.x;
	position.y = position_width * cam.angle.y;
	position.z = position_heigth * cam.angle.z;
	ray.origin = cam.orient.origin;
	ray.direction = vector_add(cam.orient.direction, position);
	return (ray);
}

/*
 * Find how much distance is 1 pixel. Depends on camera field of view,
 * length of camera direction vector and window width or heigth.
 */
float	get_zoom(t_cam cam)
{
	float	zoom;
	float	cam_length;
	float	tan;

	cam_length = vector_length(cam.orient.direction);
	tan = tanf(cam.fov * M_PI / 180 / 2);
	zoom = cam_length * tan * 2 / ft_max(2, WIDTH, 1);
	printf("\nZOOM\nCamera vector len = %f\nAngel = %f\ntan = %f\nZoom = %f\n\n", 
		cam_length, cam.fov / 2, tan, zoom);
	return (zoom);
}