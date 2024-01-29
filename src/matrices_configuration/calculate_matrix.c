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

/*
 *	Multiplies two matrices and stores the result in a result matrix.
 */
static void	mul_mat(double mat1[4][4], double mat2[4][4], double res[4][4])
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res[i][j] = 0;
			k = 0;
			while (k < 4)
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
static void set_mat(double mat[4][4], s_func rotate[4][4], double angl)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
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
static void set_mat_arr(double mat[4][4], s_func rotate[4][4], double value[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = rotate[i][j](value[i]);
			j++;
		}
		i++;
	}
}

void	print_matrix(double result_mat[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			printf("%1f ", result_mat[i][j]);
		printf("\n");
	}
}

/*
 *	It firsts rotates the points in each axis, scale them 
 *	and finally translate them. Stores the result in result_mat.
 */
void	calculate_matrix(t_mlx_data *mlx_data, double result_mat[4][4])
{
	double	mat_a[4][4];
	double	mat_b[4][4];
	double	mat_c[4][4];

	set_mat(mat_a, mlx_data->rotation_x, mlx_data->angle_x);
	set_mat(mat_b, mlx_data->rotation_y, mlx_data->angle_y);
	mul_mat(mat_a, mat_b, mat_c);
	set_mat(mat_a, mlx_data->rotation_z, mlx_data->angle_z);
	mul_mat(mat_a, mat_c, mat_b);
	set_mat_arr(mat_a, mlx_data->mat_scale, mlx_data->scale);
	mul_mat(mat_a, mat_b, mat_c);
	set_mat_arr(mat_a, mlx_data->mat_translation, mlx_data->offset);
	mul_mat(mat_a, mat_c, result_mat);
}
