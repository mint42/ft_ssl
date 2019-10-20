/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:48:10 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 05:31:41 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "sha512.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <stdint.h>

#define RROT(bits, rot) (((unsigned long)(bits >> rot)) | (bits << (64 - rot)))
#define FLIP(bits) ((bits >> 56) | ((bits & 0xff000000000000) >> 40) | ((bits & 0xff0000000000) >> 24) | ((bits & 0xff00000000) >> 8) | ((bits & 0xff000000) << 8) | ((bits & 0xff0000) << 24) | ((bits & 0xff00) << 40) | (bits << 56));

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

const uint64_t	g_k512[64] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static void	execute_round(int i, unsigned long int *word, unsigned long int *w)
{
	unsigned long int	tmp[6];

	tmp[0] = RROT(word[E], 14) ^ RROT(word[E], 18) ^ RROT(word[E], 41);
	tmp[1] = (word[E] & word[F]) ^ (~word[E] & word[G]);
	tmp[2] = word[H] + tmp[0] + tmp[1] + g_k512[i] + w[i];
	tmp[3] = RROT(word[A], 28) ^ RROT(word[A], 34) ^ RROT(word[A], 39);
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

static void	build_w(unsigned long int *w, char *block)
{
	unsigned long int	tmp1;
	unsigned long int	tmp2;
	int				i;

	ft_memcpy(w, block, 80);
	i = 16;
	while (i < 80)
	{
		tmp1 = RROT(w[i - 15], 1) ^ RROT(w[i - 15], 8) ^ (w[i - 15] >> 7);
		tmp2 = RROT(w[i - 2], 19) ^ RROT(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = w[i - 16] + tmp1 + w[i - 7] + tmp2;
		++i;
	}
}

static void	process_block(unsigned long int *word, char *block)
{
	unsigned long int	w[80];
	int					i;

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
	unsigned long int	bit_representation;
	int					padded_data_size;
	int					i;

	padded_data_size = *data_size + 9;
	while ((padded_data_size) % 128)
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
		(unsigned long int *)(*padded_data)[i] = FLIP(*padded_data);
		++i;
	}
	ft_memcpy(*padded_data + padded_data_size - 8, &bit_representation, 8);
	*data_size = padded_data_size;
	return (SUCCESS);
}

int			sha512_hash(char **hash, char *data, int data_size)
{
	char				*padded_data;
	char				block[128];
	unsigned long int	word[16];
	int					data_processed;

	sha512_init_words(word);
	padded_data = 0;
	if (pad_data(&padded_data, data, &data_size) == ERROR)
		return (ERROR);
	data_processed = 0;
	while (data_processed < data_size)
	{
		ft_memcpy(block, padded_data + data_processed, 128);
		process_block(word, block);
		data_processed = data_processed + 128;
	}
	ft_sprintf(hash, "%016lx%016lx%016lx%016lx%016lx%016lx%016lx%016lx",
		word[A_O], word[B_O], word[C_O], word[D_O], word[E_O], word[F_O],
		word[G_O], word[H_O]);
	ft_strdel(&padded_data);
	return (SUCCESS);
}
