/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:25:09 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/19 13:51:43 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_HASH_SIZE 128

# define A 0
# define B 1
# define C 2
# define D 3
# define F 4

struct	s_input;

/*
**	MD5 reference
**
**	block[64]
**		- data is processed in blocks of 64 bytes (512 bits)
**
**	word[4]
**		- 4 "word" buffers, each of size 32 bits, are used when transforming
**			the data. Together they hold the total 128 bit message digest.
**			They will be referenced as word[A], word[B], word[C], and word[D]
**			with macros for A B C and D.
**
**	flag options
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

int		md5_hash(char **hash, char *data, int data_size);
void	round0to15(int i, unsigned int *tmp, int *chunk);
void	round16to31(int i, unsigned int *tmp, int *chunk);
void	round32to47(int i, unsigned int *tmp, int *chunk);
void	round48to63(int i, unsigned int *tmp, int *chunk);

#endif
