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

static void set_mat(double mat[3][3], s_rot_function rotate[3][3], double angl)
{
	mat[0][0] = rotate[0][0](angl);
	mat[0][1] = rotate[0][1](angl);
	mat[0][2] = rotate[0][2](angl);
	mat[1][0] = rotate[1][0](angl);
	mat[1][1] = rotate[1][1](angl);
	mat[1][2] = rotate[1][2](angl);
	mat[2][0] = rotate[2][0](angl);
	mat[2][1] = rotate[2][1](angl);
	mat[2][2] = rotate[2][2](angl);
}

static void	mult_matrix(double mat1[3][3], double mat2[3][3], double res[3][3])
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

void	obtain_rotation_matrix(t_mlx_data *mlx_data, double rotation_mat[3][3])
{
	double	mat_x[3][3];
	double	mat_y[3][3];
	double	mat_z[3][3];
	double	mat_res[3][3];

	set_mat(mat_x, mlx_data->rotation_x, mlx_data->angle_x);
	set_mat(mat_y, mlx_data->rotation_y, mlx_data->angle_y);
	set_mat(mat_z, mlx_data->rotation_z, mlx_data->angle_z);
	mult_matrix(mat_x, mat_y, mat_res);
	mult_matrix(mat_res, mat_z, rotation_mat);
	//conv_matdouble_matint(mat_z, rotation_mat);
}
