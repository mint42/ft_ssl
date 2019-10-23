/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:06:23 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 19:33:59 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_arg.h"
#include "errors.h"
#include "ft_mem.h"

int		init_arg(struct s_arg **arg, char *string, int type)
{
	(*arg) = (struct s_arg *)ft_memalloc(sizeof(struct s_arg));
	if (!*arg)
		return (ERROR);
	(*arg)->arg = string;
	(*arg)->type = type;
	return (0);
}
