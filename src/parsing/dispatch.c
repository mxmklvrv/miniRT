#include "minirt.h"

// STEP 2: Read lines from input file with  gnl(need to change version)
// Trims spaces and newlines
// Passes trimmed line to dispatcher
// Based on identifier C L A sp pl cy to corresponding parsing function

// if ch == C -> pars_cam
// if ch == L -> pars_lignt
// if ch == A -> pars_ambient
// need to know that we have 1 of each, else, err
int	pars_cam_light(char *line, char ch, t_scene *scene)
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
	return (0);
}

int	dispatch(char *line, t_scene *scene)
{
	if (ft_strchr("CAL", *line))
		return (pars_cam_light(line, *line, scene));
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
		return (error("Unknown char detected in .rt", scene->err_m), 1);
}
