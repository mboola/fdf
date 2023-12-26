/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpovill- <mpovill-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 10:45:14 by mpovill-          #+#    #+#             */
/*   Updated: 2023/12/26 11:42:52 by mpovill-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

static int	clear_data(t_data data, void *mlx)
{
	//clear mem reserved for data storage
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

int main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	t_data		data_read;

	data_read = read_data_file(argc, argv);
	//if (data_read == NULL)
	//	return (0);
	mlx_data.mlx = mlx_init();
	if (mlx_data.mlx == NULL)
		return (clear_data(data_read, NULL));
	mlx_data.mlx_win = mlx_new_window(mlx_data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (mlx_data.mlx_win == NULL)
		return (clear_data(data_read, mlx_data.mlx));
	main_loop(mlx_data, data_read);
	mlx_destroy_window(mlx_data.mlx, mlx_data.mlx_win);
	return (clear_data(data_read, mlx_data.mlx));
}
