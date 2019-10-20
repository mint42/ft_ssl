/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_get_arguments.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:37:47 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/20 04:07:22 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "errors.h"
#include "input.h"
#include "ft_queue.h"

int		sha224_get_arguments(int argc, char **argv, int *argv_index, struct s_input *input)
{
	struct s_arg	*arg;

	arg = 0;
	while (*argv_index < argc)
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
