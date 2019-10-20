/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 05:20:06 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 05:20:55 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA512_H
# define SHA512_H

# define SHA512_HASH_SIZE 512

enum		e_sha512_ops
{
	SHA224_OP_P = 0,
	SHA224_OP_Q,
	SHA224_OP_R,
	SHA224_OP_S,
	SHA224_TOTAL_VALID_OPS,
};

struct s_input;

int		sha512_get_arguments(int argc, char **argv, int *argv_index, struct s_input *input);
int		sha512_get_options(int argc, char **argv, int *argv_index, struct s_input *input);
int		sha512_main(int argc, char **argv);

int		sha512_hash(char **hash, char *data, int data_size);
void	sha512_init_words(unsigned int *word);

#endif
