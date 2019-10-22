/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:43:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 13:30:30 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "md5.h"
#include "md5_macros.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include <stdint.h>

/*
**	This table has 64 elements. Each element k5[i] is calculated with this
**	equation:
**		k5[i] = 2^32 * abs(sin(i));
**	Where the value of i (1 through 64) is in radians.
*/

const uint32_t g_k5[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

/*
**	There are 4 functions that will each be done 16 times per block of data.
**	They each have the same functionality of 
**		- performing a bit operation on the tmp word buffer F.
**		- determining which block chunk will be added
**		- determining how much left rotation will be applied to tmp[F]
**	Each round# function executes these tasks with slightly different math to
**	ensure the hash is random, and irreversable
*/

static void	execute_round(uint32_t i, uint32_t *tmp, uint32_t *block_chunks)
{
	uint8_t		chunk;
	uint8_t		rot;

	chunk = 0;
	if (i < 16)
		round1(i, tmp, &chunk, &rot);
	else if (i < 32)
		round2(i, tmp, &chunk, &rot);
	else if (i < 48)
		round3(i, tmp, &chunk, &rot);
	else
		round4(i, tmp, &chunk, &rot);
	tmp[F] = tmp[F] + tmp[A] + g_k5[i] + block_chunks[chunk];
	tmp[A] = tmp[D];
	tmp[D] = tmp[C];
	tmp[C] = tmp[B];
	tmp[B] = tmp[B] + LEFT_ROT(tmp[F], rot);
}

/*
**	block_chunks[16]
**		- the block of data is chunked into 16 32 bit words
**
**	tmp_words[5]
**		- tmp_words are 5 working buffers that are used to help update words[4]
**
**	the main processing is done 64 times per block, and depending on the
**	iteration it will re-update the tmp variables differently
*/

static void	process_block(uint8_t *block, uint32_t *words)
{
	uint32_t	block_chunks[16];
	uint32_t	tmp_words[5];
	uint8_t		i;

	i = 0;
	while (i < 16)
	{
		ft_memcpy((void *)&(block_chunks[i]), (void *)&block[i * 4], 4);
		++i;
	}
	tmp_words[A] = words[A];
	tmp_words[B] = words[B];
	tmp_words[C] = words[C];
	tmp_words[D] = words[D];
	i = 0;
	while (i < 64)
	{
		execute_round(i, tmp_words, block_chunks);
		++i;
	}
	words[A] = words[A] + tmp_words[A];
	words[B] = words[B] + tmp_words[B];
	words[C] = words[C] + tmp_words[C];
	words[D] = words[D] + tmp_words[D];
}

/*
**	The string MUST be padded as part of the md5 algorithm. The padding works
**	such that the length (in bits) of the data being hashed should be a
**	multiple of 512 bits (64 bytes), because data is processed in chunks of
**	this size.
**
**	To pad the data, first a '1' bit must be concatonated to the end of the
**	data string, followed by as many '0' bits as it takes to make its size
**	divisible by 64. The end of this string, after the '0' bits, will contain
**	a 64 bit (8 byte) long repsenation of the original data size.
*/

static int	pad_data(uint8_t **padded_data, char *data, uint32_t *data_size)
{
	uint32_t	padded_data_size;
	uint32_t	bit_representation;

	padded_data_size = *data_size + 9;
	while ((padded_data_size) % 64)
		++padded_data_size;
	*padded_data = ft_memalloc(padded_data_size);
	if (!(*padded_data))
		return (ERROR);
	ft_memcpy(*padded_data, data, *data_size);
	(*padded_data)[*data_size] = (uint8_t)128;
	bit_representation = *data_size * 8;
	ft_memcpy(*padded_data + padded_data_size - 8, &bit_representation, 4);
	*data_size = padded_data_size;
	return (SUCCESS);
}

/*
**	padded_data
**		- data must first be padded to multiples of 64 bytes
**
**	block[64]
**		- data is processed in blocks of 64 bytes (512 bits)
**
**	words[4]
**		- 4 "word" buffers, each of size 32 bits, are used when processing
**			the data and have pre-defined initial values. together they hold
**			the total 128 bit md5 hash. they will be referenced as word[A],
**			word[B], word[C], and word[D] with macros for A B C and D.
*/

int			md5_hash(char **hash, char *data, uint32_t data_size)
{
	uint8_t		*padded_data;
	uint8_t		block[64];
	uint32_t	data_processed;
	uint32_t	words[4];

	words[A] = 0x67452301;
	words[B] = 0xefcdab89;
	words[C] = 0x98badcfe;
	words[D] = 0x10325476;
	padded_data = 0;
	if (pad_data(&padded_data, data, &data_size) == ERROR)
		return (ERROR);
	data_processed = 0;
	while (data_processed < data_size)
	{
		ft_memcpy(block, padded_data + data_processed, 64);
		process_block(block, words);
		data_processed = data_processed + 64;
	}
	ft_sprintf(hash, "%08x%08x%08x%08x", SWPEND(words[A]),
		SWPEND(words[B]), SWPEND(words[C]), SWPEND(words[D]));
	ft_memdel((void **)&padded_data);
	return (SUCCESS);
}
