/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:25:09 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 13:00:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_H
# define MD5_H

# include <stdint.h>

# define MD5_HASH_SIZE 128

struct	s_input;

int		md5_main(int argc, char **argv);
int		md5_get_options(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input);
int		md5_get_arguments(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input);

int		md5_hash(char **hash, char *data, uint32_t data_size);
void	round1(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot);
void	round2(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot);
void	round3(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot);
void	round4(uint8_t i, uint32_t *tmp, uint8_t *chunk, uint8_t *rot);

#endif
