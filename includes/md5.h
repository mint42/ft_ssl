/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:25:09 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/18 13:14:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_HASH_SIZE 128

# define A 0
# define B 1
# define C 2
# define D 3

struct				s_input;

/*
**	MD5 struct
**
**	data[64]
**		- Data is processed in chunks of 64 bytes (512 bits)
**
**	data_len_bytes
**		- Length of data in bytes
**
**	data_len_bits[2]
**		- Length of data in bits, if length is larger than 2^32 then only
**			lowest 2 orders of the length are used
**
**	word[4]
**		- 4 "word" buffers, each of size 32 bits, are used when transforming
**			the data. Together they hold the total 128 bit message digest.
**			They will be referenced as word[A], word[B], word[C], and word[D]
**			with macros for A B C and D.
*/

struct				s_md5
{
	unsigned char	data[64];
	unsigned int	data_len_bytes;
	unsigned int	data_len_bits[2];
	unsigned int	word[4];
};

/*
**	MD5 flag options
**
**	-p,	echo STDIN to STDOUT and append the checksum to STDOUT
**	-q, quiet mode
**	-r, reverse the format of the output
**	-s, print the sum of the given string
**
*/

enum	e_md5_ops
{
		MD5_OP_P = 0,
		MD5_OP_Q,
		MD5_OP_R,
		MD5_OP_S,
		MD5_TOTAL_VALID_OPS,
};

int		md5_main(int argc, char **argv);
int		md5_get_options(int argc, char **argv, int *argv_index, struct s_input *input);
int		md5_get_arguments(int argc, char **argv, int *argv_index, struct s_input *input);

void	md5_hash(char *hash, char *content, int content_size);

#endif
