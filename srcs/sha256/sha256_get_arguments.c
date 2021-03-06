/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_get_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:37:47 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:11:34 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "struct_arg.h"
#include "struct_input.h"
#include "ft_queue.h"
#include <stdint.h>

int		sha256_get_arguments(int argc, char **argv, uint8_t *argv_index,
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
	return (0);
}
