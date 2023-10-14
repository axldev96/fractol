/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <acaceres@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 03:00:31 by acaceres          #+#    #+#             */
/*   Updated: 2023/10/14 20:01:17 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	set_complex_numbers(t_complex *z, t_complex *c, t_scales *scales)
{
	z->real = 0.0;
	z->imag = 0.0;
	c->real = interpolate(&scales->scale_real);
	c->imag = interpolate(&scales->scale_imag);
}

int	mandelbrot(int x, int y, t_fractol *fractol)
{
	t_complex	z;
	t_complex	c;
	t_scales	scales;
	int			color;
	int			i;

	i = 0;
	init_scale_real(&scales.scale_real, x);
	init_scale_imag(&scales.scale_imag, y);
	set_complex_numbers(&z, &c, &scales);
	while (i < fractol->max_iter)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.imag * z.imag) > HYPOTENUSE)
		{
			init_scale_color(&scales.scale_color, i);
			color = interpolate(&scales.scale_color);
			return (color);
		}
		++i;
	}
	return (0x00000000);
}

void	draw_mandelbrot(t_fractol *fractol)
{
	int	x;
	int	y;
	int	color;

	x = -1;
	color = 0;
	y = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			color = mandelbrot(x, y, fractol);
			ft_mlx_pixel_put(&fractol->data, x, y, color);
		}
		ft_mlx_pixel_put(&fractol->data, x, y, WHITE);
	}
	mlx_put_image_to_window(fractol->vars.mlx, fractol->vars.win,
		fractol->data.img, 0, 0);
}