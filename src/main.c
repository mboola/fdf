
#include "ft_fdf.h"

int main(int argc, char **argv)
{
	//here we read the file
	
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 400, "Hello world!");
	mlx_loop(mlx);
	return (0);
}
