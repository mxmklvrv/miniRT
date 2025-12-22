#include "minirt.h"

static int	key_exit_hook(int key, t_vars *vars);

void	set_hooks(t_vars *vars)
{
	mlx_key_hook(vars->win, key_exit_hook, vars);
	mlx_hook(vars->win, ON_DESTROY, 0, mlx_loop_end, vars->mlx);
}

static int	key_exit_hook(int key, t_vars *vars)
{
	if (key == ESCAPE)
		mlx_loop_end(vars->mlx);
	return (EXIT_SUCCESS);
}
