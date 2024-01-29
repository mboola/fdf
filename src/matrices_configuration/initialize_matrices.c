/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_matrices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static void	initialize_rotation(t_mlx_data *mlx_data)
{
	set_rotation_x(mlx_data);
	set_rotation_y(mlx_data);
	set_rotation_z(mlx_data);
}

/*
 *	Initializes the matrices.
 */
void	initialize_matrices(t_mlx_data *mlx_data)
{
	//initialize_projection(mlx_data);
	initialize_conic_projection(mlx_data);
	initialize_rotation(mlx_data);
	initialize_scale(mlx_data);
	initialize_translation(mlx_data);
}
