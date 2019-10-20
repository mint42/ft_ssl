/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:25:58 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 04:16:58 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SHA256_H
# define SHA256_H

# define SHA256_HASH_SIZE 256

enum		e_sha256_ops
{
	SHA256_OP_P = 0,
	SHA256_OP_Q,
	SHA256_OP_R,
	SHA256_OP_S,
	SHA256_TOTAL_VALID_OPS,
};

struct s_input;

int		sha256_get_arguments(int argc, char **argv, int *argv_index, struct s_input *input);
int		sha256_get_options(int argc, char **argv, int *argv_index, struct s_input *input);
int		sha256_main(int argc, char **argv);

int		sha256_hash(char **hash, char *data, int data_size);
void	sha256_init_words(unsigned int *word);

#endif
