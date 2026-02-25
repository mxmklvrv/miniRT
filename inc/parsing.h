#ifndef PARSING_H
# define PARSING_H

int		add_to_list(t_olist **list, void *object, t_otype type, int colour);
void	free_list(t_olist *list);
t_vec3	creat_vec3(float x, float y, float z);
void	free_array(char **arr);
void	error(char *msg, char *line);
int		count_elements(char *line);
int		is_valid_int(char *line);
int		is_valid_float(char *line);
int		ft_isspace(char ch);
int		is_valid_comas(const char *line);
int		ft_rgbtoint(int transp, int red, int green, int blue);
int		ft_atof(const char *line, float *res);
void	get_whole_part(const char *line, int *i, float *temp, int *overflow);
void	get_fraction_part(const char *line, int *i, float *temp, int *overflow);
int		parse_rgb(char *str, int *color);
int		parse_vector(char *str, t_vec3 *vector, float min, float max);
int		parse_int(char *str, int min, int max, int *res);
int		parse_float(char *str, float min, float max, float *res);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_ambient(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_cam(char *line, t_scene *scene);
int		parse_cam_light(char *line, char ch, t_scene *scene);
int		dispatch(char *line, t_scene *scene);
int		parse_input_file(char *file, t_scene *scene);
int		confirm_input(int ac, char **av);
void	init_scene(t_scene *scene);
void	free_scene(t_scene *scene);

#endif