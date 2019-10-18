/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash_rounds.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 16:34:28 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/18 16:36:42 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "md5.h"

void	rounds0to15(int round, unsigned int *tmp, int *chunk)
{
	tmp[F] = ((tmp[B] & tmp[C]) | (~tmp[B] & tmp[D]));
}

void	rounds16to31(int round, unsigned int *tmp, int *chunk)
{
	tmp[F] = ((tmp[B] & tmp[D]) | (tmp[C] & ~tmp[D]));
	*chunk = (5 * round + 1) % 16;
}

void	rounds32to47(int round, unsigned int *tmp, int *chunk)
{
	tmp[F] = (tmp[B] ^ tmp[C] ^ tmp[D]);
	*chunk = (3 * round + 5) % 16;
}

void	rounds48to63(int round, unsigned int *tmp, int *chunk)
{
	tmp[F] = ((tmp[C] ^ (tmp[B] | ~tmp[D])
	*chunk = (7 * round) % 16;
}
