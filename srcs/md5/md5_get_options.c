/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_get_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:39:25 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/19 12:50:40 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "errors.h"
#include "input.h"
#include "md5.h"
#include "ft_printf.h"
#include "ft_queue.h"
#include "ft_str.h"

static int		enqueue_new_arg(int option, struct s_input *input, char **argv, int *argv_index)
{
	struct s_arg	*arg;

	arg = 0;
	if (option == MD5_OP_P)
	{
		if (init_arg(&arg, 0, TYPE_STDIN))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	if (option == MD5_OP_S)
	{
		++(*argv_index);
		if (init_arg(&arg, argv[*argv_index], TYPE_STRING))
			return (ERROR);
		ft_enqueue(input->args, arg);
	}
	return (SUCCESS);
}

static int		get_option(int *option, char *argv)
{
	static const char	*valid_ops[MD5_TOTAL_VALID_OPS + 1] = {
		"-p",
		"-q",
		"-r",
		"-s",
		0,
	};

	while (*option < MD5_TOTAL_VALID_OPS)
	{
		if (ft_strequ(valid_ops[*option], argv))
			return (SUCCESS);
		++(*option);
	}
	return (ERROR);
}

int				md5_get_options(int argc, char **argv, int *argv_index, struct s_input *input)
{
	int		option;

	option = 0;
	while (*argv_index < argc && argv[*argv_index][0] == '-')
	{
		if (get_option(&option, argv[*argv_index]) == ERROR)
		{
			ft_printf("ft_ssl: md5: '%s' is an invalid option\n", argv[*argv_index]);
			ft_queue_del(&(input->args), ft_queue_del_content);
			return (ERROR);
		}
		input->opts = (input->opts) | (1 << option);
		if (option == (int)MD5_OP_P || option == (int)MD5_OP_S)
			enqueue_new_arg(option, input, argv, argv_index);
		++(*argv_index);
	}
	return (SUCCESS);
}
