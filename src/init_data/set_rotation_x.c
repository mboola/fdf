/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_rotation_x.c                                   :+:      :+:    :+:   */
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

static double	return_one()
{
	return (1);
}

static double	negative_sin(double angle)
{
	return (-1 * sin(angle));
}

void	set_rotation_x(t_mat_funct rotation_x[4][4])
{
	rotation_x[0][0] = return_one;
	rotation_x[0][1] = return_zero;
	rotation_x[0][2] = return_zero;
	rotation_x[0][3] = return_zero;
	rotation_x[1][0] = return_zero;
	rotation_x[1][1] = cos;
	rotation_x[1][2] = sin;
	rotation_x[1][3] = return_zero;
	rotation_x[2][0] = return_zero;
	rotation_x[2][1] = negative_sin;
	rotation_x[2][2] = cos;
	rotation_x[2][3] = return_zero;
	rotation_x[3][0] = return_zero;
	rotation_x[3][1] = return_zero;
	rotation_x[3][2] = return_zero;
	rotation_x[3][3] = return_one;
}
