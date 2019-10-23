/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_macros.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:38:13 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:56:05 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA256_MACROS_H
# define SHA256_MACROS_H

# define SHA256_HASH_SIZE 256

# define RROT(bits, rot) (((uint32_t)(bits >> rot)) | (bits << (32 - rot)))
# define SWPEND(b) (b >> 24 | (b & 0xff0000 >> 8) | (b & 0xff00 << 8) | b << 24)

# define A_O 0
# define B_O 1
# define C_O 2
# define D_O 3
# define E_O 4
# define F_O 5
# define G_O 6
# define H_O 7
# define A 8
# define B 9
# define C 10
# define D 11
# define E 12
# define F 13
# define G 14
# define H 15

#endif
