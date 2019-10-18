/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:43:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/18 14:10:30 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_str.h"

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
**	These functions (macros for now) will be used by the 4 word buffers
**	(A,B,C,D) to turn 3 words of input into 1 word of output. Each of these
**	functions is done once for every "round" of data (512 bits) that needs to
**	be transformed
*/

# define F(B,C,D) ((B & C) | (~B & D))
# define G(B,C,D) ((B & D) | (C & ~D))
# define H(B,C,D) (B ^ C ^ D)
# define I(B,C,D) ((C ^ (B | ~D)

/*
** This table is used to figure out how far left you rotate the buffer each round
*/

const uint32_t g_rot[] =
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

void	form_message_digest(char *md, struct s_md5 *md5)
{

}


int		fill_data_buffer(struct s_md5 *md5, char *content, int content_size)
{

}

void	transform_data(struct s_md5)
{

}

void	pad_content(char *content, int content_size)
{

}

void	init_md5(struct s_md5 *md5)
{
	int		i;

	i = 0;
	while (i < 64)
	{
		md5->data[i] = 0;
		++i;
	}
	md5->data_len_bytes = 0;
	md5->data_len_bits[0] = 0;
	md5->data_len_bits[1] = 0;
	md5->word[A] = 0x67452301;
	md5->word[B] = 0xefcdab89;
	md5->word[C] = 0x98badcfe;
	md5->word[D] = 0x10325476;
}

void	md5_hash(char *md, char *content, int content_size)
{
	struct s_md5	md5;
	int				content_index;
	int				bytes_filled;

	init_md5(&md5);
	pad_content(&content, &content_size);
	content_index = 0;
	while (content_index < content_size)
	{
		bytes_filled = fill_data_buffer(&md5, content, content_size, content_index);
		if (bytes_filled < 64)
			return (ERROR);
		content_index = content_index + 64;
		transform_data(&md5);
	}
	form_message_digest(md, &md5);
	return (0);
}
