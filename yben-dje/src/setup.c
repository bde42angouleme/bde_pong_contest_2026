/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:13:44 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 17:29:49 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

void	reset(t_ball *ball, t_pad *left_pad, t_pad *right_pad,
		t_input_keys *input)
{
	*ball = (t_ball){(double)WIN_HEIGHT / 2.0, (double)WIN_HEIGHT / 2.0, -8.0,
		0.0};
	left_pad->x = 4;
	left_pad->y = (double)WIN_HEIGHT / 2.0;
	right_pad->x = WIN_WIDTH - 5;
	right_pad->y = (double)WIN_HEIGHT / 2.0;
	*input = (t_input_keys){0, 0, 0, 0, 0.0, 0.0, 0.0, 0.0};
}

void	setup_curses(WINDOW **win)
{
	setlocale(LC_ALL, "");
	if (!initscr())
		exit(1);
	noecho();
	raw();
	cbreak();
	curs_set(0);
	refresh();
	*win = newwin(WIN_HEIGHT / 2, WIN_WIDTH, 1, 1);
	box(*win, 0, 0);
	wrefresh(*win);
	keypad(*win, TRUE);
	nodelay(*win, TRUE);
}
