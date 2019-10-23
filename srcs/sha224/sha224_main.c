/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:03:00 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 19:40:20 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#include "sha224.h"
#include "sha224_options.h"
#include "struct_arg.h"
#include "struct_input.h"
#include "ft_fd.h"
#include "ft_mem.h"
#include "ft_printf.h"
#include "ft_put.h"
#include "ft_queue.h"
#include "ft_str.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void	print_hash(char *hash, char *data, struct s_input *input)
{
	if (ARG(input->args)->type == TYPE_STDIN)
	{
		if (input->opts & (1 << OP_P))
			ft_putstr(data);
		ft_putendl(hash);
	}
	else if (input->opts & (1 << OP_Q))
		ft_putendl(hash);
	else if (ARG(input->args)->type == TYPE_FILE)
	{
		if (input->opts & (1 << OP_R))
			ft_printf("%s %s\n", hash, ARG(input->args)->arg);
		else
			ft_printf("SHA224 (%s) = %s\n", ARG(input->args)->arg, hash);
	}
	else
	{
		if (input->opts & (1 << OP_R))
			ft_printf("%s \"%s\"\n", hash, ARG(input->args)->arg);
		else
			ft_printf("SHA224 (\"%s\") = %s\n", ARG(input->args)->arg, hash);
	}
}

static int	read_file(int fd, char **data, uint32_t *data_size)
{
	uint32_t	max_data_size;
	int			red;

	max_data_size = 80;
	*data = ft_strnew(max_data_size);
	if (!*data)
		return (ERROR);
	*data_size = 0;
	red = 1;
	while (red > 0)
	{
		red = read(fd, *data + *data_size, 80);
		*data_size = *data_size + red;
		if (*data_size == max_data_size)
		{
			max_data_size = max_data_size * 2;
			*data = ft_stresize(data, 0, max_data_size);
		}
	}
	return (red);
}

static int	get_data_from_fd(struct s_arg *arg, char **data,
				uint32_t *data_size)
{
	int		fd;

	if (arg->type == TYPE_FILE)
	{
		fd = open(arg->arg, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("ft_ssl: sha224: %s: %s\n", arg->arg, strerror(errno));
			return (E_BAD_ARG);
		}
	}
	else
		fd = STDIN_FD;
	if (read_file(fd, data, data_size) == -1)
	{
		ft_printf("ft_ssl: sha224: %s\n", strerror(errno));
		return (E_BAD_ARG);
	}
	if (close(fd) == -1)
	{
		ft_printf("ft_ssl: sha224: %s: %s\n", arg->arg, strerror(errno));
		return (E_BAD_ARG);
	}
	return (SUCCESS);
}

static int	handle_argument(struct s_input *input)
{
	char		*hash;
	char		*data;
	uint32_t	data_size;
	int			exit_code;

	data = 0;
	data_size = ft_strlen(ARG(input->args)->arg);
	if (ARG(input->args)->type == TYPE_STRING)
		data = ft_strdup(ARG(input->args)->arg);
	else
	{
		exit_code = get_data_from_fd(ARG(input->args), &data, &data_size);
		if (exit_code == ERROR)
			return (ERROR);
		if (exit_code == E_BAD_ARG)
			return (SUCCESS);
	}
	if (sha224_hash(&hash, data, data_size) == ERROR)
		return (ERROR);
	print_hash(hash, data, input);
	ft_strdel(&data);
	ft_strdel(&hash);
	return (SUCCESS);
}

int			sha224_main(int argc, char **argv)
{
	struct s_input	input;
	uint32_t		argv_index;
	void			*content;

	input.opts = 0;
	input.args = ft_queue_init();
	argv_index = 2;
	if (sha224_get_options(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	if (sha224_get_arguments(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	while ((input.args)->first)
	{
		if (handle_argument(&input) == ERROR)
		{
			ft_queue_del(&(input.args), 0);
			return (ERROR);
		}
		content = ft_dequeue(input.args);
		ft_memdel(&content);
	}
	ft_queue_del(&(input.args), ft_queue_del_content);
	return (SUCCESS);
}
