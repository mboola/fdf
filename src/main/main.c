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

static int	clear_data(t_mlx_data **mlx_data)
{
	ft_lstclear(&((*mlx_data)->points), clear_point);
	mlx_destroy_display((*mlx_data)->mlx);
	free((*mlx_data)->mlx);
	free(*mlx_data);
	return (0);
}

static void	print_info(void *info)
{
	t_point	*point;	//array of pointers
	int		i;

	i = 0;
	point = (t_point *)info;
	while (point[i].vector[0] != -1)
	{
		ft_printf(1, "X=%d, Y=%d, Z=%d, ", point[i].vector[0], point[i].vector[1], point[i].vector[2]);
		i++;
	}
	ft_printf(1, "\n");
}

int main(int argc, char **argv)
{
	t_mlx_data	*mlx_data;

	mlx_data = malloc(sizeof(t_mlx_data));
	if (mlx_data == NULL)
		return (0);
	mlx_data->points = read_data_file(argc, argv);
	if (mlx_data->points == NULL)
	{
		free(mlx_data);
		return (0);
	}
	ft_lstiter(mlx_data->points, print_info);
	mlx_data->mlx = mlx_init();
	if (mlx_data->mlx == NULL)
		return (clear_data(&mlx_data));
	mlx_data->mlx_win = mlx_new_window(mlx_data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME);
	if (mlx_data->mlx_win == NULL)
		return (clear_data(&mlx_data));
	main_loop(mlx_data);
	mlx_destroy_window(mlx_data->mlx, mlx_data->mlx_win);
	return (clear_data(&mlx_data));
}
