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

static void	init_rotation_matrices(t_ctrl_prgrm *data)
{
	set_rotation_x(data->space.rotation_x);
	set_rotation_y(data->space.rotation_y);
	set_rotation_z(data->space.rotation_z);
}

/*
 *	Initializes the matrices.
 */
void	init_matrices(t_ctrl_prgrm *data)
{
	init_rotation_matrices(data);
	init_scalation(data->space.scalation);
	init_translation(data->space.translation);
}
