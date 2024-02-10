/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_matrices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static double	return_one()
{
	return (1);
}

static double	return_zero()
{
	return (0);
}

static void init_projection(t_proj projection_matrix[4][4])
{
	projection_matrix[0][0] = return_one;
	projection_matrix[0][1] = return_zero;
	projection_matrix[0][2] = return_zero;
	projection_matrix[0][3] = return_zero;
	projection_matrix[1][0] = return_zero;
	projection_matrix[1][1] = return_one;
	projection_matrix[1][2] = return_zero;
	projection_matrix[1][3] = return_zero;
	projection_matrix[2][0] = return_zero;
	projection_matrix[2][1] = return_zero;
	projection_matrix[2][2] = return_zero;
	projection_matrix[2][3] = return_zero;
	projection_matrix[3][0] = return_zero;
	projection_matrix[3][1] = return_zero;
	projection_matrix[3][2] = return_zero;
	projection_matrix[3][3] = return_zero;
}

//TODO: change this
void	init_camera(t_camera *camera)
{
	init_projection(camera->projection_matrix);
	camera->homogeneous_coord = 1;
	camera->angle_x = 0;
	camera->angle_y = 0;
	camera->angle_z = 0;
	camera->view.left = 0;
	camera->view.right = 0;
	camera->view.top = 0;
	camera->view.bottom = 0;
	camera->view.far = 0;
	camera->view.near = 0;
}