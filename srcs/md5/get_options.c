/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:34:07 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/16 16:21:57 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "options.h"

static int		enqueue_new_arg(int op_index, struct s_input *input, char **argv, int *argv_index)
{
	struct s_arg	*arg;

	arg = 0;
	if (op_index == OP_P)
	{
		if (init_arg(&arg, 0, TYPE_STDIN))
			return (ERROR);
		ft_enqueue(input->args, node);
	}
	if (op_index == OP_S)
	{
		++(*argv_index);
		if (init_arg(&arg, argv[argv_index], TYPE_STRING))
			return (ERROR);
		ft_enqueue(input->args, node);
	}
	return (0);
}

static int		get_op_index(char *op)
{
	int					op_index;
	static const char	*valid_ops[TOTAL_VALID_OPS] = {
		"-p",
		"-q",
		"-r",
		"-s",
		0,
	};
	
	op_index = 0;
	while (op_index < TOTAL_VALID_OPS)
	{
		if (ft_strequ(valid_ops[op_index]), op)
			return (op_index);
		++op_index;
	}
	return (-1);
}

void			get_options(int argc, char **argv, int *argv_index, struct s_input *input)
{
	int		op_index;

	op_index = 0;
	while (*argv_index < argc && argv[*argv_index][0] == '-')
	{
		op_index = get_op_index(argv[argv_index]);
		if (op_index == -1)
		{
			ft_printf("ft_ssl: md5: '%s' is an invalid option", argv[argv_index]);
			ft_queue_del(input->args, ft_queue_del_content);
			return (ERROR);
		}
		input->ops = (input->ops) | (1 << op_index);
		if (op_index == (OP_P | OP_S))
			enqueue_new_arg(op_index, input, argv, argv_index);
		++(*argv_index);
		++i;
	}
	return (0);
}
