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

static int	project(double coord)
{
	return ((int)round(coord));
}

static int	return_zero()
{
	return (0);
}

void	initialize_projection(t_mlx_data *mlx_data)
{
	mlx_data->mat_proj[0][0] = project;
	mlx_data->mat_proj[0][1] = return_zero;
	mlx_data->mat_proj[0][2] = return_zero;
	mlx_data->mat_proj[0][3] = return_zero;
	mlx_data->mat_proj[1][0] = return_zero;
	mlx_data->mat_proj[1][1] = project;
	mlx_data->mat_proj[1][2] = return_zero;
	mlx_data->mat_proj[1][3] = return_zero;
	mlx_data->mat_proj[2][0] = return_zero;
	mlx_data->mat_proj[2][1] = return_zero;
	mlx_data->mat_proj[2][2] = return_zero;
	mlx_data->mat_proj[2][3] = return_zero;
	mlx_data->mat_proj[3][0] = return_zero;
	mlx_data->mat_proj[3][1] = return_zero;
	mlx_data->mat_proj[3][2] = return_zero;
	mlx_data->mat_proj[3][3] = return_zero;
}
