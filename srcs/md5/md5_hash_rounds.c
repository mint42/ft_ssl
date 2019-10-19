/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash_rounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:34:28 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/19 13:52:01 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "md5.h"

void	round0to15(int i, unsigned int *tmp, int *chunk)
{
	tmp[F] = ((tmp[B] & tmp[C]) | (~tmp[B] & tmp[D]));
	*chunk = i;
}

void	round16to31(int i, unsigned int *tmp, int *chunk)
{
	tmp[F] = ((tmp[B] & tmp[D]) | (tmp[C] & ~tmp[D]));
	*chunk = (5 * i + 1) % 16;
}

void	round32to47(int i, unsigned int *tmp, int *chunk)
{
	tmp[F] = (tmp[B] ^ tmp[C] ^ tmp[D]);
	*chunk = (3 * i + 5) % 16;
}

void	round48to63(int i, unsigned int *tmp, int *chunk)
{
	tmp[F] = (tmp[C] ^ (tmp[B] | ~tmp[D]));
	*chunk = (7 * i) % 16;
}
