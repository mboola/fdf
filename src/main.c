
#include "ft_fdf.h"

static void	*read_data_file(int argc, char **argv)
{
	return (NULL);
}

static int	clear_data(void *data, void *mlx)
{
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}

/*
 *	This method will control the images put to the window and when to close it
 */
static int	main_loop(void *mlx, void *mlx_win, void *data)
{
	//mlx_loop(mlx);
	return (1);
}

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	void	*data_read;

	data_read = read_data_file(argc, argv);
	//if (data_read == NULL)
	//	return (0);
	mlx = mlx_init();
	if (mlx == NULL)
		return (clear_data(data_read, NULL));
	mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (mlx_win == NULL)
		return (clear_data(data_read, mlx));
	main_loop(mlx, mlx_win, data_read);
	mlx_destroy_window(mlx, mlx_win);
	return (clear_data(data_read, mlx));
}
