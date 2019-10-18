/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:25:09 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 17:57:55 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# define MD5_HASH_SIZE 128

enum		e_md5_ops
{
	MD5_OP_P = 0,
	MD5_OP_Q,
	MD5_OP_R,
	MD5_OP_S,
	MD5_TOTAL_VALID_OPS,
};

struct s_input;

int		md5_get_arguments(int argc, char **argv, int *argv_index, struct s_input *input);
int		md5_get_options(int argc, char **argv, int *argv_index, struct s_input *input);
void	md5_hash(char *hash, char *content, int content_size);
int		md5_main(int argc, char **argv);

#endif
