/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_scalation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 18:18:20 by mpovill-          #+#    #+#             */
/*   Updated: 2024/01/01 18:18:20 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static double	return_one()
{
	return (1);
}

static double	return_zero()
{
	return (0);
}

static double	return_value(double value)
{
	return (value);
}

void	init_scalation(t_mat_funct scalation[4][4])
{
	scalation[0][0] = return_value;
	scalation[0][1] = return_zero;
	scalation[0][2] = return_zero;
	scalation[0][3] = return_zero;
	scalation[1][0] = return_zero;
	scalation[1][1] = return_value;
	scalation[1][2] = return_zero;
	scalation[1][3] = return_zero;
	scalation[2][0] = return_zero;
	scalation[2][1] = return_zero;
	scalation[2][2] = return_value;
	scalation[2][3] = return_zero;
	scalation[3][0] = return_zero;
	scalation[3][1] = return_zero;
	scalation[3][2] = return_zero;
	scalation[3][3] = return_one;
}