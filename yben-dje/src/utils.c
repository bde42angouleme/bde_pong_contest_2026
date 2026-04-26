/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yben-dje <yben-dje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 17:14:51 by yben-dje          #+#    #+#             */
/*   Updated: 2026/04/26 17:29:53 by yben-dje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pong.h"

float	get_time(void)
{
	struct timespec	res;

	if (clock_gettime(CLOCK_MONOTONIC_RAW, &res) < 0)
		return (0.016);
	return ((double)res.tv_nsec / 1000000000.0 + (double)res.tv_sec);
}
