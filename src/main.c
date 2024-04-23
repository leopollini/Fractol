/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:28 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/03 13:20:14 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	reimage(t_window *win)
{
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	my_image_creator(win, win->size);
	mlx_put_image_to_window(win->mlx, win->win, win->img.img, 0, 0);
	mlx_do_sync(win->mlx);
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

int	ft_atoi(const char *str)
{
	int	i;
	int	res;

	if (!str)
		return (0);
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
		res = (res * 10) + (str[i++] - '0');
	return (res);
}

void	initw(t_window *win)
{
	win->type = (win->type + 1) % TYPE_END;
	win->col.z = 1 + E_N2;
	win->col.r = 1;
	win->col.g = 1;
	win->col.b = 2;
	win->cen.x = win->size.x / 2;
	win->cen.y = win->size.y / 2;
	win->using = 0;
	type_manager(win);
}

int	main(int argn, char *strs[])
{
	t_window	w;

	w.type = 0;
	initw(&w);
	if (argn > 2)
		w.size.x = ft_atoi((const char *)strs[1]);
	if (argn > 2)
		w.size.y = ft_atoi((const char *)strs[2]);
	else
	{
		w.size.x = 800;
		w.size.y = 800;
	}
	if (w.size.x <= 0 || w.size.y <= 0)
		return (write(1, "Window size error\n", 8));

	w.mlx = mlx_init();
	w.win = mlx_new_window(w.mlx, w.size.x, w.size.y, "Fract'ol");
	w.img.img = mlx_new_image(w.mlx, w.size.x, w.size.y);
	w.img.addr = mlx_get_data_addr(w.img.img, &w.img.bps, &w.img.ll, &w.img.en);
my_image_creator(&w, w.size);
	mlx_put_image_to_window(w.mlx, w.win, w.img.img, 0, 0);
	mlx_hook(w.win, 17, 1L << 0, win_close, &w);
	mlx_hook(w.win, 2, 1L << 0, manage_keys, &w);
	mlx_mouse_hook(w.win, manage_mouse, &w);
	mlx_loop(w.mlx);
}
