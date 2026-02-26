#ifndef MINIRT_H
# define MINIRT_H

# include "macros.h"
# include "structs.h"
# include "libft.h"
# include "mlx.h"
# include "mlx_int.h"
# include "parsing.h"

# include <stdio.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

// test
void	print_pos(t_scene *scene);
// test

/* ===== Visuals ============================================================ */
bool	visuals_loop(t_scene *scene);
bool	set_visuals(t_data *data);
void	free_visuals(t_data *data);
void	ft_mlx_put_pixel(t_data *data, t_pixel pixel);
void	set_hooks(t_data *data);
void	redraw_scene(t_data *data);

/* ===== Hooks ============================================================== */
int	key_press_hook(int key, t_data *data);
int	key_release_hook(int key, t_data *data);
int	render_hook(t_data *data);
void	set_general_keys(int key, t_data *data);
void	set_translation_keys(int key, t_move_state *move, int value);
void	set_rotation_keys(int key, t_move_state *move, int value);
void	set_resize_keys(int key, t_move_state *move, int value);
void	select_object(t_scene *scene);
void	translate_object(t_olist *node, t_vec3 move_vec);
void	translate_cam(t_cam *cam, t_vec3 move_vec);
void	rotate_cam(t_cam *cam, float angle, t_axis axis);
void	apply_movement(t_data *data);
int	handle_translation(t_data *data);
int	handle_rotation(t_data *data);
void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis);
void	rotate_objects(t_olist *node, float angle, t_axis axis);
t_vec3	rotate_y(t_vec3 current, float angle);
t_vec3	rotate_x(t_vec3 current, float angle);
int	handle_resize(t_data *data);
int	resize_diameter(t_olist *node, float value);
int	resize_height(t_olist *node, float value);

/* ===== Hooks on release ============================================================== */
// int	key_press_hook(int key, t_data *data);
// int	key_release_hook(int key, t_data *data);
// int	handle_translation(int key, t_data *data);
// int	handle_rotation(int key, t_data *data);
// int	handle_resize(int key, t_data *data);
// void	rotate_obj_or_cam(t_data *data, float angle, t_axis axis);
// void	select_object(t_scene *scene);
// void	translate_object(t_olist *node, t_vec3 move_vec);
// void	rotate_objects(t_olist *node, float angle, t_axis axis);
// void	rotate_cam(t_cam *cam, float angle, t_axis axis);
// void	translate_cam(t_cam *cam, t_vec3 move_vec);
// int	resize_diameter(t_olist *node, float value);
// int	resize_height(t_olist *node, float value);
// t_vec3	rotate_y(t_vec3 current, float angle);
// t_vec3	rotate_x(t_vec3 current, float angle);

/* ===== Render ============================================================= */
void	draw_scene(t_data *data);
void	setup_scene(t_scene *scene);
void	setup_camera_angle(t_cam *cam);
void	setup_object_matrix(t_olist *obj_list);
t_vec3	get_direction_for_position(t_pixel pixel, t_cam cam);
int		trace_color(t_ray ray, t_scene *scene);
bool	is_closest(t_intersection intersection, int *closest);
void	set_matrix(t_matrix *old_m, t_matrix new_m);

/* ===== Vector math ======================================================== */
t_vec3	new_vector(float x, float y, float z);
t_vec3	new_point(float x, float y, float z);
bool	is_point(t_vec3 v);
bool	is_equalf(float f1, float f2);
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

/* ===== Matrix math ======================================================== */
t_matrix	new_matrix(int row, int col);
t_matrix	new_identity_matrix(int	row);
t_matrix	new_submatrix(t_matrix m, int target_row, int target_col);
t_matrix	new_inverse_matrix(t_matrix m);
t_matrix	new_translation_matrix(float x, float y, float z);
t_matrix	new_scaling_matrix(float x, float y, float z);
t_matrix	new_rotation_x_matrix(float radians);
t_matrix	new_rotation_y_matrix(float radians);
t_matrix	new_rotation_z_matrix(float radians);
t_matrix	new_shearing_matrix(t_vec3 x, t_vec3 y, t_vec3 z);
t_matrix	new_matrix_multiply(t_matrix m1, t_matrix m2);
void		free_matrix(t_matrix matrix);
bool		matrix_is_equal(t_matrix m1, t_matrix m2);
bool		matrix_has_equal_dimensions(t_matrix m1, t_matrix m2);
t_vec3		matrix_multiply_by_vector(t_matrix m, t_vec3 v);
void		matrix_transpose(t_matrix m);
float		matrix_find_determinant(t_matrix m);
float		matrix_find_minor(t_matrix m, int row, int col);
float		matrix_find_cofactor(t_matrix m, int row, int col);
bool	    matrix_is_invertible(t_matrix m, float *determinant);

/* ===== Rays =============================================================== */
t_ray	new_ray(t_vec3 origin, t_vec3 direction);
t_ray	ray_transform(t_ray r, t_matrix m);
t_ray	ray_transform_inverse(t_ray r, t_matrix m);

/* ===== Shapes math ======================================================== */
t_intersection	hit_sp(t_ray cam, t_sp *sp);
t_intersection	hit_cy(t_ray cam, t_cy *cy);
t_intersection	hit_pl(t_ray cam, t_pl *pl);
float	degrees_to_radians(float degrees);

/* ===== Color ============================================================== */
int		new_color(int opacity, int red, int green, int blue);
int		get_opacity(int color);
int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
int		color_add(int c1, int c2);
int		color_substract(int c1, int c2);
int		color_multiply(int c, float scalar);
int		color_mix(int c1, int c2);



// test functions
void	print_vars(t_scene *scene);
void	print_list(t_scene *scene);
void	print_vector(t_vec3	vector);
void	print_ray(t_ray	ray);
void	print_color(int color);
void	print_matrix(t_matrix matrix);
void	print_intersection(t_intersection intersection);

#endif
