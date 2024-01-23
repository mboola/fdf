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
