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

static int	project_x(double coord, t_mlx_data *mlx_data)
{
	return ((int)round(coord * mlx_data->scale + mlx_data->offset[0]));
}

static int	project_y(double coord, t_mlx_data *mlx_data)
{
	return ((int)round(coord * mlx_data->scale + mlx_data->offset[1]));
}

static int	return_zero()
{
	return (0);
}

//not sure if coordinates x and y are OK...
void	set_projection(t_mlx_data *mlx_data)
{
	mlx_data->projection_matrix[0][0] = project_x;
	mlx_data->projection_matrix[0][1] = return_zero;
	mlx_data->projection_matrix[0][2] = return_zero;
	mlx_data->projection_matrix[1][0] = return_zero;
	mlx_data->projection_matrix[1][1] = project_y;
	mlx_data->projection_matrix[1][2] = return_zero;
	mlx_data->projection_matrix[2][0] = return_zero;
	mlx_data->projection_matrix[2][1] = return_zero;
	mlx_data->projection_matrix[2][2] = return_zero;
}
