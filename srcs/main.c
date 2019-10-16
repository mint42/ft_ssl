/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 12:02:51 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/16 16:17:00 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			main(int argc, char **argv)
{
	int		command_index;

	if (argc < 2)
	{
		write(STDOUT_FD, "usage: ft_ssl command [command opts] [command args]", 51);
		return (0);
	}
	command_index = get_command_index(argv[1]);
	if (command_index == -1)
	{
		ft_printf("ft_ssl: Error: '%s' is an invalid command.", argv[1]);
		return (0);
	}
	execute_command(command_index, argc, argv);
	return (0);
}
