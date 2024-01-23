/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_matrix_rotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"


static void	conv_matdouble_matint(double mat_double[3][3], int mat_int[3][3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mat_int[i][j] = (int)round(mat_double[i][j]);
			j++;
		}
		i++;
	}
}

static void	print_matrix(int mat[3][3])
{
	int	i;
	int j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			ft_printf(1, "%d", mat[i][j]);
			j++;
		}
		ft_printf(1, "\n");
		i++;
	}
}

/*
 *	Multiplies two matrices and stores the result in a result matrix.
 */
static void	mul_mat(double mat1[3][3], double mat2[3][3], double res[3][3])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			res[i][j] = 0;
			k = 0;
			while (k < 3)
			{
				res[i][j] += mat1[i][k] * mat2[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
}

/*
 *	Creates a matrix with a value and a matrix of functions.
 */
static void set_mat(double mat[3][3], s_func rotate[3][3], double angl)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mat[i][j] = rotate[i][j](angl);
			j++;
		}
		i++;
	}
}

/*
 *	Creates a matrix with an array of values and a matrix of functions.
 */
static void set_mat_arr(double mat[3][3], s_func rotate[3][3], double value[3])
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mat[i][j] = rotate[i][j](value[i]);
			j++;
		}
		i++;
	}
}

/*
 *	Multiplies rotation, scaling and traslation matrices.
 *	Stores the result in result_mat.
 */
void	calculate_matrix(t_mlx_data *mlx_data, double result_mat[3][3])
{
	double	mat_a[3][3];
	double	mat_b[3][3];
	double	mat_c[3][3];

	set_mat(mat_a, mlx_data->rotation_x, mlx_data->angle_x);
	set_mat(mat_b, mlx_data->rotation_y, mlx_data->angle_y);
	mul_mat(mat_a, mat_b, mat_c);
	set_mat(mat_a, mlx_data->rotation_z, mlx_data->angle_z);
	mul_mat(mat_a, mat_c, mat_b);
	set_mat_arr(mat_a, mlx_data->mat_scale, mlx_data->scale);
	mul_mat(mat_a, mat_b, mat_c);
	set_mat_arr(mat_a, mlx_data->mat_scale, mlx_data->offset);
	mul_mat(mat_a, mat_c, result_mat);
}
