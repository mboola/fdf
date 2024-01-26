/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_points.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

/*
 *  We get the new point.
 */
static void	multiply_matrix(double mat[4][4], int point[4], double point_p[4])
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		point_p[i] = 0;
		j = 0;
		while (j < 4)
		{
			point_p[i] += mat[i][j] * (double)point[j];
			j++;
		}
		i++;
	}
}

/*
 *	We multiply our point to the matrix to get the new coordenates.
 *	We then project it.
 */
static void	mul_and_project(int point[4], double mat[4][4],
		s_proj mat_proj[4][4], int res[4])
{
	double	new_point[4];

	multiply_matrix(mat, point, new_point);
	res[0] = mat_proj[0][0](new_point[0]);
	res[1] = mat_proj[1][1](new_point[1]);
	res[2] = 0;
	res[3] = 0;
}

/*
 *	Recieves an array of 3d points and converts them to points from our current
 *	vision point. It then projects them into our 2d screen.
 */
void	convert_points(t_point *points_3d, t_mlx_data *mlx_data,
	double mat[4][4], int row)
{
	int			i;
	int			coord[4];
	t_vector2	vector2;
	t_vector2	*mem;

	i = 0;
	while (points_3d[i].vector[0] != -1)	//while not end of array
	{
		printf("Point before: %d, %d, %d\n", points_3d[i].vector[0], points_3d[i].vector[1], points_3d[i].vector[2]);
		mul_and_project(points_3d[i].vector, mat, mlx_data->mat_proj, coord);
		printf("Point after: %d, %d\n", coord[0], coord[1]);
		vector2.coord[0] = coord[0];
		vector2.coord[1] = coord[1];
		vector2.color = points_3d[i].color;
		mem = (t_vector2 *)(mlx_data->pixels.points[row]);
		mem[i] = vector2;
		//ft_printf(1, "X=%d, Y=%d\n", vector[0], vector[1]);
		i++;
	}
}
