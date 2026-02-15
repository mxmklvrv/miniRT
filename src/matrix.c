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

t_matrix	new_identity_matrix(int	row)
{
	t_matrix	res;
	int			i;

	res = new_matrix(row, row);
	if (!res.ptr)
		return (res);
	i = 0;
	while (i < row)
	{
		res.ptr[i][i] = 1;
		i++;
	}
	return (res);
}

t_matrix	new_submatrix(t_matrix m, int target_row, int target_col)
{
	t_matrix	res;
	int			i;
	int			j;

	if (m.col <= 2 || m.row <= 2)
	{
		ft_putendl_fd("Error: can't create submatrix, matrix is too small", STDERR_FILENO);
		res.ptr = NULL;
		return (res);
	}
	res = new_matrix(m.row - 1, m.col - 1);
	if (!res.ptr)
		return (res);
	j = 0;
	while (j < m.row)
	{
		i = 0;
		while (i < m.col)
		{
			if (i != target_col && j != target_row)
				res.ptr[j - (j > target_row)][i - (i > target_col)] = m.ptr[j][i];
			i++;
		}
		j++;
	}
	return (res);
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

t_matrix	new_matrix_multiply(t_matrix m1, t_matrix m2)
{
	int			i;
	int			j;
	t_matrix	res;
	
	if (m1.col != m2.row)
	{
		ft_putendl_fd("Error: can't multiply, matrices have different dimensions", STDERR_FILENO);
		res.ptr = NULL;
		return (res);
	}
	res = new_matrix(m2.row, m2.col);
	if (!res.ptr)
		return (res);
	j = 0;
	while (j < m1.row)
	{
		i = 0;
		while (i < m2.col)
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

t_vec3	matrix_multiply_by_vector(t_matrix m, t_vec3 v)
{
	t_vec3		res;
	t_matrix	v_m;
	t_matrix	res_m;

	res = new_vector(0, 0, 0);
	v_m = new_matrix(4, 1);
	if (!v_m.ptr)
		return (res);
	v_m.ptr[0][0] = v.x;
	v_m.ptr[1][0] = v.y;
	v_m.ptr[2][0] = v.z;
	v_m.ptr[3][0] = v.w;
	res_m = new_matrix_multiply(m, v_m);
	if (!res_m.ptr)
	{
		free_matrix(v_m);
		return (res);
	}
	res.x = res_m.ptr[0][0];
	res.y = res_m.ptr[1][0];
	res.z = res_m.ptr[2][0];
	res.w = res_m.ptr[3][0];
	free_matrix(v_m);
	free_matrix(res_m);
	return (res);
}

//Can change to return new matrix
void	matrix_transpose(t_matrix m)
{
	int			middle;
	int			i;
	int			j;

	if (m.col != m.row)
	{
		ft_putendl_fd("Error: can't transpose, matrix not symmetrical", STDERR_FILENO);
		return ;
	}
	j = 0;
	i = 0;
	middle = 0;
	while (j < m.col)
	{
		i = middle + 1;
		while (i < m.row)
		{
			ft_swapf(&m.ptr[j][i], &m.ptr[i][j]);
			i++;
		}
		j++;
	}
}

float	matrix_find_determinant(t_matrix m)
{
	int		i;
	float	res;

	if (m.col != m.row)
	{
		ft_putendl_fd("Error: can't find determinant, matrix isn't square", STDERR_FILENO);
		return (0);
	}
	if (m.col == 2 || m.row == 2)
		return (m.ptr[0][0] * m.ptr[1][1] - m.ptr[0][1] * m.ptr[1][0]);
	i = 0;
	res = 0;
	while (i < m.col)
	{
		res += m.ptr[0][i] * matrix_find_cofactor(m, 0, i);
		i++;
	}
	return (res);
}

float	matrix_find_minor(t_matrix m, int row, int col)
{
	t_matrix	sub_m;
	float		res;

	if (m.col > 4 || m.row > 4)
	{
		ft_putendl_fd("Error: can't find minor, matrix bigger than 4x4", STDERR_FILENO);
		return (0);
	}
	sub_m = new_submatrix(m, row, col);
	if (!sub_m.ptr)
		return (0);
	res = matrix_find_determinant(sub_m);
	free_matrix(sub_m);
	return (res);
}

float	matrix_find_cofactor(t_matrix m, int row, int col)
{
	int	sign;

	sign = -1;
	if ((row % 2 == 0) == (col % 2 == 0))
		sign = 1;
	return (sign * matrix_find_minor(m, row, col));
}
