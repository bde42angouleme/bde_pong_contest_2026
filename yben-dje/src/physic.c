/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:14:18 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 20:55:36 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

static int	handle_ball(t_ball *ball, t_pad left_pad, t_pad right_pad,
		double delta)
{
	ball->x += delta * ball->speed_x;
	ball->y += delta * ball->speed_y;
	if ((int)roundl(ball->x) == left_pad.x + 1 && ball->y >= left_pad.y - 2.5
		&& ball->y <= left_pad.y + 2.5)
	{
		ball->speed_x = -ball->speed_x;
		ball->speed_y = (ball->y - left_pad.y) * 2.5;
		ball->x = (double)left_pad.x + 1.6;
	}
	if ((int)roundl(ball->x) == right_pad.x && ball->y >= right_pad.y - 2.5
		&& ball->y <= right_pad.y + 2.5)
	{
		ball->speed_x = -ball->speed_x;
		ball->speed_y = (ball->y - right_pad.y) * 2.5;
		ball->x = (double)right_pad.x - 0.6;
	}
	if (ball->y <= 2.0)
		ball->speed_y = -ball->speed_y;
	if (ball->y >= (double)WIN_HEIGHT - 3.0)
		ball->speed_y = -ball->speed_y;
	if (ball->x <= 2.0)
		return (2);
	if (ball->x >= WIN_WIDTH - 2)
		return (1);
	return (0);
}

void	handle_physic(t_pong *pong)
{
	int	state;

	pong->input.up_delay -= pong->delta;
	pong->input.down_delay -= pong->delta;
	pong->input.e_delay -= pong->delta;
	pong->input.d_delay -= pong->delta;
	handle_keys(pong->win, &pong->running, &pong->input);
	process_inputs(&pong->input, &pong->left_pad, &pong->right_pad,
		pong->delta);
	state = handle_ball(&pong->ball, pong->left_pad, pong->right_pad,
			pong->delta);
	if (state != 0)
		reset(&pong->ball, &pong->left_pad, &pong->right_pad, &pong->input);
	if (state == 1)
		pong->left_pad.score++;
	if (state == 2)
		pong->right_pad.score++;
}
