/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_macros.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:20:41 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 17:26:04 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_MACROS_H
# define MD5_MACROS_H

# define LROT(bits, rot) (((bits) << (rot)) | ((bits) >> (32 - (rot))))
# define BYTE2(b) (b & 0xff00)
# define BYTE3(b) (b & 0xff0000)
# define SWPEND(b) ((b >> 24) | (BYTE3(b) >> 8) | (BYTE2(b) << 8) | (b << 24))

# define A 0
# define B 1
# define C 2
# define D 3
# define F 4

#endif
