/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pong.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:09:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 17:29:15 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PONG_H
# define PONG_H

# include <locale.h>
# include <math.h>
# include <ncurses.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>

# define WIN_WIDTH 43
# define WIN_HEIGHT 40

# define PAD_SPEED 10.0

typedef struct s_pad
{
	int				x;
	double			y;
	unsigned int	score;
}					t_pad;

typedef struct s_input_keys
{
	bool			up_pressed;
	bool			down_pressed;
	bool			e_pressed;
	bool			d_pressed;

	double			up_delay;
	double			down_delay;
	double			e_delay;
	double			d_delay;
}					t_input_keys;

typedef struct s_ball
{
	double			x;
	double			y;
	double			speed_x;
	double			speed_y;
}					t_ball;

typedef struct s_pong
{
	WINDOW			*win;
	bool			running;
	t_ball			ball;
	t_pad			left_pad;
	t_pad			right_pad;
	t_input_keys	input;
	double			old_time;
	double			new_time;
	double			delta;
}					t_pong;

void				process_inputs(t_input_keys *input, t_pad *left_pad,
						t_pad *right_pad, double delta);
void				handle_keys(WINDOW *win, bool *running,
						t_input_keys *input);
void				handle_physic(t_pong *pong);
void				render(WINDOW *win, t_ball ball, t_pad left_pad,
						t_pad right_pad);
void				show_end(WINDOW *win, int pad);
void				reset(t_ball *ball, t_pad *left_pad, t_pad *right_pad,
						t_input_keys *input);
void				setup_curses(WINDOW **win);
float				get_time(void);

#endif