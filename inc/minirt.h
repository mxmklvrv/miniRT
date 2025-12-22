#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "macros.h"
# include "mlx.h"
# include "mlx_int.h"
# include "structs.h"
# include <camera.h>
# include <fcntl.h>
# include <math.h>
# include <scene.h>
# include <sphere.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/stat.h>
# include <vector.h>

int		handle_error(void);
bool	check_args(int argc, char **argv, char **format);
bool	set_visuals(t_vars *vars, t_data *data);
void	free_visuals(t_vars *vars, t_data *data);
void	ft_mlx_put_pixel(t_data *data, t_point point);
void	set_hooks(t_vars *vars);
bool	visuals_loop(char **format);
void	free_format(char **format);

#endif
