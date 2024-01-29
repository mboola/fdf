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

static void	initialize_isometric(t_mlx_data *mlx_data)
{
	mlx_data->distorsion = 1;
	mlx_data->conic = 0;
	mlx_data->angle_x = 0.6154729074;
	mlx_data->angle_y = 0.7853981634;
	mlx_data->angle_z = 0.52;
}

static void	initialize_conic(t_mlx_data *mlx_data)
{
	mlx_data->distorsion = 0.9;
	mlx_data->conic = 1;
	mlx_data->angle_x = 0;
	mlx_data->angle_y = 0;
	mlx_data->angle_z = 0;
}

static void	set_scale(t_mlx_data *mlx_data)
{
	int	x;
	int	y;
	int	k;
	int	n;
	int	scale;

	x = mlx_data->pixels.n_col;
	y = mlx_data->pixels.n_row;
	k = (WIN_WIDTH / 5) * 3;
	n = (WIN_HEIGHT / 5) * 3;
	if (k / x > n / y)
		scale = n / y;
	else
		scale = k / x;
	if (scale < 0.1)
		scale = 0.1;
	mlx_data->scale[0] = scale;
	mlx_data->scale[1] = scale;
	mlx_data->scale[2] = scale;
}

static void	set_translation(t_mlx_data *mlx_data)
{
	double	x;
	double	y;
	int	h;
	double	angle;
	double	total_angle;

	x = (double) mlx_data->pixels.n_col;
	y = (double) mlx_data->pixels.n_row;
	angle = atan(y / x);
	h = (y * sin(angle)) / 2;
	total_angle = angle + mlx_data->angle_z;
	x = sin(total_angle) * h;
	y = cos(total_angle) * h;
	x = x * mlx_data->scale[0];
	y = y * mlx_data->scale[1];
	mlx_data->offset[0] = WIN_HEIGHT / 2 - y;
	mlx_data->offset[1] = WIN_WIDTH / 2 - x;
	mlx_data->offset[2] = 0;
}

static void	set_view_values(t_mlx_data *mlx_data)
{
	t_view	view;

	view.top = 5;
	view.down = 1;
	view.left = -2;
	view.right = 2;
	view.far = 10;
	view.near = 2;
	mlx_data->view_values = view;
}

void	initialize_view(t_mlx_data *mlx_data)
{
	if (VIEW)
		initialize_conic(mlx_data);
	else
		initialize_isometric(mlx_data);
	set_scale(mlx_data);
	set_translation(mlx_data);
	set_view_values(mlx_data);
}
