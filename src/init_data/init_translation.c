/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_translation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static double	return_one(double d)
{
	(void)d;
	return (1);
}

static double	return_zero(double d)
{
	(void)d;
	return (0);
}

static double	return_value(double value)
{
	return (value);
}

void	init_translation(t_mat_funct translation[4][4])
{
	translation[0][0] = return_one;
	translation[0][1] = return_zero;
	translation[0][2] = return_zero;
	translation[0][3] = return_value;
	translation[1][0] = return_zero;
	translation[1][1] = return_one;
	translation[1][2] = return_zero;
	translation[1][3] = return_value;
	translation[2][0] = return_zero;
	translation[2][1] = return_zero;
	translation[2][2] = return_one;
	translation[2][3] = return_value;
	translation[3][0] = return_zero;
	translation[3][1] = return_zero;
	translation[3][2] = return_zero;
	translation[3][3] = return_one;
}
