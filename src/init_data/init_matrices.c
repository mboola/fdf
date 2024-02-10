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

static void	init_rotation_matrices(t_space *space)
{
	set_rotation_x(space->rotation_x);
	set_rotation_y(space->rotation_y);
	set_rotation_z(space->rotation_z);
}

/*
 *	Initializes the matrices.
 */
void	init_matrices(t_space *space)
{
	init_rotation_matrices(space);
	init_scalation(space->scalation);
	init_translation(space->translation);
}
