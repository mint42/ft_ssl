/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash_rounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:34:28 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 12:49:29 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "md5_macros.h"
#include <stdint.h>

void	round1(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot)
{
	static const uint32_t	rot_values[4] = {7, 12, 17, 22};

	tmp[F] = ((tmp[B] & tmp[C]) | (~tmp[B] & tmp[D]));
	*chunk = i;
	*rot = rot_values[i % 4];
}

void	round2(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot)
{
	static const uint32_t	rot_values[4] = {5, 9, 14, 20};
	
	tmp[F] = ((tmp[B] & tmp[D]) | (tmp[C] & ~tmp[D]));
	*chunk = (5 * i + 1) % 16;
	*rot = rot_values[i % 4];
}

void	round3(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot)
{
	static const uint32_t	rot_values[4] = {4, 11, 16, 23};

	tmp[F] = (tmp[B] ^ tmp[C] ^ tmp[D]);
	*chunk = (3 * i + 5) % 16;
	*rot = rot_values[i % 4];
}

void	round4(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot)
{
	static const uint32_t	rot_values[4] = {6, 10, 15, 21};

	tmp[F] = (tmp[C] ^ (tmp[B] | ~tmp[D]));
	*chunk = (7 * i) % 16;
	*rot = rot_values[i % 4];
}
