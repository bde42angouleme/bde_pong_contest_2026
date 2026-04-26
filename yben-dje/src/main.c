/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 13:40:56 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 21:19:18 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

int	main(void)
{
	t_pong	pong;
	double	old_time;

	setup_curses(&pong.win);
	pong.running = true;
	reset(&pong.ball, &pong.left_pad, &pong.right_pad, &pong.input);
	pong.left_pad.score = 0;
	pong.right_pad.score = 0;
	pong.delta = 0.016;
	while (pong.running)
	{
		old_time = get_time();
		handle_physic(&pong);
		if (pong.right_pad.score == 5)
			show_end(pong.win, 1);
		if (pong.left_pad.score == 5)
			show_end(pong.win, 0);
		if (pong.left_pad.score == 5 || pong.right_pad.score == 5)
			break ;
		render(pong.win, pong.ball, pong.left_pad, pong.right_pad);
		usleep(max(0, (0.016 - (get_time() - old_time)) * 1000000));
	}
	delwin(pong.win);
	delwin(stdscr);
	endwin();
}
