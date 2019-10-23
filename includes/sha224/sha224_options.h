/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_options.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:33:20 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 15:34:12 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHA224_OPTIONS_H
# define SHA224_OPTIONS_H

enum		e_ops
{
	OP_P = 0,
	OP_Q,
	OP_R,
	OP_S,
	TOTAL_VALID_OPS,
};

#endif