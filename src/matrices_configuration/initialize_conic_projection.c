/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_projection.c                                   :+:      :+:    :+:   */
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

static double	one_one(t_view view)
{
	double	value;

	value = view.right - view.left;
	if (value == 0)
		return (0);
	return (2 / value);
}

static double	two_two(t_view view)
{
	double	value;

	value = view.top - view.down;
	if (value == 0)
		return (0);
	return (2 / value);
}

static double	three_three(t_view view)
{
	double	value;

	value = view.far - view.near;
	if (value == 0)
		return (0);
	return (-2 / value);
}

static double	one_four(t_view view)
{
	double	value;

	value = view.right - view.left;
	if (value == 0)
		return (0);
	return ((view.right + view.left) / value);
}

static double	two_four(t_view view)
{
	double	value;

	value = view.top - view.down;
	if (value == 0)
		return (0);
	return ((view.top + view.down) / value);
}

static double	three_four(t_view view)
{
	double	value;

	value = view.far - view.near;
	if (value == 0)
		return (0);
	return ((view.far + view.near) / value);
}

void	initialize_conic_projection(t_mlx_data *mlx_data)
{
	mlx_data->mat_proj[0][0] = one_one;
	mlx_data->mat_proj[0][1] = return_zero;
	mlx_data->mat_proj[0][2] = return_zero;
	mlx_data->mat_proj[0][3] = return_zero;
	mlx_data->mat_proj[1][0] = one_four;
	mlx_data->mat_proj[1][1] = two_two;
	mlx_data->mat_proj[1][2] = return_zero;
	mlx_data->mat_proj[1][3] = two_four;
	mlx_data->mat_proj[2][0] = return_zero;
	mlx_data->mat_proj[2][1] = return_zero;
	mlx_data->mat_proj[2][2] = three_three;
	mlx_data->mat_proj[2][3] = three_four;
	mlx_data->mat_proj[3][0] = return_one;
	mlx_data->mat_proj[3][1] = return_zero;
	mlx_data->mat_proj[3][2] = return_zero;
	mlx_data->mat_proj[3][3] = return_zero;
}