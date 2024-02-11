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

/*
 *	Clears the struct created to run the application.
 */
static void	clear_data(t_ctrl_prgrm **data)
{
	if ((*data)->mlx != NULL)
	{
		if ((*data)->image.img != NULL)
			mlx_destroy_image((*data)->mlx, (*data)->image.img);
		if ((*data)->mlx_win != NULL)
			mlx_destroy_window((*data)->mlx, (*data)->mlx_win);
		mlx_destroy_display((*data)->mlx);
		free((*data)->mlx);
	}
	if ((*data)->space.shape != NULL)
		clear_shape((*data)->space.shape);
	free(*data);
	exit(0);
}

static char	mlx_reserve_image(t_ctrl_prgrm *data)
{
	t_image	image;

	image.img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (image.img == NULL)
		return (0);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_len,
			&image.endian);
	data->image = image;
	return (1);
}

/*
 *	Main function. Reads the file into a matrix of points.
 *	Creates a struct that will hold all the information to create a window
 *	and put pixels to it. Clears the struct when ended.
 */
int	main(int argc, char **argv)
{
	t_ctrl_prgrm	*data;

	if (argc != 2)
		return (0);
	data = ft_calloc(sizeof(t_ctrl_prgrm), 1);
	if (data == NULL)
		return (0);
	data->space.shape = read_input(argv[1]);
	if (data->space.shape == NULL)
		clear_data(&data);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		clear_data(&data);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (data->mlx_win == NULL)
		clear_data(&data);
	if (!mlx_reserve_image(data))
		clear_data(&data);
	main_loop(data);
	clear_data(&data);
	return (0);
}
