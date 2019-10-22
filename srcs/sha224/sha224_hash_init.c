/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_hash_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 03:54:24 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 15:31:33 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha224_macros.h"
#include <stdint.h>

void		sha224_init_words(uint32_t *word)
{
	word[A_O] = 0xc1059ed8;
	word[B_O] = 0x367cd507;
	word[C_O] = 0x3070dd17;
	word[D_O] = 0xf70e5939;
	word[E_O] = 0xffc00b31;
	word[F_O] = 0x68581511;
	word[G_O] = 0x64f98fa7;
	word[H_O] = 0xbefa4fa4;
}
