/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:48:10 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:33:35 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "sha256.h"
#include "sha256_macros.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <stdint.h>

const uint32_t	g_k256[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void	execute_round(uint32_t i, uint32_t *word, uint32_t *w)
{
	uint32_t	tmp[6];

	tmp[0] = RROT(word[E], 6) ^ RROT(word[E], 11) ^ RROT(word[E], 25);
	tmp[1] = (word[E] & word[F]) ^ (~word[E] & word[G]);
	tmp[2] = word[H] + tmp[0] + tmp[1] + g_k256[i] + w[i];
	tmp[3] = RROT(word[A], 2) ^ RROT(word[A], 13) ^ RROT(word[A], 22);
	tmp[4] = (word[A] & word[B]) ^ (word[A] & word[C]) ^ (word[B] & word[C]);
	tmp[5] = tmp[3] + tmp[4];
	word[H] = word[G];
	word[G] = word[F];
	word[F] = word[E];
	word[E] = word[D] + tmp[2];
	word[D] = word[C];
	word[C] = word[B];
	word[B] = word[A];
	word[A] = tmp[2] + tmp[5];
}

static void	build_w(uint32_t *w, uint8_t *block)
{
	uint32_t	tmp1;
	uint32_t	tmp2;
	int			i;

	ft_memcpy(w, block, 64);
	i = 16;
	while (i < 64)
	{
		tmp1 = RROT(w[i - 15], 7) ^ RROT(w[i - 15], 18) ^ (w[i - 15] >> 3);
		tmp2 = RROT(w[i - 2], 17) ^ RROT(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + tmp1 + w[i - 7] + tmp2;
		++i;
	}
}

static void	process_block(uint8_t *block, uint32_t *word)
{
	uint32_t	w[64];
	int			i;

	build_w(w, block);
	word[A] = word[A_O];
	word[B] = word[B_O];
	word[C] = word[C_O];
	word[D] = word[D_O];
	word[E] = word[E_O];
	word[F] = word[F_O];
	word[G] = word[G_O];
	word[H] = word[H_O];
	i = 0;
	while (i < 64)
	{
		execute_round(i, word, w);
		++i;
	}
	word[A_O] = word[A_O] + word[A];
	word[B_O] = word[B_O] + word[B];
	word[C_O] = word[C_O] + word[C];
	word[D_O] = word[D_O] + word[D];
	word[E_O] = word[E_O] + word[E];
	word[F_O] = word[F_O] + word[F];
	word[G_O] = word[G_O] + word[G];
	word[H_O] = word[H_O] + word[H];
}

static int	pad_data(uint8_t **padded_data, char *data, uint32_t *data_size)
{
	uint32_t	padded_data_size;
	uint32_t	bit_representation;
	uint32_t	i;

	padded_data_size = *data_size + 9;
	while ((padded_data_size) % 64)
		++padded_data_size;
	*padded_data = ft_memalloc(padded_data_size);
	if (!(*padded_data))
		return (ERROR);
	ft_memcpy(*padded_data, data, *data_size);
	(*padded_data)[*data_size] = (uint8_t)128;
	bit_representation = *data_size * 8;
	i = 0;
	while (i < ((padded_data_size - 8) / 4))
	{
		((uint32_t *)(*padded_data))[i] = SWPEND(((uint32_t *)(*padded_data))[i]);
		++i;
	}
	ft_memcpy(*padded_data + padded_data_size - 4, &bit_representation, 4);
	*data_size = padded_data_size;
	return (SUCCESS);
}

int			sha256_hash(char **hash, char *data, uint32_t data_size)
{
	uint8_t		*padded_data;
	uint8_t		block[64];
	uint32_t	word[16];
	uint32_t	data_processed;

	sha256_init_words(word);
	padded_data = 0;
	if (pad_data(&padded_data, data, &data_size) == ERROR)
		return (ERROR);
	data_processed = 0;
	while (data_processed < data_size)
	{
		ft_memcpy(block, padded_data + data_processed, 64);
		process_block(block, word);
		data_processed = data_processed + 64;
	}
	ft_sprintf(hash, "%08x%08x%08x%08x%08x%08x%08x%08x", word[A_O], word[B_O],
		word[C_O], word[D_O], word[E_O], word[F_O], word[G_O], word[H_O]);
	ft_memdel((void **)&padded_data);
	return (SUCCESS);
}
