/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rotation_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static double	return_zero()
{
	return (0);
}

static double	return_one()
{
	return (1);
}

static double	negative_sin(double angle)
{
	return (-1 * sin(angle));
}

void	set_rotation_x(t_mlx_data *mlx_data)
{
	mlx_data->rotation_x[0][0] = return_one;
	mlx_data->rotation_x[0][1] = return_zero;
	mlx_data->rotation_x[0][2] = return_zero;
	mlx_data->rotation_x[1][0] = return_zero;
	mlx_data->rotation_x[1][1] = cos;
	mlx_data->rotation_x[1][2] = negative_sin;
	mlx_data->rotation_x[2][0] = return_zero;
	mlx_data->rotation_x[2][1] = sin;
	mlx_data->rotation_x[2][2] = cos;
}
