/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_points.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	multiply_matrix_double(double mat[4][4], double point[4],
	double point_p[4])
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
			point_p[i] += mat[i][j] * point[j];
			j++;
		}
		i++;
	}
}

static void	set_mat(double mat[4][4], t_proj proj[4][4], t_view view)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mat[i][j] = proj[i][j](view);
			j++;
		}
		i++;
	}
}

/*
 *	We multiply our point to the matrix to get the new coordenates.
 *	We then project it.
 */
static void	mul_and_project(int cartesian_coord[3], double mat[4][4],
		t_camera *camera, int normalized[3])
{
	double	homogeneous_coordinates[4];
	double	point_to_project[4];
	double	projected_point[4];
	double	mat_proj[4][4];

	homogeneous_coordinates[0] = (double) cartesian_coord[0];
	homogeneous_coordinates[1] = (double) cartesian_coord[1];
	homogeneous_coordinates[2] = (double) cartesian_coord[2];
	homogeneous_coordinates[3] = camera->homogeneous_coord;
	set_mat(mat_proj, camera->projection_matrix, camera->view);
	multiply_matrix_double(mat, homogeneous_coordinates, point_to_project);
	multiply_matrix_double(mat_proj, point_to_project, projected_point);
	normalized[0] = (int) projected_point[0];
	normalized[1] = (int) projected_point[1];
	normalized[2] = (int) projected_point[2];
}

/*
 *	Recieves an array of 3d points and converts them to points from our current
 *	vision point. It then projects them into our 2d screen.
 */
void	buffer_points(t_point *points_3d, t_shape *shape, t_ctrl_prgrm *data,
	int row)
{
	int			i;
	int			coord[3];
	t_projected	vector2;
	t_projected	*mem;

	i = 0;
	while (points_3d[i].vector[0] != -1)
	{
		mul_and_project(points_3d[i].vector, shape->transformation_matrix,
			&(data->space.camera), coord);
		vector2.coord[0] = coord[0];
		vector2.coord[1] = coord[1];
		vector2.color = points_3d[i].color;
		mem = (t_projected *)(shape->buffer->points[row]);
		mem[i] = vector2;
		i++;
	}
}
