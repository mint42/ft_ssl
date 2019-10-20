/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:48:10 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 02:23:33 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "sha256.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <stdint.h>

#define RROT(bits, rot) (((unsigned int)(bits >> rot)) | (bits << (32 - rot)))
#define FLIP(bits) ((bits >> 24) | ((bits & 0xff0000) >> 8) | ((bits & 0xff00) << 8) | (bits << 24))

# define A_O 0
# define B_O 1
# define C_O 2
# define D_O 3
# define E_O 4
# define F_O 5
# define G_O 6
# define H_O 7
# define A 8
# define B 9
# define C 10
# define D 11
# define E 12
# define F 13
# define G 14
# define H 15

const uint32_t	g_k2[64] =
{
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

static void	execute_round(int i, unsigned int *word, unsigned int *w)
{
	unsigned int	tmp[6];

	tmp[0] = RROT(word[E], 6) ^ RROT(word[E], 11) ^ RROT(word[E], 25);
	tmp[1] = (word[E] & word[F]) ^ (~word[E] & word[G]);
	tmp[2] = word[H] + tmp[0] + tmp[1] + g_k2[i] + w[i];
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

static void	build_w(unsigned int *w, char *block)
{
	unsigned int	tmp1;
	unsigned int	tmp2;
	int				i;

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

static void	process_block(unsigned int *word, char *block)
{
	unsigned int	w[64];
	int				i;

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

static int	pad_data(char **padded_data, char *data, int *data_size)
{
	int		padded_data_size;
	int		bit_representation;
	int		i;

	padded_data_size = *data_size + 9;
	while ((padded_data_size) % 64)
		++padded_data_size;
	*padded_data = ft_strnew(padded_data_size);
	if (!(*padded_data))
		return (ERROR);
	ft_memcpy(*padded_data, data, *data_size);
	(*padded_data)[*data_size] = (unsigned char)128;
	bit_representation = *data_size * 8;
	i = 0;
	while (i < ((padded_data_size - 8) / 4))
	{
		((unsigned int *)(*padded_data))[i] = FLIP(((unsigned int *)(*padded_data))[i]);
		++i;
	}
	ft_memcpy(*padded_data + padded_data_size - 4, &bit_representation, 4);
	*data_size = padded_data_size;
	return (SUCCESS);
}

void		init_words(unsigned int *word)
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

int			sha256_hash(char **hash, char *data, int data_size)
{
	char			*padded_data;
	char			block[64];
	unsigned int	word[16];
	int				data_processed;

	init_words(word);
	padded_data = 0;
	if (pad_data(&padded_data, data, &data_size) == ERROR)
		return (ERROR);
	data_processed = 0;
	while (data_processed < data_size)
	{
		ft_memcpy(block, padded_data + data_processed, 64);
		process_block(word, block);
		data_processed = data_processed + 64;
	}
	ft_sprintf(hash, "%08x%08x%08x%08x%08x%08x%08x%08x", word[A_O], word[B_O],
		word[C_O], word[D_O], word[E_O], word[F_O], word[G_O], word[H_O]);
	ft_strdel(&padded_data);
	return (SUCCESS);
}
