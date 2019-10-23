/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_macros.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:34:17 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 17:26:52 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_MACROS_H
# define SHA224_MACROS_H

# define SHA224_HASH_SIZE 224

# define RROT(bits, rot) (((uint32_t)(bits >> rot)) | (bits << (32 - rot)))
# define BYTE2(b) (b & 0xff00)
# define BYTE3(b) (b & 0xff0000)
# define SWPEND(b) ((b >> 24) | (BYTE3(b) >> 8) | (BYTE2(b) << 8) | (b << 24))


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
