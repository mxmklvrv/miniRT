#include "minirt.h"


// will expand for sure later, depending on needs.
void	set_to_null(t_rt *rt)
{
	rt->mlx = NULL;
	rt->window = NULL;
}

// void	pars_input(int ac, char **av, t_rt *rt)
// {
// }

void	error_exit(char *msg)
{
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
bool	rt_file_extension(char *filename)
{
	size_t	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 3)
		return (false);
	if (ft_strncmp(filename + len - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

void	confirm_input(int ac, char **av)
{
	if (ac != 2)
		error_exit(ERR_AC);
	if (!rt_file_extension(av[1]))
		error_exit(ERR_EXT);
	printf("cool");
}

int	main(int ac, char **av)
{
	// t_rt rt;

	// set_to_null(&rt);
	confirm_input(ac, av);
	// pars_input(ac, av, &rt);
}