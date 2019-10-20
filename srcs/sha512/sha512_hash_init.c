/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_hash_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 03:54:24 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 05:18:46 by rreedy           ###   ########.fr       */
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

void		sha512_init_words(unsigned long int *word)
{
	word[A_O] = 0x6a09e667f3bcc908;
	word[B_O] = 0xbb67ae8584caa73b;
	word[C_O] = 0x3c6ef372fe94f82b;
	word[D_O] = 0xa54ff53a5f1d36f1;
	word[E_O] = 0x510e527fade682d1;
	word[F_O] = 0x9b05688c2b3e6c1f;
	word[G_O] = 0x1f83d9abfb41bd6b;
	word[H_O] = 0x5be0cd19137e2179;
}
