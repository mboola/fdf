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

void	set_isometric_view(t_ctrl_prgrm *data)
{
	t_shape	*shape;

	shape = data->space.shape;
	shape->angle_x = 0.60710678118;
	shape->angle_y = -0.70710678118;
	shape->angle_z = -0.57734471598;
	data->rasterize = 1;
}
