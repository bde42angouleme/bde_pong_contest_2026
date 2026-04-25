/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 13:40:56 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 01:52:01 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <locale.h>
#include <math.h>
#include <ncurses.h>
#include <stdio.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

void	draw_pad(WINDOW *win, int x, float y)
{
	char	*c;
	int		grid_y;

	char *const parts[] = {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"};
	y += 1.0;
	y /= 2.0;
	c = parts[(int)roundf((1 - (y - floorf(y))) * 8)];
	grid_y = (int)y;
	mvwaddstr(win, grid_y - 1, x, c);
	mvwaddstr(win, grid_y, x, "█");
	wattron(win, A_REVERSE);
	mvwaddstr(win, grid_y + 1, x, c);
	wattroff(win, A_REVERSE);
}

float	get_time(void)
{
	struct timespec	res;

	clock_gettime(CLOCK_MONOTONIC_RAW, &res);
	return ((double)res.tv_nsec / 1000000000.0 + (double)res.tv_sec);
}

typedef struct s_pad
{
	int		x;
	double	y;
}			t_pad;

typedef struct s_input_keys
{
	bool	up_pressed;
	bool	down_pressed;
	bool	e_pressed;
	bool	d_pressed;

	double	up_delay;
	double	down_delay;
	double	e_delay;
	double	d_delay;
}			t_input_keys;

typedef struct s_ball
{
	double	x;
	double	y;
	double	speed_x;
	double	speed_y;
}			t_ball;

void handle_key(bool *pressed, double *delay, double *opposite_delay, bool active)
{
	if (active)
	{
		if (!*pressed)
			*delay = 0.1;
		else
			*delay = 0.1;
		*pressed = true;
		*opposite_delay = 0.0;
	}
	if (*delay < 0.0)
	{
		*pressed = false;
		*delay = 0.0;
	}
}

void handle_ball(t_ball *ball, t_pad left_pad, t_pad right_pad, double delta)
{
	ball->x += delta * ball->speed_x;
	ball->y += delta * ball->speed_y;
	if ((int)roundl(ball->x) == left_pad.x + 1 && ball->y >= left_pad.y - 2.0
		&& ball->y <= left_pad.y + 2.0)
	{
		ball->speed_x = -ball->speed_x;
		ball->x = (double)left_pad.x + 1.6;
	}
	if ((int)roundl(ball->x) == right_pad.x - 1 && ball->y >= right_pad.y - 2.0
		&& ball->y <= right_pad.y + 2.0)
	{
		ball->speed_x = -ball->speed_x;
		ball->x = (double)right_pad.x - 1.6;
	}
	if (ball->y <= 0)
		ball->speed_y = -ball->speed_y;
	if (ball->y >= 40.0)
		ball->speed_y = -ball->speed_y;
}

void render(WINDOW *win, t_ball ball, t_pad left_pad, t_pad right_pad)
{
	werase(win);
	draw_pad(win, left_pad.x, left_pad.y);
	draw_pad(win, right_pad.x, right_pad.y);
	mvwaddstr(win, (int)roundl((ball.y - 0.5) / 2.0), (int)roundl((ball.x - 0.5)),
		"⬤");
	wrefresh(win);
}

void setup_curses(WINDOW **win)
{
	setlocale(LC_ALL, "");
	initscr();
	noecho();
	raw();
	cbreak();
	curs_set(0);
	refresh();
	*win = newwin(40, 40, 1, 1);
	box(*win, 0, 0);
	wrefresh(*win);
	keypad(*win, TRUE);
	nodelay(*win, TRUE);

}

int	main(void)
{
	WINDOW *win;
	bool	running;
	t_ball ball;
	t_pad	left_pad;
	t_pad	right_pad;
	t_input_keys input;
	double	old_time;
	double	new_time;
	double	delta;
	int		key;

	setup_curses(&win);
		
	running = true;
	input.up_pressed = false;
	input.down_pressed = false;
	ball = (t_ball){20.0, 20.0, -5.0, -5.0};
	left_pad = (t_pad){5, 20.0};
	right_pad = (t_pad){35, 20.0};
	input = (t_input_keys){0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0};
	old_time = get_time();
	while (running)
	{
		new_time = get_time();
		delta = new_time - old_time;
		old_time = new_time;
		key = wgetch(win);
		input.up_delay -= delta;
		input.down_delay -= delta;
		input.e_delay -= delta;
		input.d_delay -= delta;
		handle_key(&input.up_pressed, &input.up_delay, &input.down_delay, key == KEY_UP);
		handle_key(&input.down_pressed, &input.down_delay, &input.up_delay, key == KEY_DOWN);
		handle_key(&input.e_pressed, &input.e_delay, &input.d_delay, key == 'e');
		handle_key(&input.d_pressed, &input.d_delay, &input.e_delay, key == 'd');
		if (input.down_pressed)
			right_pad.y += 10.0 * delta;
		if (input.up_pressed)
			right_pad.y -= 10.0 * delta;
		if (input.e_pressed)
			left_pad.y -= 10.0 * delta;
		if (input.d_pressed)
			left_pad.y += 10.0 * delta;
		if (key == 'q')
			running = false;
		handle_ball(&ball, left_pad, right_pad, delta);
		render(win, ball, left_pad, right_pad);
		usleep(1000 * 16);
	}
	wrefresh(win);
	endwin();
}
