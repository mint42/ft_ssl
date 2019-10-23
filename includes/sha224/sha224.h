/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 04:07:33 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:56:48 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_H
# define SHA224_H

# include <stdint.h>

struct s_input;

int		sha224_get_arguments(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input);
int		sha224_get_options(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input);
int		sha224_main(int argc, char **argv);

int		sha224_hash(char **hash, char *data, uint32_t data_size);
void	sha224_init_words(uint32_t *word);

#endif
