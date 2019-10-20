/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_hash_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 03:54:24 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 04:16:45 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# define A_O 0
# define B_O 1
# define C_O 2
# define D_O 3
# define E_O 4
# define F_O 5
# define G_O 6
# define H_O 7

void		sha256_init_words(unsigned int *word)
{
	word[A_O] = 0x6a09e667;
	word[B_O] = 0xbb67ae85;
	word[C_O] = 0x3c6ef372;
	word[D_O] = 0xa54ff53a;
	word[E_O] = 0x510e527f;
	word[F_O] = 0x9b05688c;
	word[G_O] = 0x1f83d9ab;
	word[H_O] = 0x5be0cd19;
}
