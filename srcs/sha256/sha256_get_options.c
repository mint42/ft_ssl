/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_get_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:38:54 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 15:44:58 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "sha256.h"
#include "sha256_options.h"
#include "struct_arg.h"
#include "struct_input.h"
#include "ft_printf.h"
#include "ft_queue.h"
#include "ft_str.h"
#include <stdint.h>

static int		enqueue_new_arg(uint8_t option, struct s_input *input, char **argv, uint32_t *argv_index)
{
	struct s_arg	*arg;

	arg = 0;
	if (option == OP_P)
	{
		if (init_arg(&arg, 0, TYPE_STDIN))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	if (option == OP_S)
	{
		++(*argv_index);
		if (init_arg(&arg, argv[*argv_index], TYPE_STRING))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	return (SUCCESS);
}

static int		get_option(uint8_t *option, char *argv)
{
	static const char	*valid_ops[TOTAL_VALID_OPS + 1] = {
		"-p",
		"-q",
		"-r",
		"-s",
		0,
	};

	*option = 0;
	while (*option < TOTAL_VALID_OPS)
	{
		if (ft_strequ(valid_ops[*option], argv))
			return (SUCCESS);
		++(*option);
	}
	return (ERROR);
}

int				sha256_get_options(int argc, char **argv, uint32_t *argv_index, struct s_input *input)
{
	uint8_t		option;

	option = 0;
	while (*argv_index < (uint32_t)argc && argv[*argv_index][0] == '-')
	{
		if (get_option(&option, argv[*argv_index]) == ERROR)
		{
			ft_printf("ft_ssl: sha256: '%s' is an invalid option", argv[*argv_index]);
			ft_queue_del(&(input->args), ft_queue_del_content);
			return (ERROR);
		}
		input->opts = (input->opts) | (1 << option);
		if (option == (uint8_t)OP_P || option == (uint8_t)OP_S)
			enqueue_new_arg(option, input, argv, argv_index);
		++(*argv_index);
	}
	return (SUCCESS);
}
