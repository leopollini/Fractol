/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:28 by lpollini          #+#    #+#             */
/*   Updated: 2023/01/27 00:13:05 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	win_close(t_window *win)
{
	mlx_destroy_window(win->mlx, win->win);
	free(win->mlx);
	exit(0);
}

void	clear_image(t_window *win, t_vector_int size)
{
	t_ld	i;
	t_ld	j;

	i = 0;
	j = 0;
	while (i < size.x)
		while (j < size.y)
			my_mlx_pixel_put(&win->img, i++, j++, 0);
}

int	manage_key_release(int keypressed, t_window *win)
{
	printf("released keycode %i\n", keypressed);
}

int	manage_button_press(int keypressed, int x, int y, t_window *win)
{
	printf("pressed mouse at %i, %i; code %i\n", x, y, keypressed);
}

int	manage_button_release(int keypressed, int x, int y, t_window *win)
{
	printf("released mouse at %i, %i; code %i\n", x, y, keypressed);
}

t_ld	square_of(t_ld a)
{
	return (a * a);
}

t_ld	sqr_mod_of(t_vector_ld vec)
{
	return (square_of(vec.x) + square_of(vec.y));
}

int	create_color_overflow(int b, t_another_cont color)
{
	return (create_trgb(0, b * color.r, b * color.g, b * color.b));
}

t_ld	mod(t_ld a)
{
	if (a > 0)
		return (a);
	return (-a);
}

int	julia_col(t_vector_ld zed, t_ld x, t_ld y, t_another_cont color)
{
	t_vector_ld	temp;
	int			count;

	count = -1;
	while (count++ < color.iter)
	{
		temp.x = x * x;
		temp.y = y * y;
		if (temp.x + temp.y > SQR_RAD)
		{
			return (create_color_overflow(count, color));
		}
		y = x * y * 2 + zed.y;
		x = temp.x - temp.y + zed.x;
	}
	return (create_trgb(0, 0, 0, 0));
}

int	mandelbrot_col(t_vector_ld zed, t_ld x, t_ld y, t_another_cont color)
{
	t_vector_ld	temp;
	int			count;

	count = -1;
	while (count++ < color.iter)
	{
		temp.x = zed.x * zed.x;
		temp.y = zed.y * zed.y;
		if (temp.x + temp.y > SQR_RAD)
		{
			return (create_color_overflow(count, color));
		}
		zed.y = zed.x * zed.y * 2 + y;
		zed.x = temp.x - temp.y + x;
	}
	return (create_trgb(0, 0, 0, 0));
}

int	burn_s_color(t_vector_ld zed, t_ld x, t_ld y, t_another_cont color)
{
	t_vector_ld	temp;
	int			count;

	count = -1;
	while (count++ < color.iter)
	{
		temp.x = zed.x * zed.x;
		temp.y = zed.y * zed.y;
		if (temp.x + temp.y > SQR_RAD)
		{
			return (create_color_overflow(count, color));
		}
		zed.y = mod(zed.x * zed.y) * 2 + y;
		zed.x = temp.x - temp.y + x;
	}
	return (create_trgb(0, 0, 0, 0));
}

void	julia_set(t_window *win, t_vector_int winsize)
{
	t_vector_int_ld	cen;
	t_vector_ld		zero;
	t_another_cont	color;

	color = win->coloration;
	zero.x = win->firstp.x;
	zero.y = win->firstp.y;
	if (win->coloration.z != 1 + E_N2)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &cen.intg.x, &cen.intg.y);
		printf("[MOUSEPOS: %i, %i]", cen.intg.x, cen.intg.y);
		cen.doub.x = (win->cen.x - cen.intg.x) * (win->coloration.z / win->p_zoom) + cen.intg.x;
		cen.doub.y = (win->cen.y - cen.intg.y) * (win->coloration.z / win->p_zoom) + cen.intg.y;
	}
	else
	{
		win->coloration.z -= E_N2;
		cen.doub.x = winsize.x / 2;
		cen.doub.y = winsize.y / 2;
	}
	win->cen.x = cen.doub.x;
	win->cen.y = cen.doub.y;
	win->p_zoom = win->coloration.z;
	color.iter = win->iters;
	cen.doub.x /= win->scale;
	cen.doub.y /= win->scale;
	for (t_ld i = 0; i < winsize.x; i++)
		for (t_ld j = 0; j < winsize.y; j++)
			my_mlx_pixel_put(&win->img, i, j, julia_col(zero, i / win->scale - cen.doub.x, j / win->scale - cen.doub.y, color));
}

void	mandelbrot_set(t_window *win, t_vector_int winsize)
{
	t_vector_int_ld	cen;
	t_vector_ld		zero;
	t_another_cont	color;

	color = win->coloration;
	zero.x = 0;
	zero.y = 0;
	if (win->coloration.z != 1 + E_N2)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &cen.intg.x, &cen.intg.y);
		printf("[MOUSEPOS: %i, %i]", cen.intg.x, cen.intg.y);
		cen.doub.x = (win->cen.x - cen.intg.x) * (win->coloration.z / win->p_zoom) + cen.intg.x;
		cen.doub.y = (win->cen.y - cen.intg.y) * (win->coloration.z / win->p_zoom) + cen.intg.y;
	}
	else
	{
		win->coloration.z -= E_N2;
		cen.doub.x = winsize.x / 2;
		cen.doub.y = winsize.y / 2;
	}
	win->cen.x = cen.doub.x;
	win->cen.y = cen.doub.y;
	win->p_zoom = win->coloration.z;
	color.iter = win->iters;
	cen.doub.x /= win->scale;
	cen.doub.y /= win->scale;
	for (t_ld i = 0; i < winsize.x; i++)
		for (t_ld j = 0; j < winsize.y; j++)
			my_mlx_pixel_put(&win->img, i, j, mandelbrot_col(zero, i / win->scale - cen.doub.x, j / win->scale - cen.doub.y, color));
}

void	burning_ship_set(t_window *win, t_vector_int winsize)
{
	t_vector_int_ld	cen;
	t_vector_ld		zero;
	t_another_cont	color;

	color = win->coloration;
	zero.x = 0;
	zero.y = 0;
	if (win->coloration.z != 1 + E_N2)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &cen.intg.x, &cen.intg.y);
		printf("[MOUSEPOS: %i, %i]", cen.intg.x, cen.intg.y);

		cen.doub.x = (win->cen.x - cen.intg.x) * (win->coloration.z / win->p_zoom) + cen.intg.x;
		cen.doub.y = (win->cen.y - cen.intg.y) * (win->coloration.z / win->p_zoom) + cen.intg.y;
	}
	else
	{
		win->coloration.z -= E_N2;
		cen.doub.x = winsize.x / 2;
		cen.doub.y = winsize.y / 2;
	}
	win->cen.x = cen.doub.x;
	win->cen.y = cen.doub.y;
	win->p_zoom = win->coloration.z;
	color.iter = win->iters;
	cen.doub.x /= win->scale;
	cen.doub.y /= win->scale;
	for (t_ld i = 0; i < winsize.x; i++)
		for (t_ld j = 0; j < winsize.y; j++)
			my_mlx_pixel_put(&win->img, i, j, burn_s_color(zero, i / win->scale - cen.doub.x, j / win->scale - cen.doub.y, color));
}

void	my_image_creator(t_window *win, t_vector_int winsize)
{
	win->scale = winsize.x / 10 * win->coloration.z;
	if (win->type == JULIA)
	{
		julia_set(win, winsize);
	}
	if (win->type == MANDELBROT)
	{
		mandelbrot_set(win, winsize);
	}
	if (win->type == B_SHIP)
	{
		burning_ship_set(win, winsize);
	}
	printf("finished\n");
}

void	reimage(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	my_image_creator(win, win->size);
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_do_sync(win->mlx);
}

int	manage_keys(int keypressed, t_window *win)
{
	switch (keypressed)
	{
	case 117:
		win->coloration.r += CHANGE_VAL;
		break;
	case 106:
		win->coloration.r -= CHANGE_VAL;
		break;
	case 105:
		win->coloration.g += CHANGE_VAL;
		break;
	case 107:
		win->coloration.g -= CHANGE_VAL;
		break;
	case 111:
		win->coloration.b += CHANGE_VAL;
		break;
	case 108:
		win->coloration.b -= CHANGE_VAL;
		break;

		// zoom
	case 118:
		win->coloration.z /= SCALE_L;
		break;
	case 98:
		win->coloration.z /= SCALE_S;
		break;
	case 110:
		win->coloration.z *= SCALE_S;
		break;
	case 109:
		win->coloration.z *= SCALE_L;
		break;

		// change x of starting point
	case 113:
		win->firstp.x += E_0;
		break;
	case 119:
		win->firstp.x += E_N1;
		break;
	case 101:
		win->firstp.x += E_N2;
		break;
	case 114:
		win->firstp.x -= E_N2;
		break;
	case 116:
		win->firstp.x -= E_N1;
		break;
	case 121:
		win->firstp.x -= E_0;
		break;
		// change y of starting point
	case 97:
		win->firstp.y += E_0;
		break;
	case 115:
		win->firstp.y += E_N1;
		break;
	case 100:
		win->firstp.y += E_N2;
		break;
	case 102:
		win->firstp.y -= E_N2;
		break;
	case 103:
		win->firstp.y -= E_N1;
		break;
	case 104:
		win->firstp.y -= E_0;
		break;

		//type changer
	case 112 :
		win->type = (win->type + 1) % TYPE_END;
		break ;

		// move keys
		
	case 65361:
		win->cen.x += 30;
		break;
	case 65363:
		win->cen.x -= 30;
		break;
	case 65362:
		win->cen.y += 30;
		break;
	case 65364:
		win->cen.y -= 30;
		break;

		// close with Esc
	case 65307:
		win_close(win);
		break;
	default: return (0);
	};
	win->iters = MAX_ITER * log(win->coloration.z + 25) / 3;
	printf("[PRESSED: %i] ", keypressed);
	printf("now set to: %Lf, %Lf, %Lf, %Lf. Fract type: %i; inital point: %Lf, %Lf; Iters: %d\n", win->coloration.z, win->coloration.r, win->coloration.g, win->coloration.b, win->type, win->firstp.x, win->firstp.y, win->iters);
	reimage(win);
}

void	initwindow(t_window *win)
{
	win->size.x = 800;
	win->size.y = 800;

	win->coloration.z = 1 + E_N2;
	win->coloration.r = 1;
	win->coloration.g = 1;
	win->coloration.b = 2;
	win->cen.x = win->size.x / 2;
	win->cen.y = win->size.y / 2;
	win->using = 0;

	if (win->type == JULIA)
	{
		win->firstp.x = 0;
		win->firstp.y = -0.8f;
		win->iters = MAX_ITER;
	}
	if (win->type == MANDELBROT)
	{
		win->firstp.x = 0;
		win->firstp.y = 0;
		win->iters = MAX_ITER;
	}
	if (win->type == B_SHIP)
	{
		win->firstp.x = 0;
		win->firstp.y = 0;
		win->iters = MAX_ITER;
	}
}

int	manage_mouse(int button, int x, int y, t_window *win)
{
	t_vector_int	temp;

	if (button == 5)
		manage_keys(98, win);
	if (button == 4)
		manage_keys(110, win);
	if (button == 1 && win->type == JULIA)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &temp.x, &temp.y);
		win->firstp.x = (t_ld )temp.x / win->size.x * 4 - 2;
		win->firstp.y = -(t_ld )temp.y / win->size.y * 4 + 2;
		printf("##POINT SET TO: %Lf, %Lf###\n", win->firstp.x, win->firstp.y);
		reimage(win);
	}
}

int	main()
{
	t_window window;

	window.type = 1;
	initwindow(&window);

	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.size.x, window.size.y, "Hello world!");
	window.img.img = mlx_new_image(window.mlx, window.size.x, window.size.y);
	window.img.addr = mlx_get_data_addr(window.img.img, &window.img.bits_per_pixel, &window.img.line_length, &window.img.endian);

	my_image_creator(&window, window.size);
	mlx_put_image_to_window(window.mlx, window.win, window.img.img, 0, 0);

	mlx_hook(window.win, 17, 1L << 0, win_close, &window);
	mlx_hook(window.win, 2, 1L << 0, manage_keys, &window);
	mlx_mouse_hook(window.win, manage_mouse, &window);

	mlx_loop(window.mlx);
}
