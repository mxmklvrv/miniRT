#include "minirt.h"

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 2: Read lines from input file with  gnl(need to change version)
// Trims spaces and newlines
// Passes trimmed line to dispatcher
// Based on identifier C L A sp pl cy to corresponding parsing function

// if ch == C -> pars_cam
// if ch == L -> pars_lignt
// if ch == A -> pars_ambient
// need to know that we have 1 of each, else, err
int	parse_input_file(char *file, t_scene *scene)
{
	int		fd;
	int		check;
	char	*line;
	char	*trimmed;

	check = 1;
	init_scene(scene);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (error("cannot open file for reading"), 1);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \n");
		free(line);
		if (!trimmed)
		{
			close(fd);
			return (error(ERR_ALLOC), 1);
		}
		check = dispatch(trimmed, scene);
		free(trimmed);
		if (check != 0)
		{
			close(fd);
			return (1);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
	// another func to check amb/cam/light
	// should have qty == 1 of each.
}

void	init_scene(t_scene *scene)
{
	scene->obj_list = NULL;
	scene->qt_ambiant = 0;
	scene->qt_cam = 0;
	scene->qt_light = 0;
}

int	dispatch(char *line, t_scene *scene)
{
	while (*line == ' ') // what about tabs here ??
	line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	else if (ft_strchr("CAL", *line))
		return (parse_cam_light(line, *line, scene));
	else if (ft_strncmp(line, "sp", 2) == 0)
	{
		line += 2;
		return (parse_sphere(line, scene));
	}
	else if (ft_strncmp(line, "pl", 2) == 0)
	{
		line += 2;
		return (parse_plane(line, scene));
	}
	else if (ft_strncmp(line, "cy", 2) == 0)
	{
		line += 2;
		return (parse_cylinder(line, scene));
	}
	else
		return (error("Unknown char detected in .rt"), 1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 3: Main parsing functions for Cam Ambient Light
// Extracting basic data

// refractors below
//<0,2 255,255,255>
int	parse_cam_light(char *line, char ch, t_scene *scene)
{
	if (ch == 'C')
	{
		scene->qt_cam++;
		return (parse_cam(++line, scene));
	}
	else if (ch == 'A')
	{
		scene->qt_ambiant++;
		return (parse_ambient(++line, scene));
	}
	else if (ch == 'L')
	{
		scene->qt_light++;
		return (parse_light(++line, scene));
	}
	// we need a func to count CAL at the end of pars
	return (0);
}

int	parse_cam(char *line, t_scene *scene)
{
	char	**res;
	float	fov;

	if (scene->qt_cam > 1)
		return (error("Only 1 camera is alowed"), 1);
	if (count_elements(line) != 3)
		return (error("Wrong specs for camera"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	if (parse_vector(res[0], &scene->cam.view_point, -100.0f, 100.0f) == 1)
		return (error("Invalid camera view point"), free_array(res), 1);
	if (parse_vector(res[1], &scene->cam.orient, 0.0f, 1.0f) == 1)
		return (error("Invalid camera orientation"), free_array(res), 1);
	fov = 0;
	if (parse_float(res[2], 0.0f, 180.0f, &fov) == 1)
		return (error("Invalid camera FOV"), free_array(res), 1);
	scene->cam.fov = fov;
	free_array(res);
	return (0);
}

int	parse_ambient(char *line, t_scene *scene)
{
	char	**res;
	float	ratio;
	int		colour;

	if (scene->qt_ambiant > 1)
		return (error("Only 1 Ambient is allowed"), 1);
	if (count_elements(line) != 2)
		return (error("Wrong Ambient specs"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	ratio = 0.0f;
	colour = 0;
	if (parse_float(res[0], 0.0f, 1.0f, &ratio) == 1)
		return (error("Invalid Ambient ratio"), free_array(res), 1);
	if (parse_rgb(res[1], &colour) == 1)
		return (error("Invalid Ambient colour"), free_array(res), 1);
	scene->ambient.amb = ratio;
	scene->ambient.colour = colour;
	free_array(res);
	return (0);
}

int	parse_light(char *line, t_scene *scene)
{
	char	**res;
	float	bright;
	int		colour;

	if (scene->qt_light > 1)
		return (error("Only 1 light is allowed"), 1);
	if (count_elements(line) != 3) // or 2 for mandotary
		return (error("Invalid light specs"), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), 1);
	bright = 0.0f;
	colour = 0;
	if (parse_vector(res[0], &scene->light.pos, -100.0f, 100.0f) == 1)
		return (error("Invalid light position"), free_array(res), 1);
	if (parse_float(res[1], 0.0f, 1.0f, &bright) == 1)
		return (error("Invalid light brightness"), free_array(res), 1);
	if (parse_rgb(res[2], &colour) == 1) // this is for bonus
		return (error("Invalid light colour"), free_array(res), 1);
	scene->light.bright = bright;
	scene->light.color = colour; // this is for bonus
	free_array(res);
	return (0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
// STEP 4: Main parsing functions for sphere cylinder plane
// Extracting basic data
// Adding each to the linked list of objects

// 0.0,0.0,20.6 12.6 10,0,255
int	parse_sphere(char *line, t_scene *scene)
{
	char	**res;
	t_sp	*sphere;
	float	diameter;
	int		colour;

	if (count_elements(line) != 3)
		return (error("Invalid specs for sphere"), 1);
	sphere = malloc(sizeof(t_sp));
	if (!sphere)
		return (error(ERR_ALLOC), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), free(sphere), 1);
	if (parse_vector(res[0], &sphere->sp_center, -100.0f, 100.0f) == 1)
		return (error("Invalid sphere center"), free(sphere), free_array(res),
			1);
	diameter = 0;
	colour = 0;
	if (parse_float(res[1], 0.0f, 100.0f, &diameter) == 1)
		return (error("Invalid sphere diameter"), free(sphere), free_array(res),
			1);
	if (parse_rgb(res[2], &colour) == 1)
		return (error("Invalid sphere colour"), free(sphere), free_array(res),
			1);
	sphere->diameter = diameter;
	sphere->colour = colour;
	if (add_to_list(&scene->obj_list, sphere, SP, sphere->colour) == 1)
		return (error("Failed adding sphere to the list"), free_array(res),
			free(sphere), 1);
	printf("SPHERE\n");
	printf("cent %f %f %f\n", sphere->sp_center.x, sphere->sp_center.y,
		sphere->sp_center.z);
	printf("diam %f\n", sphere->diameter);
	printf("color %d\n\n", sphere->colour);
	return (free_array(res), 0);
}

// 0.0,0.0,-10.0  0.0,1.0,0.0  0,0,225
int	parse_plane(char *line, t_scene *scene)
{
	char	**res;
	t_pl	*plane;
	int		colour;

	if (count_elements(line) != 3)
		return (error("Invalid specs for plane"), 1);
	plane = malloc(sizeof(t_pl));
	if (!plane)
		return (error(ERR_ALLOC), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), free(plane), 1);
	if (parse_vector(res[0], &plane->pl_point, -100.0f, 100.0f) == 1)
		return (error("Invalid coordinates of a point in plane"), free(plane),
			free_array(res), 1);
	if (parse_vector(res[1], &plane->normal, 0.0f, 1.0f) == 1)
		return (error("Invalid normal vector for plane"), free(plane),
			free_array(res), 1);
	colour = 0;
	if (parse_rgb(res[2], &colour) == 1)
		return (error("Invalid plane colour"), free(plane), free_array(res), 1);
	plane->colour = colour;
	if (add_to_list(&scene->obj_list, plane, PL, plane->colour) == 1)
		return (error("Failed adding plane to the list"), free(plane),
			free_array(res), 1);
	printf("PLANE\n");
	printf("pl point %f %f %f\n", plane->pl_point.x, plane->pl_point.y,
		plane->pl_point.z);
	printf("norm %f %f %f\n", plane->normal.x, plane->normal.y,
		plane->normal.z);
	printf("color %d\n\n", plane->colour);
	return (free_array(res), 0);
}
// 50.0,0.0,20.6    0.0,0.0,1.0    14.2    21.42   10,0,255
int	parse_cylinder(char *line, t_scene *scene)
{
	char	**res;
	t_cy	*cylinder;
	float	diameter;
	float	height;
	int		colour;

	if (count_elements(line) != 5)
		return (error("Invalid specs for cylinder"), 1);
	cylinder = malloc(sizeof(t_cy));
	if (!cylinder)
		return (error(ERR_ALLOC), 1);
	res = ft_split(line, ' ');
	if (!res)
		return (error(ERR_ALLOC), free(cylinder), 1);
	if (parse_vector(res[0], &cylinder->cy_center, -100.0f, 100.0f) == 1)
		return (error("Invalid coordinates of the center of the cylinder"),
			free(cylinder), free_array(res), 1);
	if (parse_vector(res[1], &cylinder->normal, 0.0f, 1.0f) == 1)
		return (error("Invalid coordinates of the center of the cylinder"),
			free(cylinder), free_array(res), 1);
	diameter = 0.0f;
	height = 0.0f;
	colour = 0;
	if (parse_float(res[2], 0.0f, 100.0f, &diameter) == 1)
		return (error("Invalid cylinder diameter"), free(cylinder),
			free_array(res), 1);
	if (parse_float(res[3], 0.0f, 100.0f, &height) == 1)
		return (error("Invalid cylinder height"), free(cylinder),
			free_array(res), 1);
	if (parse_rgb(res[4], &colour) == 1)
		return (error("Invalid cylinder colour"), free(cylinder),
			free_array(res), 1);
	cylinder->diameter = diameter;
	cylinder->height = height;
	cylinder->colour = colour;
	if (add_to_list(&scene->obj_list, cylinder, CY, cylinder->colour) == 1)
		return (error("Failed adding cylinder to the list"), free(cylinder),
			free_array(res), 1);
	printf("CYLINDR\n");
	printf("cy cent %f %f %f\n", cylinder->cy_center.x, cylinder->cy_center.y,
		cylinder->cy_center.z);
	printf("norm %f %f %f\n", cylinder->normal.x, cylinder->normal.y,
		cylinder->normal.z);
	printf("diam %f\n", cylinder->diameter);
	printf("height %f", cylinder->height);
	printf("color %d\n\n", cylinder->colour);
	free_array(res);
	return (0);
}