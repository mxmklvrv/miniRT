#include "minirt.h"

static float	matrix_multiply_one(t_matrix m1, t_matrix m2, int row, int col);

t_matrix	new_matrix(int row, int col)
{
	t_matrix	matrix;
	int			i;

	matrix.row = row;
	matrix.col = col;
	matrix.ptr = ft_calloc(row + 1, sizeof(float *));
	if (matrix.ptr)
	{
		i = 0;
		while (i < row)
		{
			matrix.ptr[i] = ft_calloc(col, sizeof(float));
			if (matrix.ptr[i] == NULL)
			{
				free_matrix(matrix);
				break ;
			}
			i++;
		}
	}
	return (matrix);
}

void	free_matrix(t_matrix matrix)
{
	int	i;

	i = 0;
	while (matrix.ptr && matrix.ptr[i])
	{
		free(matrix.ptr[i]);
		matrix.ptr[i] = NULL;
		i++;
	}
	free(matrix.ptr);
	matrix.ptr = NULL;
}

bool	matrix_is_equal(t_matrix m1, t_matrix m2)
{
	int	i;
	int	j;

	if (!m1.ptr || !m2.ptr)
	{
		ft_putendl_fd("Error: matrix is NULL", STDERR_FILENO);
		return (false);
	}
	if (!matrix_has_equal_dimensions(m1, m2))
	{
		ft_putendl_fd("Error: matricces are not comparable", STDERR_FILENO);
		return (false);
	}
	j = 0;
	while (j < m1.row)
	{
		i = 0;
		while (i < m1.col)
		{
			if (m1.ptr[j][i] != m2.ptr[j][i])
				return (false);
			i++;
		}
		j++;
	}
	return (true);
}

bool	matrix_has_equal_dimensions(t_matrix m1, t_matrix m2)
{
	return (m1.col == m2.col && m1.row == m2.row);
}

t_matrix	matrix_multiply(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	t_matrix	res;
	
	res = new_matrix(m1.row, m1.col);
	if (!res.ptr)
		return (res);
	if (m1.col != m2.row || m1.row != m2.col)
	{
		ft_putendl_fd("Error: can't multiply, matrices have different dimensions", STDERR_FILENO);
		free_matrix(res);
		return (res);
	}
	j = 0;
	while (j < m1.row)
	{
		i = 0;
		while (i < m1.col)
		{
			res.ptr[j][i] = matrix_multiply_one(m1, m2, j, i);
			i++;
		}
		j++;
	}
	return (res);
}

static float	matrix_multiply_one(t_matrix m1, t_matrix m2, int row, int col)
{
	int		i;
	float	res;

	res = 0;
	i = 0;
	while (i < m1.col)
	{
		res += m1.ptr[row][i] * m2.ptr[i][col];
		i++;
	}
	return (res);
}
