/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_hash_init.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 03:54:24 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 04:18:04 by rreedy           ###   ########.fr       */
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

void		sha224_init_words(unsigned int *word)
{
	word[A_O] = 0xc1059ed8;
	word[B_O] = 0x367cd507;
	word[C_O] = 0x3070dd17;
	word[D_O] = 0xf70e5939;
	word[E_O] = 0xffc00b31;
	word[F_O] = 0x68581511;
	word[G_O] = 0x64f98fa7;
	word[H_O] = 0xbefa4fa4;
}
