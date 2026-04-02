/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akolupae <akolupae@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 21:02:49 by akolupae          #+#    #+#             */
/*   Updated: 2026/04/01 21:02:51 by akolupae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

void	setup_camera_angle(t_cam *cam);

int		confirm_input(int ac, char **av);
int		parse_input_file(char *file, t_scene *scene);
int		dispatch(char *line, t_scene *scene);
int		parse_cam(char *line, t_scene *scene);
int		parse_ambient(char *line, t_scene *scene);
int		parse_light(char *line, t_scene *scene);
int		parse_cylinder(char *line, t_scene *scene);
int		parse_plane(char *line, t_scene *scene);
int		parse_sphere(char *line, t_scene *scene);

int		ft_atof(const char *line, float *res);
int		ft_atoi_and_overflow(const char *nptr, int *overflow);
int		parse_int(char *str, int min, int max, int *res);
int		parse_float(char *str, float min, float max, float *res);
int		parse_vector(char *str, t_vec3 *vector, float min, float max);
int		parse_rgb(char *str, int *color);

int		parse_error(t_scene *scene, char *msg, char **res, void *ptr);
int		parse_fatal(t_scene *scene, int fd);
int		error_return(char *msg, char *line);
void	error_msg(char *msg, char *line);

void	free_array(char **arr);
void	free_scene(t_scene *scene);

void	free_list(t_olist *list);

int		add_to_list(t_scene *scene, t_shape *shape);
int		add_light_to_list(t_scene *scene, t_light *light);

int		count_elements(char *line);
int		is_valid_int(char *line);
int		is_valid_float(char *line);
int		is_valid_comas(const char *line);
int		ft_isspace(char ch);

#endif
