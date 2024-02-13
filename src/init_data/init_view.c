/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	set_scale(t_shape *shape)
{
	int		x;
	int		y;
	int		k;
	int		n;
	double	scale;

	x = shape->buffer->n_col;
	y = shape->buffer->n_row;
	k = (WIN_WIDTH / 5) * 3;
	n = (WIN_HEIGHT / 5) * 3;
	if (k / x > n / y)
		scale = n / y;
	else
		scale = k / x;
	if (scale < 0.1)
		scale = 0.1;
	shape->scale[0] = scale;
	shape->scale[1] = scale;
	shape->scale[2] = scale;
}

static void	set_translation(t_shape *shape)
{
	double	x;
	double	y;
	int		h;
	double	angle;
	double	total_angle;

	x = (double) shape->buffer->n_col;
	y = (double) shape->buffer->n_row;
	angle = atan(y / x);
	h = (y * sin(angle)) / 2;
	total_angle = angle + shape->angle_z;
	x = sin(total_angle) * h;
	y = cos(total_angle) * h;
	x = x * shape->scale[0];
	y = y * shape->scale[1];
	shape->translate[0] = WIN_HEIGHT / 2 - y;
	shape->translate[1] = WIN_WIDTH / 2 - x;
	shape->translate[2] = 0;
}

static void	set_view_values(t_camera *camera)
{
	camera->homogeneous_coord = 1;
	camera->view.left = 0;
	camera->view.right = 0;
	camera->view.top = 0;
	camera->view.bottom = 0;
	camera->view.far = 0;
	camera->view.near = 0;
}

void	init_view(t_ctrl_prgrm *data)
{
	t_shape	*shape;

	shape = data->space.shape;
	set_isometric_view(data);
	set_scale(shape);
	set_translation(shape);
	set_view_values(&(data->space.camera));
	init_projection(data->space.camera.projection_matrix);
}
