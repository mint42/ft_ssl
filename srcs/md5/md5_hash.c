/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:43:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 18:45:50 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_str.h"

# define F(X,Y,Z) ((X & Y) | (~X & Z))
# define G(X,Y,Z) ((X & Z) | (Y & ~Z))
# define H(X,Y,Z) (X ^ Y ^ Z)
# define I(X,Y,Z) ((Y ^ (X | ~Z)


void	md5_hash(char *hash, char *content, int content_size)
{
	int		word_a;
	int		word_b;
	int		word_c;
	int		word_d;

	word_a = 0x01234567;
	word_b = 0x89abcdef;
	word_c = 0xfedcba98;
	word_d = 0x76543210;

	(void)content_size;
	ft_strncpy(hash, content, MD5_HASH_SIZE);
}
