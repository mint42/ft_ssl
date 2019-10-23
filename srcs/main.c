/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:02:51 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 17:59:02 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "md5.h"
#include "sha224.h"
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
		sha224_main,
		sha256_main,
	};

	return (command_table[command](argc, argv));
}

static int		get_command(char *argv)
{
	int					command;
	static const char	*valid_commands[TOTAL_VALID_COMMANDS + 1] = {
		"md5",
		"sha224",
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

static void		print_valid_commands()
{
	write(STDOUT_FD, "\n", 1);
	write(STDOUT_FD, "Standard commands:\n", 19);
	write(STDOUT_FD, "\n", 1);
	write(STDOUT_FD, "Message Digest commands:\n", 25);
	write(STDOUT_FD, "md5\n", 4);
	write(STDOUT_FD, "sha256\n", 7);
	write(STDOUT_FD, "sha224\n", 7);
	write(STDOUT_FD, "\n", 1);
	write(STDOUT_FD, "Cipher commands:\n", 17);
}

#include <unistd.h>
int				main(int argc, char **argv)
{
	int		command;

	if (argc < 2)
	{
		write(STDOUT_FD,
			"usage: ft_ssl command [command opts] [command args]\n", 52);
		return (0);
	}
	command = get_command(argv[1]);
	if (command == -1)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.\n", argv[1]);
		print_valid_commands();
		return (0);
	}
	execute_command(command, argc, argv);
	sleep(10);
	return (0);
}
