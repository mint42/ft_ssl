/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_macros.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:20:41 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 12:20:45 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_MACROS_H
# define MD5_MACROS_H

#define LEFT_ROT(bits, rot) (((bits) << (rot)) | ((bits) >> (32 - (rot))))
#define SWPEND(bits) ((bits >> 24) | ((bits & 0xff0000) >> 8) | ((bits & 0xff00) << 8) | (bits << 24))

//#define SWPEND(b) ((b >> 24) | ((b & 0xf) >> 8) | ((b & 0xf) << 8) | (b << 24))

#define A 0
#define B 1
#define C 2
#define D 3
#define F 4

#endif
