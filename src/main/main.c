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
	mlx_destroy_window((*data)->mlx, (*data)->mlx_win);
	mlx_destroy_display((*data)->mlx);
	free((*data)->mlx);
	clear_space((*data)->space);
	free(*data);
	exit(0);
}

/*
 *	Main function. Reads the file into a matrix of points.
 *	Creates a struct that will hold all the information to create a window
 *	and put pixels to it. Clears the struct when ended.
 */
int main(int argc, char **argv)
{
	t_ctrl_prgrm	*data;
	t_list			*shape;

	data = ft_calloc(sizeof(t_ctrl_prgrm), 1);
	if (data == NULL)
		return (0);
	shape = read_input(argc, argv);
	if (shape == NULL)
	{
		free(data);
		return (0);
	}
	data->space.shapes = shape;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		clear_data(&data);
	data->mlx_win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, WIN_NAME);
	if (data->mlx_win == NULL)
		clear_data(&data);
	main_loop(data);
	clear_data(&data);
	return (0);
}
