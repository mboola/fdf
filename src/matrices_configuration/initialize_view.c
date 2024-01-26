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
	mlx_data->angle_x = 0.7;
	mlx_data->angle_y = 0.35;
	mlx_data->angle_z = 0;
}

static void	initialize_conic(t_mlx_data *mlx_data)
{
	mlx_data->angle_x = 0;
	mlx_data->angle_y = 0;
	mlx_data->angle_z = 0;
}

static void	set_scale(t_mlx_data *mlx_data)
{
	mlx_data->scale[0] = 30;
	mlx_data->scale[1] = 30;
	mlx_data->scale[2] = 30;
	//y = mlx_data->pixels.n_row;
	//set this values correctly
	mlx_data->offset[0] = 5;
	mlx_data->offset[1] = 5;
	mlx_data->offset[2] = 0;
}

void	initialize_view(t_mlx_data *mlx_data)
{
	if (VIEW)
		initialize_conic(mlx_data);
	else
		initialize_isometric(mlx_data);
	set_scale(mlx_data);
}
