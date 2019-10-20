/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:07:33 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 04:17:31 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
# define SHA224_H

# define SHA224_HASH_SIZE 224

enum		e_sha224_ops
{
	SHA224_OP_P = 0,
	SHA224_OP_Q,
	SHA224_OP_R,
	SHA224_OP_S,
	SHA224_TOTAL_VALID_OPS,
};

struct s_input;

int		sha224_get_arguments(int argc, char **argv, int *argv_index, struct s_input *input);
int		sha224_get_options(int argc, char **argv, int *argv_index, struct s_input *input);
int		sha224_main(int argc, char **argv);

int		sha224_hash(char **hash, char *data, int data_size);
void	sha224_init_words(unsigned int *word);

#endif
