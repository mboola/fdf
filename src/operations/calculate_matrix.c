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
static void	set_mat(double mat[4][4], t_mat_funct func[4][4], double angl)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = func[i][j](angl);
			j++;
		}
		i++;
	}
}

/*
 *	Creates a matrix with an array of values and a matrix of functions.
 */
static void	set_mat_arr(double mat[4][4], t_mat_funct func[4][4], double *value)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = func[i][j](value[i]);
			j++;
		}
		i++;
	}
}

/*
 *	It firsts rotates the points in each axis, scale them 
 *	and finally translate them. Stores the result in result_mat.
 */
void	calculate_matrix(t_ctrl_prgrm *data, t_shape *shape)
{
	t_space	space;
	double	mat_a[4][4];
	double	mat_b[4][4];
	double	mat_c[4][4];

	space = data->space;
	set_mat(mat_a, space.rotation_x, shape->angle_x);
	set_mat(mat_b, space.rotation_y, shape->angle_y);
	mul_mat(mat_a, mat_b, mat_c);
	set_mat(mat_a, space.rotation_z, shape->angle_z);
	mul_mat(mat_a, mat_c, mat_b);
	set_mat_arr(mat_a, space.scalation, shape->scale);
	mul_mat(mat_a, mat_b, mat_c);
	set_mat_arr(mat_a, space.translation, shape->translate);
	mul_mat(mat_a, mat_c, shape->transformation_matrix);
}
