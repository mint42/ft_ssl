/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_get_options.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:38:54 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 13:56:39 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "errors.h"
#include "input.h"
#include "sha256.h"
#include "ft_printf.h"
#include "ft_queue.h"
#include "ft_str.h"

static int		enqueue_new_arg(int option, struct s_input *input, char **argv, int *argv_index)
{
	struct s_arg	*arg;

	arg = 0;
	if (option == SHA256_OP_P)
	{
		if (init_arg(&arg, 0, TYPE_STDIN))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	if (option == SHA256_OP_S)
	{
		++(*argv_index);
		if (init_arg(&arg, argv[*argv_index], TYPE_STRING))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	return (0);
}

static int		get_option(char *argv)
{
	int					option;
	static const char	*valid_ops[SHA256_TOTAL_VALID_OPS + 1] = {
		"-p",
		"-q",
		"-r",
		"-s",
		0,
	};

	option = 0;
	while (option < SHA256_TOTAL_VALID_OPS)
	{
		if (ft_strequ(valid_ops[option], argv))
			return (option);
		++option;
	}
	return (-1);
}

int				sha256_get_options(int argc, char **argv, int *argv_index, struct s_input *input)
{
	int		option;

	option = 0;
	while (*argv_index < argc && argv[*argv_index][0] == '-')
	{
		option = get_option(argv[*argv_index]);
		if (option == -1)
		{
			ft_printf("ft_ssl: sha256: '%s' is an invalid option", argv[*argv_index]);
			ft_queue_del(&(input->args), ft_queue_del_content);
			return (ERROR);
		}
		input->opts = (input->opts) | (1 << option);
		if (option == (SHA256_OP_P | SHA256_OP_S))
			enqueue_new_arg(option, input, argv, argv_index);
		++(*argv_index);
	}
	return (0);
}
