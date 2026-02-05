#include "minirt.h"

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
		printf("Error: matrix is NULL\n");
		return (false);
	}
	if (m1.col != m2.col || m1.row != m2.row)
	{
		printf("Error: matricces are not comparable\n");
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
