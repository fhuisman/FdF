/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhuisman <fhuisman@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/13 11:33:30 by fhuisman      #+#    #+#                 */
/*   Updated: 2023/04/06 13:57:01 by fhuisman      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "./MLX42/include/MLX42/MLX42.h"
# include "./libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

# define WIDTH			1920
# define HEIGHT			1080
# define ERR_ARGUMENT	"Invalid argument count"
# define ERR_MALLOC		"Memory allocation failed"
# define ERR_MAP		"invalid map"
# define ERR_MLX		"Failed to initiate mlx"
# define ERR_IMG		"Failed to create image"
# define ERR_FD			"invalid file descriptor"

typedef enum projection
{
	ISOMETRIC	= 1,
	PARALLEL	= 2,
}	t_projection;

typedef struct point
{
	double			x;
	double			y;
	double			z;
	double			x_init;
	double			y_init;
	double			z_init;
	uint32_t		color;
	struct point	*next;
	struct point	*next_point;
	struct point	*next_row;
}	t_point;

typedef struct draw_line_data
{
	double		delta_x;
	double		delta_y;
	uint32_t	length;
	double		pixel_x;
	double		pixel_y;
}	t_draw_line_data;

typedef struct color_data
{
	int32_t	red;
	int32_t	green;
	int32_t	blue;
}	t_color_data;

typedef struct fdf
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_point			*map;
	int32_t			screen_width;
	int32_t			screen_height;
	int32_t			map_width;
	int32_t			map_height;
	double			mouse_x;
	double			mouse_y;
	int32_t			x_shift;
	int32_t			y_shift;
	double			zoom;
	int				x_rotation;
	int				y_rotation;
	int				z_rotation;
	double			altitude;
	int				projection;
}	t_fdf;

t_point		*init_map(int fd);
void		init_fdf(t_fdf *fdf, char *inputfile);
void		free_map(t_point *map);
void		draw_line(t_fdf *fdf, t_point p1, t_point p2);
void		free_exit(mlx_t *mlx, mlx_image_t *img, t_point *map, char *errmsg);
uint32_t	hexstring_to_uint(char *s);
void		free_split_line(char **split_line);
void		x_rotation(t_point *point, int degrees);
void		y_rotation(t_point *point, int degrees);
void		z_rotation(t_point *point, int degrees);
void		rotate(t_fdf *fdf, int key);
void		isometric(t_point *point);
void		draw(t_fdf *fdf);
void		zoom(t_fdf *fdf, double delta_y);
void		change_map(t_fdf *fdf);
void		get_map_dimensions(t_fdf *fdf);
void		hooks(t_fdf *fdf);
void		key_hook(mlx_key_data_t keydata, void *param);
void		close_hook(void *param);
void		resize_hook(int32_t width, int32_t height, void *param);
void		scroll_hook(double xdelta, double ydelta, void *param);
void		cursor_hook(double xpos, double ypos, void *param);
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		change_projection(t_fdf *fdf, int key);

#endif