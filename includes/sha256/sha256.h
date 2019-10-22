/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 12:25:58 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 15:46:20 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef SHA256_H
# define SHA256_H

# include <stdint.h>

struct s_input;

int		sha256_get_arguments(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input);
int		sha256_get_options(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input);
int		sha256_main(int argc, char **argv);

int		sha256_hash(char **hash, char *data, uint32_t data_size);
void	sha256_init_words(uint32_t *word);

#endif
