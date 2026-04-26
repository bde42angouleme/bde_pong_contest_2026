/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:12:20 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 21:19:08 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

static void	handle_key(bool *pressed, double *delay, double *opposite_delay,
		bool active)
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

void	handle_keys(WINDOW *win, bool *running, t_input_keys *input)
{
	int		key;
	bool	states[4];

	memset(states, 0, 4 * sizeof(bool));
	key = 0;
	while (key != ERR)
	{
		key = wgetch(win);
		if (key == KEY_UP)
			states[0] = true;
		if (key == KEY_DOWN)
			states[1] = true;
		if (key == 'e')
			states[2] = true;
		if (key == 'd')
			states[3] = true;
		if (key == 'q')
			*running = false;
	}
	handle_key(&input->up_pressed, &input->up_delay, &input->down_delay,
		states[0]);
	handle_key(&input->down_pressed, &input->down_delay, &input->up_delay,
		states[1]);
	handle_key(&input->e_pressed, &input->e_delay, &input->d_delay, states[2]);
	handle_key(&input->d_pressed, &input->d_delay, &input->e_delay, states[3]);
}

void	process_inputs(t_input_keys *input, t_pad *left_pad, t_pad *right_pad,
		double delta)
{
	if (input->down_pressed)
		right_pad->y += PAD_SPEED * delta;
	if (input->up_pressed)
		right_pad->y -= PAD_SPEED * delta;
	if (input->e_pressed)
		left_pad->y -= PAD_SPEED * delta;
	if (input->d_pressed)
		left_pad->y += PAD_SPEED * delta;
	if (left_pad->y <= 3.0)
		left_pad->y = 3.0;
	if (left_pad->y >= (double)WIN_HEIGHT - 5.1)
		left_pad->y = (double)WIN_HEIGHT - 5.1;
	if (right_pad->y <= 3.0)
		right_pad->y = 3.0;
	if (right_pad->y >= (double)WIN_HEIGHT - 5.1)
		right_pad->y = (double)WIN_HEIGHT - 5.1;
}
