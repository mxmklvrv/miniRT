#ifndef MINIRT_H
# define MINIRT_H

# include "macros.h"
# include "structs.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"

# include <stdio.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

int		confirm_input(int ac, char **av);

/* ===== Parser ============================================================= */
int		parse_input_file(char *file, t_scene *scene);
int		dispatch(char *line, t_scene *scene);
int		parse_cam_light(char *line, char ch, t_scene *scene);
int		parse_cam(char *line, t_scene *scene);
int		parse_ambient(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);

/* ===== Parser uitls ======================================================= */
void	init_scene(t_scene *scene);
void	free_scene(t_scene *scene);
int		add_to_list(t_olist **list, void *object, t_otype type, int colour);
void	free_list(t_olist *list);
t_vec3	creat_vec3(float x, float y, float z);
void	free_array(char **arr);
void	error(char *msg);
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

/* ===== Visuals ============================================================ */
bool	visuals_loop(t_scene *scene);
bool	set_visuals(t_data *data);
void	free_visuals(t_data *data);
void	ft_mlx_put_pixel(t_data *data, t_pixel pixel);
void	set_hooks(t_data *data);
void	redraw_scene(t_data *data, t_scene *scene);

/* ===== Render ============================================================= */
void	draw_scene(t_data *data, t_scene *scene);

/* ===== Shapes math ======================================================== */
int		hit_sp(t_ray cam, t_sp *sp);
int		hit_cy(t_ray cam, t_cy *cy);
int		hit_pl(t_ray cam, t_pl *pl);

/* ===== Vector math ======================================================== */
t_vec3	new_vector(float x, float y, float z);
t_vec3	new_point(float x, float y, float z);
bool	is_point(t_vec3 vec);
t_vec3	vector_negate(t_vec3 v);
t_vec3	vector_add(t_vec3 v1, t_vec3 v2);
t_vec3	vector_substract(t_vec3 v1, t_vec3 v2);
t_vec3	vector_multiply(t_vec3 v, float scalar);
t_vec3	vector_divide(t_vec3 v, float scalar);
float	vector_magnitude(t_vec3 v);
t_vec3	vector_normalize(t_vec3 v);
float	vector_dot(t_vec3 v1, t_vec3 v2);
t_vec3	vector_cross(t_vec3 v1, t_vec3 v2);
float	degrees_to_radians(float degrees);

/* ===== Color ============================================================== */
int	new_color(int opacity, int red, int green, int blue);
int	get_opacity(int color);
int	get_red(int color);
int	get_green(int color);
int	get_blue(int color);
int	color_add(int c1, int c2);
int	color_substract(int c1, int c2);
int	color_multiply(int color, int scalar);


// test functions
void	print_vars(t_scene *scene);
void	print_list(t_scene *scene);

#endif
