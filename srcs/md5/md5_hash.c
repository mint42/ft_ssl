/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:43:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/18 16:44:45 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_str.h"

# define ROTATE(bits, rot) (((bits) << (rot)) | ((bits) >> (32 - (rot))));

/*
**	NOTES
**
**	four main functions:
**
**		init -- init_md5()
**			initalize the md5 struct
**			datalen = 0;
**			bitlen[0] = 0;
**			bitlen[1] = 0;
**				these are in BIG endian?? supposedly
**			
**		update -- fill_data_buffer()
**			copies data into the md5 struct
**			
**		final -- pad_remaining_data()
**			padding and adding the bitlen[] to the end of data[]
**		
**		transform -- transform_data()
**			takes the md5 struct does the thing to ABCD buffers
*/

/*
** This table is used to figure out how far left you rotate the buffer each round
*/

const uint32_t g_rot[64] =
{
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12,
	17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16,
	23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15,
	21, 6, 10, 15, 21, 6, 10, 15, 21
};

/*
**	This table, for some sort of computing that I will figure out later, is
**	called 'T' (for now) and has 64 elements. Each element T(i) ('i' being the
**	i-th element in the table) is calculated with this equation:
**		T(i) = 2^32 * abs(sin(i));
**	Where the value of i (1 through 64) is in radians.
*/

const uint32_t g_T[64] =
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

static void	execute_round(int round, unsigned int *tmp, unsigned int *buff_chunks)
{
	int				chunk;

	chunk = 0;
	if (round < 16)
		rounds0to15(tmp, &chunk);
	else if (round < 32)
		rounds16to31(tmp, &chunk);
	else if (round < 48)
		rounds32to47(tmp, &chunk);
	else
		rounds48to63(words, &chunk);
	tmp[F] = tmp[F] + tmp[A] + g_T[round] + buff_chunks[chunk];
	tmp[A] = tmp[D];
	tmp[D] = tmp[C];
	tmp[C] = tmp[B];
	tmp[B] = tmp[B] + ROTATE(tmp[F], g_rot[round]);
}

static void	update_words(unsigned int *words, char *buff)
{
	unsigned int	buff_chunks[16];
	unsigned int	tmp_words[5];
	int				i;

	i = 0;
	while (i < 16)
	{
		ft_memcpy(buff_chunks[i], buff[i * 4], 4);
		++i;
	}
	tmp_words[A] = words[A];
	tmp_words[B] = words[B];
	tmp_words[C] = words[C];
	tmp_words[D] = words[D];
	i = 0;
	while (i < 64)
	{
		execute_round(i, tmp_words, chunks);
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
**	multiple of 512 bits (64 bytes), because data is transformed in chunks of
**	this size.
**
**	To pad the data, first a '1' bit must be concatonated to the end of the
**	data string, followed by as many '0' bits as it takes to make its size
**	divisible by 64. The end of this string, after the '0' bits, will contain
**	a 64 bit (8 byte) long repsenation of the original data size.
*/

static int	pad_data(char **data, int *data_size)
{
	char	*padded_data;
	int		padded_data_size;
	int		bit_representation;

	padded_data_size = data_size + 1;
	while ((padded_data_size + 8) % 64)
		++padded_data_size;
	padded_data = ft_strnew(padded_data_size + 8); if (!padded_data)
		return (ERROR);
	ft_memcpy(padded_data, *data, data_size);
	padded_data[*data_size] = (unsigned char)0x80;
	bit_representation = data_size * 8;
	ft_memcpy(padded_data + padded_data_size, &bit_representation, 4);
	ft_strdel(data);
	*data = padded_data;
	*data_size = padded_data_size;
	return (0);
}

void		md5_hash(char *hash, char **data, int data_size)
{
	char			buff[64];
	unsigned int	words[4];
	int				data_processed;

	words[A] = 0x67452301;
	words[B] = 0xefcdab89;
	words[C] = 0x98badcfe;
	words[D] = 0x10325476;
	if (pad_data(data, &data_size) == ERROR)
		return (0);
	data_processed = 0;
	while (data_processed < data_size)
	{
		ft_memcpy(buff, *data + data_processed, 64);
		update_words(words, buff);
		data_processed = data_processed + 64;
	}
	hash = ft_sprintf("%x%x%x%x", words[A], words[B], words[C], words[D]);
	return (0);
}
