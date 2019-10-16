/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:49:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/16 15:55:38 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

int		md5_main(int argc, char **argv)
{
	struct s_input	input;
	int				argv_index;

	init_input(&input);
	if (get_options(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	if (get_arguments(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	while (input->args)
	{
		if (hash_md5(input->args) == ERROR)
		{
			ft_queue_del(input->args, ft_queue_del_content);
			return (ERROR);
		}
		ft_dequeue(input->args);
	}
	return (0);
}
