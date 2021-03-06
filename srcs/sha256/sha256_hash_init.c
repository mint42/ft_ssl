/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 03:54:24 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 15:48:55 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256_macros.h"
#include <stdint.h>

void		sha256_init_words(uint32_t *word)
{
	word[A_O] = 0x6a09e667;
	word[B_O] = 0xbb67ae85;
	word[C_O] = 0x3c6ef372;
	word[D_O] = 0xa54ff53a;
	word[E_O] = 0x510e527f;
	word[F_O] = 0x9b05688c;
	word[G_O] = 0x1f83d9ab;
	word[H_O] = 0x5be0cd19;
}
