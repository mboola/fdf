/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rotation_z.c                                   :+:      :+:    :+:   */
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

void	set_rotation_z(t_mlx_data *mlx_data)
{
	mlx_data->rotation_z[0][0] = cos;
	mlx_data->rotation_z[0][1] = negative_sin;
	mlx_data->rotation_z[0][2] = return_zero;
	mlx_data->rotation_z[0][3] = return_zero;
	mlx_data->rotation_z[1][0] = sin;
	mlx_data->rotation_z[1][1] = cos;
	mlx_data->rotation_z[1][2] = return_zero;
	mlx_data->rotation_z[1][3] = return_zero;
	mlx_data->rotation_z[2][0] = return_zero;
	mlx_data->rotation_z[2][1] = return_zero;
	mlx_data->rotation_z[2][2] = return_one;
	mlx_data->rotation_z[2][3] = return_zero;
	mlx_data->rotation_z[3][0] = return_zero;
	mlx_data->rotation_z[3][1] = return_zero;
	mlx_data->rotation_z[3][2] = return_zero;
	mlx_data->rotation_z[3][3] = return_one;
}
