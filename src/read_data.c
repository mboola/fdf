
#include "ft_fdf.h"

static int	open_file(int argc, char **argv)
{
	int	fd;

	//TODO: check that file name ends with .fdf
	if (argc == 1)
		return (-1);
	fd = open(argv[1], O_DIRECTORY);
	if (fd != -1)
		return (-1);
	close(fd);
	fd = open(argv[1], O_RDONLY);
	return (fd);
}

//TODO: when we read a number, there will also be a color. also store that in the point information
//All lines should be the same len???
static char	process_line(t_list **lst, char **line, int row)
{
	char	**mat;
	int		col;
	t_list	*node;
	char	err;

	col = 0;
	err = 0;
	mat = ft_split(*line, ' ');
	free(*line);
	if (mat == NULL)
		return (1);
	while (!err && *(mat + col) != NULL)
	{
		node = new_point(row, col, ft_atoi_err(*(mat + col), &err), &err);
		ft_lstadd_back(lst, node);
		col++;
	}
	clear_matrix(&mat);
	if (err)
		return (1);
	return (0);
}

t_list	*read_data_file(int argc, char **argv)
{
	t_list	*lst;
	char	*line;
	int		fd;
	char	err;
	int		row;

	fd = open_file(argc, argv);
	if (fd == -1)
		return (NULL);
	err = 0;
	row = 0;
	lst = NULL;
	line = get_next_line(fd);
	while (!err && line != NULL)
	{
		err = process_line(&lst, &line, row);
		row++;
		line = get_next_line(fd);
	}
	close(fd);
	if (err)
	{
		ft_lstclear(&lst, clear_point);
		free(line);
		return (NULL);
	}
	return (lst);
}
