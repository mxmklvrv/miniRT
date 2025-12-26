#include "minirt.h"

// below maxim

void	error_exit(char *msg)
{
	ft_putendl_fd(ERR_MSG, 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

// first time opne to count numb of strs in file
// so we can allocate necessary memmory to store strs
int	count_file_strs(char *file)
{
	int		fd;
	int		res;
	char	*str;

	res = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	str = get_next_line(fd);
	while (str)
	{
		if (str[0] != '\0' && str[0] != '\n' && str[0] != '#')
			res++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (res);
}

void	pars_input_file(char *file, t_mrt *rt)
{
	int		str_num;
	//char	**strings;

	str_num = count_file_strs(file);
	if (str_num < 0)
	{
		free(rt); // for now
		error_exit("Cannot open file");
	}
	printf("%d ", str_num);
	// open agaim, malloc mem * str_num
	// sabe them
}


bool	rt_file_extension(char *file)
{
	size_t	len;

	if (!file)
		return (false);
	len = ft_strlen(file);
	if (len < 3)
		return (false);
	if (ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

void	confirm_input(int ac, char **av)
{
	if (ac != 2)
		error_exit(ERR_AC);
	if (!rt_file_extension(av[1]))
		error_exit(ERR_EXT);
}

int	main(int ac, char **av)
{
	t_mrt	*rt;

	confirm_input(ac, av);
	rt = ft_calloc(1, sizeof(t_mrt));
	if (!rt)
		error_exit(ERR_ALLOC);
	pars_input_file(av[1], rt);
}
