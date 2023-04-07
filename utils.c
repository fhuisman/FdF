/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 11:37:19 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/07 14:58:49 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_map_dimensions(t_fdf *fdf)
{
	t_point	*temp;
	int		z_min;
	int		z_max;

	temp = fdf->map;
	z_min = temp->z;
	z_max = temp->z;
	while (temp)
	{
		if (temp->z > z_max)
			z_max = temp->z;
		if (temp->z < z_min)
			z_min = temp->z;
		temp = temp->next;
	}
	fdf->altitude = z_max - z_min;
	if (fdf->altitude == 0)
		fdf->altitude = 1;
	temp = fdf->map;
	while (temp->next_point)
		temp = temp->next_point;
	while (temp->next_row)
		temp = temp->next_row;
	fdf->map_height = temp->y + 1;
	fdf->map_width = temp->x + 1;
}

uint32_t	hexstring_to_uint(char *s)
{
	int			i;
	uint32_t	uint;

	uint = 0;
	i = 2;
	if (!s)
		return (0xffffff);
	while (s[i])
	{
		s[i] = ft_toupper(s[i]);
		if (s[i] >= '0' && s[i] <= '9')
		{
			uint *= 16;
			uint += s[i] - '0';
		}
		else if (s[i] >= 'A' && s[i] <= 'F')
		{
			uint *= 16;
			uint += s[i] - 'A' + 10;
		}
		i++;
	}
	return (uint);
}

static uint32_t	color_gradient(uint32_t length, t_point p1, t_point p2,
	uint32_t pixel)
{
	uint32_t		color;
	t_color_data	c1;
	t_color_data	c2;
	double			percent;

	if (p1.color == p2.color)
		return (p1.color);
	c1.red = (p1.color >> 24) & 0xFF;
	c1.green = (p1.color >> 16) & 0xFF;
	c1.blue = (p1.color >> 8) & 0xFF;
	c2.red = (p2.color >> 24) & 0xFF;
	c2.green = (p2.color >> 16) & 0xFF;
	c2.blue = (p2.color >> 8) & 0xFF;
	color = 0xFF;
	percent = pixel / (double)length;
	color |= (int)((1 - percent) * c1.red + (percent * c2.red)) << 24;
	color |= (int)((1 - percent) * c1.green + (percent * c2.green)) << 16;
	color |= (int)((1 - percent) * c1.blue + (percent * c2.blue)) << 8;
	return (color);
}

void	draw_line(t_fdf *fdf, t_point p1, t_point p2)
{
	t_draw_line_data	data;
	uint32_t			pixel;

	data.delta_x = p2.x - p1.x;
	data.delta_y = p2.y - p1.y;
	data.length = sqrt((data.delta_x * data.delta_x)
			+ (data.delta_y * data.delta_y));
	data.delta_x /= data.length;
	data.delta_y /= data.length;
	data.pixel_x = p1.x;
	data.pixel_y = p1.y;
	pixel = 0;
	while (pixel < data.length)
	{
		if (data.pixel_x > 0 && data.pixel_x < fdf->screen_width
			&& data.pixel_y > 0 && data.pixel_y < fdf->screen_height)
			mlx_put_pixel(fdf->img, data.pixel_x, data.pixel_y,
				color_gradient(data.length, p1, p2, pixel));
		data.pixel_x += data.delta_x;
		data.pixel_y += data.delta_y;
		pixel++;
	}
}
