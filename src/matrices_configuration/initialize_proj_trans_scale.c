/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scale.c                                        :+:      :+:    :+:   */
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

static double	return_value(double value)
{
	return (value);
}

void	initialize_translation(t_mlx_data *mlx_data)
{
	mlx_data->mat_translation[0][0] = return_zero;
	mlx_data->mat_translation[0][1] = return_zero;
	mlx_data->mat_translation[0][2] = return_value;
	mlx_data->mat_translation[1][0] = return_zero;
	mlx_data->mat_translation[1][1] = return_zero;
	mlx_data->mat_translation[1][2] = return_value;
	mlx_data->mat_translation[2][0] = return_zero;
	mlx_data->mat_translation[2][1] = return_zero;
	mlx_data->mat_translation[2][2] = return_value;
}

void	initialize_scale(t_mlx_data *mlx_data)
{
	mlx_data->mat_scale[0][0] = return_value;
	mlx_data->mat_scale[0][1] = return_zero;
	mlx_data->mat_scale[0][2] = return_zero;
	mlx_data->mat_scale[1][0] = return_zero;
	mlx_data->mat_scale[1][1] = return_value;
	mlx_data->mat_scale[1][2] = return_zero;
	mlx_data->mat_scale[2][0] = return_zero;
	mlx_data->mat_scale[2][1] = return_zero;
	mlx_data->mat_scale[2][2] = return_value;
}

void	initialize_projection(t_mlx_data *mlx_data)
{
	mlx_data->mat_proj[0][0] = 1;
	mlx_data->mat_proj[0][1] = 0;
	mlx_data->mat_proj[0][2] = 0;
	mlx_data->mat_proj[1][0] = 0;
	mlx_data->mat_proj[1][1] = 1;
	mlx_data->mat_proj[1][2] = 0;
	mlx_data->mat_proj[2][0] = 0;
	mlx_data->mat_proj[2][1] = 0;
	mlx_data->mat_proj[2][2] = 0;
}
