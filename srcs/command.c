/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:57:30 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/16 16:13:56 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_str.h"

int		get_command_index(char *command)
{
	int					command_index;
	static const char	*valid_commands[TOTAL_VALID_COMMANDS] = {
		"md5",
		"sha256",
		0,
	};
	
	command_index = 0;
	while (command_index < TOTAL_VALID_COMMANDS)
	{
		if (ft_strequ(valid_commands[command_index]), command)
			return (command_index);
		++command_index;
	}
	return (-1);
}

int		execute_command(int command_index, int argc, char **argv)
{
	static void		(*command_table[TOTAL_VALID_COMMANDS])() = {
		md5_main,
		sha256_main,
	};
	
	command_table[command_index](argc, argv);
}
