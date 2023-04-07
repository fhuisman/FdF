/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/22 14:10:50 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 12:48:47 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_map(t_fdf *fdf)
{
	t_point	*temp;

	temp = fdf->map;
	while (temp)
	{
		temp->x = temp->x_init * fdf->zoom;
		temp->y = temp->y_init * fdf->zoom;
		temp->z = temp->z_init * fdf->zoom / fdf->altitude;
		temp->x -= (fdf->map_width * fdf->zoom) / 2;
		temp->y -= (fdf->map_height * fdf->zoom) / 2;
		x_rotation(temp, fdf->x_rotation);
		y_rotation(temp, fdf->y_rotation);
		z_rotation(temp, fdf->z_rotation);
		if (fdf->projection == ISOMETRIC)
			isometric(temp);
		temp->x += (fdf->screen_width / 2) + fdf->x_shift;
		temp->y += (fdf->screen_height / 2) + fdf->y_shift;
		temp = temp->next;
	}
}

void	draw(t_fdf *fdf)
{
	t_point	*temp;

	change_map(fdf);
	temp = fdf->map;
	while (temp->next)
	{
		if (temp->next_point)
			draw_line(fdf, *temp, *temp->next_point);
		if (temp->next_row)
			draw_line(fdf, *temp, *temp->next_row);
		temp = temp->next;
	}
	mlx_image_to_window(fdf->mlx, fdf->img, 0, 0);
}
