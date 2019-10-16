/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:17:33 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/16 13:18:00 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void			init_input(struct s_input *input)
{
	input.comm = 0;
	input.opts = 0;
	input.args = 0;
	input.n_args = 0;
}
