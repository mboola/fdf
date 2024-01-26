/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void	update_angle_x(t_mlx_data *mlx_data, double increment)
{
	int	tmp;

	printf("%1f\n", mlx_data->angle_x);

	if (mlx_data->angle_x + increment > MAX_ANGLE)
	{
		tmp = MAX_ANGLE - mlx_data->angle_x;
		mlx_data->angle_x = increment - tmp;
	}
	else
		mlx_data->angle_x += increment;
}

void	update_angle_y(t_mlx_data *mlx_data, double increment)
{
	int	tmp;

	printf("%1f\n", mlx_data->angle_y);

	if (mlx_data->angle_y + increment > MAX_ANGLE)
	{
		tmp = MAX_ANGLE - mlx_data->angle_y;
		mlx_data->angle_y = increment - tmp;
	}
	else
		mlx_data->angle_y += increment;
}

void	update_angle_z(t_mlx_data *mlx_data, double increment)
{
	int	tmp;

	printf("%1f\n", mlx_data->angle_z);

	if (mlx_data->angle_z + increment > MAX_ANGLE)
	{
		tmp = MAX_ANGLE - mlx_data->angle_z;
		mlx_data->angle_z = increment - tmp;
	}
	else
		mlx_data->angle_z += increment;
	//here i calculate the offset_translation
	//mlx_data->offset_correction[0] += 10; 
	//mlx_data->offset_correction[1] += 10; 
}
