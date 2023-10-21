/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaceres <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 06:23:56 by acaceres          #+#    #+#             */
/*   Updated: 2023/10/21 07:11:03 by acaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	hook_key_handler(int keycode, t_fractol *fractol)
{
	if (keycode == ESCAPE)
		close_hook(fractol);
	move_hook(keycode, fractol);
	iters_hook(keycode, fractol);
	zoom_hook(keycode, fractol);
	reset_hook(keycode, fractol);
	draw_fractal(fractol);
	return (0);
}

int	hook_mouse_handler(int action, int x, int y, t_fractol *fractol)
{
	if (action == MOUSE_UP)
		fractol->zoom *= 1.3;
	else if (action == MOUSE_DOWN)
		fractol->zoom /= 1.3;
	if (x || y)
		draw_fractal(fractol);
	return (0);
}

int	window_close_hook(t_fractol *fractol)
{
	close_hook(fractol);
	return (0);
}

void	hook_handler(t_fractol *fractol)
{
	mlx_key_hook(fractol->vars.win, hook_key_handler, fractol);
	mlx_mouse_hook(fractol->vars.win, hook_mouse_handler, fractol);
	mlx_hook(fractol->vars.win, ON_DESTROY, 0, window_close_hook, fractol);
}
