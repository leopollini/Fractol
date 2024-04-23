/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lol_fullmain.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:28 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/26 19:25:12 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int cl)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bps / 8));
	*(unsigned int *)dst = cl;
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

void	clear_image(t_window *win, t_vec_i size)
{
	t_ld	i;
	t_ld	j;

	i = 0;
	j = 0;
	while (i < size.x)
		while (j < size.y)
			my_mlx_pixel_put(&win->img, i++, j++, 0);
}

t_ld	square_of(t_ld a)
{
	return (a * a);
}

t_ld	sqr_mod_of(t_vec_ld vec)
{
	return (square_of(vec.x) + square_of(vec.y));
}

int	create_color_overflow(int b, t_a_c cl)
{
	return (create_trgb(0, b * cl.r, b * cl.g, b * cl.b));
}

t_ld	mod(t_ld a)
{
	if (a > 0)
		return (a);
	return (-a);
}

int	j_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl)
{
	t_vec_ld	t;
	int			count;

	count = -1;
	while (count++ < cl.iter)
	{
		t.x = x * x;
		t.y = y * y;
		if (t.x + t.y > SQR_RAD)
		{
			return (create_color_overflow(count, cl));
		}
		y = x * y * 2 + zed.y;
		x = t.x - t.y + zed.x;
	}
	return (create_trgb(0, 0, 0, 0));
}

int	m_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl)
{
	t_vec_ld	t;
	int			count;

	count = -1;
	while (count++ < cl.iter)
	{
		t.x = zed.x * zed.x;
		t.y = zed.y * zed.y;
		if (t.x + t.y > SQR_RAD)
		{
			return (create_color_overflow(count, cl));
		}
		zed.y = zed.x * zed.y * 2 + y;
		zed.x = t.x - t.y + x;
	}
	return (create_trgb(0, 0, 0, 0));
}

int	bs_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl)
{
	t_vec_ld	t;
	int			count;

	count = -1;
	while (count++ < cl.iter)
	{
		t.x = zed.x * zed.x;
		t.y = zed.y * zed.y;
		if (t.x + t.y > SQR_RAD)
		{
			return (create_color_overflow(count, cl));
		}
		zed.y = mod(zed.x * zed.y) * 2 + y;
		zed.x = t.x - t.y + x;
	}
	return (create_trgb(0, 0, 0, 0));
}

void	stuff_doer(t_window *win, t_vec_i_ld *cen, t_a_c *cl, t_vec_i winsize)
{
	if (win->col.z != 1 + E_N2)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &cen->i.x, &cen->i.y);
		cen->d.x = (win->cen.x - cen->i.x) * (win->col.z / win->z) + cen->i.x;
		cen->d.y = (win->cen.y - cen->i.y) * (win->col.z / win->z) + cen->i.y;
	}
	else
	{
		win->col.z -= E_N2;
		cen->d.x = winsize.x / 2;
		cen->d.y = winsize.y / 2;
	}
	win->cen.x = cen->d.x;
	win->cen.y = cen->d.y;
	win->z = win->col.z;
	cl->iter = win->iters;
	cen->d.x /= win->s;
	cen->d.y /= win->s;
}

void	j_s(t_window *win, t_vec_i winsize)
{
	t_vec_i_ld		cen;
	t_vec_ld		z;
	t_a_c			cl;
	t_vec_i			c;
	int				t;

	c.x = -1;
	cl = win->col;
	z.x = win->firstp.x;
	z.y = win->firstp.y;
	stuff_doer(win, &cen, &cl, winsize);
	while (++c.x < winsize.x)
	{
		c.y = -1;
		while (++c.y < winsize.y)
		{
			t = j_c(z, c.x / win->s - cen.d.x, c.y / win->s - cen.d.y, cl);
			my_mlx_pixel_put(&win->img, c.x, c.y, t);
		}
	}
}

void	mandelbrot_set(t_window *win, t_vec_i winsize)
{
	t_vec_i_ld		cen;
	t_vec_ld		z;
	t_a_c			cl;
	t_vec_i			c;
	int				t;

	c.x = 0;
	cl = win->col;
	z.x = 0;
	z.y = 0;
	stuff_doer(win, &cen, &cl, winsize);
	while (++c.x < winsize.x)
	{
		c.y = -1;
		while (++c.y < winsize.y)
		{
			t = m_c(z, c.x / win->s - cen.d.x, c.y / win->s - cen.d.y, cl);
			my_mlx_pixel_put(&win->img, c.x, c.y, t);
		}
	}
}

void	burning_ship_set(t_window *win, t_vec_i winsize)
{
	t_vec_i_ld		cen;
	t_vec_ld		z;
	t_a_c			cl;
	t_vec_i			c;
	int				t;

	c.x = 0;
	cl = win->col;
	z.x = 0;
	z.y = 0;
	stuff_doer(win, &cen, &cl, winsize);
	while (++c.x < winsize.x)
	{
		c.y = -1;
		while (++c.y < winsize.y)
		{
			t = bs_c(z, c.x / win->s - cen.d.x, c.y / win->s - cen.d.y, cl);
			my_mlx_pixel_put(&win->img, c.x, c.y, t);
		}
	}
}

void	my_image_creator(t_window *win, t_vec_i winsize)
{
	win->s = winsize.x / 10 * win->col.z;
	if (win->type == JULIA)
	{
		j_s(win, winsize);
	}
	if (win->type == MANDELBROT)
	{
		mandelbrot_set(win, winsize);
	}
	if (win->type == B_SHIP)
	{
		burning_ship_set(win, winsize);
	}
}

void	reimage(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	my_image_creator(win, win->size);
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_do_sync(win->mlx);
	printf("Done!\n");
}

void	type_manager(t_window *win)
{
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

void	initw(t_window *win)
{
	win->type = (win->type + 1) % TYPE_END;
	win->size.x = 800;
	win->size.y = 800;
	win->col.z = 1 + E_N2;
	win->col.r = 1;
	win->col.g = 1;
	win->col.b = 2;
	win->cen.x = win->size.x / 2;
	win->cen.y = win->size.y / 2;
	win->using = 0;
	type_manager(win);
}

int	keys_manager_1(t_window *win, int keypressed)
{
	if (keypressed == 117)
		win->col.r += CHANGE_VAL;
	else if (keypressed == 106)
		win->col.r -= CHANGE_VAL;
	else if (keypressed == 105)
		win->col.g += CHANGE_VAL;
	else if (keypressed == 107)
		win->col.g -= CHANGE_VAL;
	else if (keypressed == 111)
		win->col.b += CHANGE_VAL;
	else if (keypressed == 108)
		win->col.b -= CHANGE_VAL;
	else if (keypressed == 118)
		win->col.z /= SCALE_L;
	else if (keypressed == 98)
		win->col.z /= SCALE_S;
	else if (keypressed == 110)
		win->col.z *= SCALE_S;
	else if (keypressed == 109)
		win->col.z *= SCALE_L;
	else if (keypressed == 113)
		win->firstp.x += E_0;
	else
		return (0);
	return (1);
}

int	keys_manager_2(t_window *win, int keypressed)
{
	if (keypressed == 119)
		win->firstp.x += E_N1;
	else if (keypressed == 101)
		win->firstp.x += E_N2;
	else if (keypressed == 114)
		win->firstp.x -= E_N2;
	else if (keypressed == 116)
		win->firstp.x -= E_N1;
	else if (keypressed == 121)
		win->firstp.x -= E_0;
	else if (keypressed == 97)
		win->firstp.y += E_0;
	else if (keypressed == 115)
		win->firstp.y += E_N1;
	else if (keypressed == 100)
		win->firstp.y += E_N2;
	else if (keypressed == 102)
		win->firstp.y -= E_N2;
	else if (keypressed == 103)
		win->firstp.y -= E_N1;
	else if (keypressed == 104)
		win->firstp.y -= E_0;
	else
		return (0);
	return (1);
}

int	manage_keys(int keypressed, t_window *win)
{
	if (keys_manager_1(win, keypressed))
		(void)win;
	else if (keys_manager_2(win, keypressed))
		(void)win;
	else if (keypressed == 65361)
		win->cen.x += 30;
	else if (keypressed == 65363)
		win->cen.x -= 30;
	else if (keypressed == 65362)
		win->cen.y += 30;
	else if (keypressed == 65364)
		win->cen.y -= 30;
	else if (keypressed == 112)
	{
		initw(win);
	}
	else if (keypressed == 65307)
		win_close(win);
	else
		return (0);
	win->iters = MAX_ITER * log(win->col.z + 25) / 3;
	reimage(win);
}

int	manage_mouse(int button, int x, int y, t_window *win)
{
	t_vec_i	t;

	if (button == 5)
		manage_keys(98, win);
	if (button == 4)
		manage_keys(110, win);
	if (button == 1 && win->type == JULIA)
	{
		mlx_mouse_get_pos(win->mlx, win->win, &t.x, &t.y);
		win->firstp.x = (t_ld)t.x / win->size.x * 4 - 2;
		win->firstp.y = -(t_ld)t.y / win->size.y * 4 + 2;
		reimage(win);
	}
}

int	main( void )
{
	t_window	w;

	w.type = 0;
	initw(&w);
	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, w.size.x, w.size.y, "Fract'ol!");
	w.img.img = mlx_new_image(w.mlx, w.size.x, w.size.y);
	w.img.addr = mlx_get_data_addr(w.img.img, &w.img.bps, &w.img.ll, &w.img.en);
	my_image_creator(&w, w.size);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_hook(w.win, 17, 1L << 0, win_close, &w);
	mlx_hook(w.win, 2, 1L << 0, manage_keys, &w);
	mlx_mouse_hook(w.win, manage_mouse, &w);
	mlx_loop(w.mlx);
}
