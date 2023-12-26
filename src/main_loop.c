/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	handle_no_event(void *mlx_data)
{
    /* This function needs to exist, but it is useless for the moment */
    return (0);
}

/*
 *  Using mlx_loop_end creates a leak. Not my problem, caused by mlx lib.
 */
static int	handle_input(int keys, t_mlx_data *mlx_data)
{
    if (keys == XK_Escape) // should it be a & ?
        mlx_loop_end(mlx_data->mlx);
    return (0);
}

static void register_hooks(t_mlx_data mlx_data, t_data data)
{
    mlx_loop_hook(mlx_data.mlx, &handle_no_event, &mlx_data);
    //mlx_hook(mlx_data.mlx_win, KeyPress, KeyPressMask, &handle_input, &mlx_data);
    mlx_key_hook(mlx_data.mlx_win, &handle_input, &mlx_data);
}

/*
 *	This method will initialize all the hooks needed and start the aplication
 */
int	main_loop(t_mlx_data mlx_data, t_data data)
{
    //first register hooks
    register_hooks(mlx_data, data);
	mlx_loop(mlx_data.mlx);
	return (1);
}
