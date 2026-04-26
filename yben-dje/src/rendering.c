/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:33:08 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 17:33:53 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

static void	draw_pad(WINDOW *win, int x, float y)
{
	char *const	parts[] = {" ", "▁", "▂", "▃", "▄", "▅", "▆", "▇", "█"};
	char	*c;
	int		grid_y;

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

void	render(WINDOW *win, t_ball ball, t_pad left_pad, t_pad right_pad)
{
	werase(win);
	box(win, 0, 0);
	draw_pad(win, left_pad.x, left_pad.y);
	draw_pad(win, right_pad.x, right_pad.y);
	mvwprintw(win, 2, WIN_WIDTH / 2 - 1, "%d:%d", left_pad.score,
		right_pad.score);
	mvwaddstr(win, (int)roundl((ball.y - 0.5) / 2.0), (int)roundl((ball.x
				- 0.5)), "⬤");
	wrefresh(win);
}

void	show_end(WINDOW *win, int pad)
{
	const char	*left_msg = "Left player won!";
	const char	*right_msg = "Right player won!";

	nodelay(win, FALSE);
	werase(win);
	box(win, 0, 0);
	if (pad == 0)
		mvwaddstr(win, WIN_HEIGHT / 4, (WIN_WIDTH - strlen(left_msg)) / 2,
			left_msg);
	if (pad == 1)
		mvwaddstr(win, WIN_HEIGHT / 4, (WIN_WIDTH - strlen(right_msg)) / 2,
			right_msg);
	wrefresh(win);
	sleep(1);
	wgetch(win);
}
