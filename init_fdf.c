/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_fdf.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/04 13:11:42 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 13:50:01 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_fdf(t_fdf *fdf)
{
	get_map_dimensions(fdf);
	fdf->screen_width = WIDTH;
	fdf->screen_height = HEIGHT;
	fdf->mouse_y = -1;
	fdf->mouse_x = -1;
	fdf->zoom = fdf->screen_width / fdf->map_width / 2;
	if ((fdf->screen_height / fdf->map_height / 2) < fdf->zoom)
		fdf->zoom = fdf->screen_height / fdf->map_height / 2;
	fdf->x_shift = 0;
	fdf->y_shift = 0;
	fdf->x_rotation = 0;
	fdf->y_rotation = 0;
	fdf->z_rotation = 0;
	fdf->projection = ISOMETRIC;
}

void	init_fdf(t_fdf *fdf, char *inputfile)
{
	int		fd;

	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
		free_exit(NULL, NULL, fdf->map, ERR_MLX);
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		free_exit(fdf->mlx, NULL, fdf->map, ERR_IMG);
	fd = open(inputfile, O_RDONLY);
	if (fd < 0)
		free_exit(fdf->mlx, fdf->img, fdf->map, ERR_FD);
	fdf->map = init_map(fd);
	close(fd);
	if (!fdf->map)
		free_exit(fdf->mlx, fdf->img, fdf->map, ERR_MAP);
	set_fdf(fdf);
}
