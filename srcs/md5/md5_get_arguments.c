/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_get_arguments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:39:37 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:07:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_arg.h"
#include "errors.h"
#include "struct_input.h"
#include "ft_queue.h"
#include <stdint.h>

int		md5_get_arguments(int argc, char **argv, uint32_t *argv_index,
			struct s_input *input)
{
	struct s_arg	*arg;

	arg = 0;
	while (*argv_index < (uint32_t)argc)
	{
		if (init_arg(&arg, argv[*argv_index], TYPE_FILE))
			return (ERROR);
		ft_enqueue(input->args, arg);
		++(*argv_index);
	}
	if (!((input->args)->first))
	{
		if (init_arg(&arg, 0, TYPE_STDIN))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	return (SUCCESS);
}
