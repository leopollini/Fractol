/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpollini <lpollini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 18:57:52 by lpollini          #+#    #+#             */
/*   Updated: 2023/07/29 11:32:00 by lpollini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H

# define FRACTOL_H

# define EXITVAL 10
# define LN_ACCURACY 50
# define MAX_ITER 80
# define SQR_RAD 100
# define CHANGE_VAL 0.25f
# define E_0 0.1f
# define E_N1 0.01f
# define E_N2 0.001f
# define SCALE_S 1.2f
# define SCALE_L 2.2f
# define SCALE_LL 12

# include "mlx/mlx.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "fractol.h"

enum	e_fractype
{
	B_SHIP,
	JULIA,
	MANDELBROT,
	TYPE_END
};

typedef long double	t_ld;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bps;
	int		ll;
	int		en;
}				t_data;

typedef struct s_vec_i {
	int	x;
	int	y;
}				t_vec_i;

typedef struct s_vec_ld { //hlep
	t_ld	x;
	t_ld	y;
}				t_vec_ld;

typedef struct s_vec_i_ld {
	t_vec_i			i;
	t_vec_ld		d;
}				t_vec_i_ld;

typedef struct s_color {
	int	t;
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_a_c {
	t_ld	z;
	int		iter;
	t_ld	r;
	t_ld	g;
	t_ld	b;
}				t_a_c;

typedef struct s_window {
	void			*mlx;
	void			*win;
	t_data			img;
	t_vec_i			size;
	t_a_c			col;
	t_ld			z;
	t_ld			s;
	t_ld			invs;
	enum e_fractype	type;
	t_vec_ld		firstp;
	t_vec_ld		cen;
	int				using;
	int				lkey;
	int				iters;
	int				mdown;
}				t_window;

void	my_mlx_pixel_put(t_data *data, int x, int y, int cl);
int		create_trgb(int t, int r, int g, int b);
int		win_close(t_window *win);
void	clear_image(t_window *win, t_vec_i size);
t_ld	square_of(t_ld a);
t_ld	sqr_mod_of(t_vec_ld vec);
int		create_color_overflow(int b, t_a_c cl);
t_ld	mod(t_ld a);
int		j_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl);
int		m_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl);
int		bs_c(t_vec_ld zed, t_ld x, t_ld y, t_a_c cl);
void	stuff_doer(t_window *win, t_vec_i_ld *cen, t_a_c *cl, t_vec_i winsize);
void	j_s(t_window *win, t_vec_i winsize);
void	mandelbrot_set(t_window *win, t_vec_i winsize);
void	burning_ship_set(t_window *win, t_vec_i winsize);
void	my_image_creator(t_window *win, t_vec_i winsize);
void	reimage(t_window *win);
void	type_manager(t_window *win);
void	initw(t_window *win);
int		manage_keys(int keypressed, t_window *win);
int		manage_mouse(int button, int x, int y, t_window *win);

#endif
