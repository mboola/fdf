
#include "ft_fdf.h"

static int	open_file(int argc, char **argv)
{
	int	fd;

	//TODO: check that file name ends with .fdf
	if (argc != 2)
		return (-1);
	/*
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (-1);
	}*/
	fd = open(argv[1], O_RDONLY);
	return (fd);
}

static unsigned char	transform_color(char **str, char *err)
{
	char	value[3];

	if (**str == '\0')
		return (0xFF);
	value[0] = **str;
	(*str)++;
	if (**str == '\0')
	{
		*err = 1;
		return (0);
	}
	value[1] = **str;
	(*str)++;
	value[2] = '\0';
	if (ft_strchr(HEXHIGHBASE, value[0]) && ft_strchr(HEXHIGHBASE, value[1]))
		return (ft_atoi_base(value, HEXHIGHBASE));
	if (ft_strchr(HEXLOWBASE, value[0]) && ft_strchr(HEXLOWBASE, value[1]))
		return (ft_atoi_base(value, HEXLOWBASE));
	*err = 1;
	return (0);
}

static int	convert_rgb(unsigned char red, unsigned char green, unsigned blue)
{
	return (red << 16 | green << 8 | blue);
}

static int	get_color(char *str, char *err)
{
	char			*colon;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	colon = ft_strchr(str, ',');
	if (colon == NULL)
		return (0);
	colon++;
	if (!ft_strncmp(colon, "0x", 2))
	{
		*err = 1;
		return (0);
	}
	red = transform_color(&colon, err);
	if (*err)
		return (0);
	green = transform_color(&colon, err);
	if (*err)
		return (0);
	blue = transform_color(&colon, err);
	if (*err)
		return (0);
	return (convert_rgb(red, green, blue));
}

static char		check_num_correct(char *str)
{
	if (*str == '-')
		str++;
	while (ft_isdigit(*str))
		str++;
	if (*str != '\0' && *str != ',')
		return (1);
	return (0);
}

static t_list	*create_points(char **mat, int len, int row, char *err)
{
	t_point	*points;
	t_list	*node_row;
	int		i;

	points = malloc(sizeof(t_point) * (len + 1));
	if (points == NULL)
	{
		*err = 1;
		return (NULL);
	}
	i = 0;
	while (!*err && i < len)
	{
		points[i].vector[0] = row;
		points[i].vector[1] = i;
		points[i].color = get_color(*(mat + i), err);
		if (*err)
			return (NULL);
		points[i].vector[2] = ft_atoi(*(mat + i));
		points[i].vector[3] = 1;
		*err = check_num_correct(*(mat + i));
		i++;
	}
	points[len].vector[0] = -1;
	node_row = ft_lstnew(points);
	if (node_row == NULL)
		*err = 1;
	return (node_row);
}

/*
 *	Converts a line from the file into data, controlling correct intput.
 *	Adds an array of points into a linked list.
 */
static int	process_line(t_list **lst, char **line, int n_row)
{
	char	**mat;
	char	*trimmed_line;
	int		n_col;
	t_list	*row_points;
	char	err;

	err = 0;
	trimmed_line = ft_strtrim(*line, " \n");
	free(*line);
	if (trimmed_line == NULL)
		return (-1);
	mat = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (mat == NULL)
		return (-1);
	n_col = ft_matlen((void **)mat);
	if (n_col == 0)
		return (-1);
	row_points = create_points(mat, n_col, n_row, &err);
	ft_lstadd_back(lst, row_points);
	ft_matclear((void ***)&mat);
	if (err)
		return (-1);
	return (n_col);
}

static int	assign_values(int col, t_list **lst, char **line, t_mlx_data *mlx)
{
	void	**mat_points;

	if (col != mlx->pixels.n_col)
	{
		ft_lstclear(lst, clear_point);
		free(*line);
		return (0);
	}
	mlx->points = *lst;
	mat_points = ft_calloc_matstruct(sizeof(t_vector2), mlx->pixels.n_row, mlx->pixels.n_col);
	if (mat_points == NULL)
	{
		ft_lstclear(lst, clear_point);
		return (0);
	}
	mlx->pixels.points = mat_points;
	return (1);
}

/*
 *	Reads the data from the file passed as argv. Checks if input is correct.
 *	It reads lines from the file and processes them. 
 */
int	read_input_file(int argc, char **argv, t_mlx_data *mlx_data)
{
	t_list	*lst;
	char	*line;
	int		fd;
	int		col;
	int		row;

	fd = open_file(argc, argv);
	if (fd == -1)
		return (0);
	lst = NULL;
	line = get_next_line(fd);
	col = process_line(&lst, &line, 0);
	if (col < 0)
		return (0);
	mlx_data->pixels.n_col = col;
	row = 1;
	line = get_next_line(fd);
	while (col == mlx_data->pixels.n_col && line)
	{
		col = process_line(&lst, &line, row);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
	mlx_data->pixels.n_row = row;
	return (assign_values(col, &lst, &line, mlx_data));
}
