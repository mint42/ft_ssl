/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 11:01:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:48:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MD5_OPTIONS_H
# define MD5_OPTIONS_H

/*
**	options
**
**	-p,	echo STDIN to STDOUT and append the checksum to STDOUT
**	-q, quiet mode
**	-r, reverse the format of the output
**	-s, print the sum of the given string
*/

enum	e_ops
{
	OP_P = 0,
	OP_Q,
	OP_R,
	OP_S,
	TOTAL_VALID_OPS,
};

#endif
