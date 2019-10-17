/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:02:51 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 13:52:56 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "md5.h"
#include "sha256.h"
#include "ssl.h"
#include "ft_fd.h"
#include "ft_printf.h"
#include "ft_str.h"
#include <unistd.h>

static int		execute_command(int command, int argc, char **argv)
{
	static int		(*command_table[TOTAL_VALID_COMMANDS])() = {
		md5_main,
		sha256_main,
	};

	return (command_table[command](argc, argv));
}

static int		get_command(char *argv)
{
	int					command;
	static const char	*valid_commands[TOTAL_VALID_COMMANDS + 1] = {
		"md5",
		"sha256",
		0,
	};
	
	command = 0;
	while (command < TOTAL_VALID_COMMANDS)
	{
		if (ft_strequ(valid_commands[command], argv))
			return (command);
		++command;
	}
	return (-1);
}

int				main(int argc, char **argv)
{
	int		command;

	if (argc < 2)
	{
		write(STDOUT_FD, "usage: ft_ssl command [command opts] [command args]\n", 52);
		return (0);
	}
	command= get_command(argv[1]);
	if (command == -1)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
		return (0);
	}
	execute_command(command, argc, argv);
	return (0);
}
