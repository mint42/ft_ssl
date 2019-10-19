/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:49:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/19 10:52:46 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "errors.h"
#include "input.h"
#include "md5.h"
#include "ft_fd.h"
#include "ft_printf.h"
#include "ft_put.h"
#include "ft_queue.h"
#include "ft_str.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void print_hash(char *hash, char *data, struct s_input *input)
{
	if (ARG(input->args)->type == TYPE_STDIN)
	{
		if (input->opts & (1 << MD5_OP_P))
			ft_putendl(data);
		ft_putendl(hash);
	}
	else if (input->opts & (1 << MD5_OP_Q))
		ft_putendl(hash);
	else if (ARG(input->args)->type == TYPE_FILE)
	{
		if (input->opts & (1 << MD5_OP_R))
			ft_printf("%s %s\n", hash, ARG(input->args)->arg);
		else
			ft_printf("MD5(%s) = %s\n", ARG(input->args)->arg, hash);
	}
	else
	{
		if (input->opts & (1 << MD5_OP_R))
			ft_printf("%s \"%s\"\n", hash, ARG(input->args)->arg);
		else
			ft_printf("MD5(\"%s\") = %s\n", ARG(input->args)->arg, hash);
	}
}

static int	read_file(int fd, char **data, int *data_size)
{
	int		max_data_size;
	int		red;

	max_data_size = 80;
	*data = ft_strnew(max_data_size);
	if (!*data)
	{
		write(STDOUT_FD, "failed to allocate\n", 19);
		return (ERROR);
	}
	*data_size = 0;
	red = 1;
	while (red > 0)
	{
		red = read(fd, *data + *data_size, 80);
		*data_size = *data_size + red;
		if (*data_size == max_data_size)
		{
			max_data_size = max_data_size * 2;
			ft_stresize(data, 0, max_data_size);
		}
	}
	return (red);
}

static int	get_data_from_fd(struct s_arg *arg, char **data, int *data_size)
{
	int		fd;

	if (arg->type == TYPE_FILE)
	{
		fd = open(arg->arg, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("ft_ssl: md5: %s: %s\n", arg->arg, strerror(errno));
			return (ERROR);
		}
	}
	else
		fd = STDIN_FD;
	if (read_file(fd, data, data_size) == -1)
	{
		ft_printf("ft_ssl: md5: %s\n", strerror(errno));
		return (ERROR);
	}
	if (close(fd) == -1)
	{
		ft_printf("ft_ssl: md5: %s: %s\n", arg->arg, strerror(errno));
		return (ERROR);
	}
	return (0);
}

static int	handle_argument(struct s_input *input)
{
	char	*hash;
	char	*data;
	int		data_size;

	data = 0;
	data_size = 0;
	if (ARG(input->args)->type == TYPE_STRING)
		data = ft_strdup(ARG(input->args)->arg);
	else
	{
		if (get_data_from_fd(ARG(input->args), &data, &data_size) == ERROR)
			return (ERROR);
	}
	if (md5_hash(&hash, &data, data_size) == ERROR)
		return (ERROR);
	print_hash(hash, data, input);
	if (ARG(input->args)->type != TYPE_STRING)
		ft_strdel(&data);
	ft_strdel(&hash);
	return (0);
}

int		md5_main(int argc, char **argv)
{
	struct s_input	input;
	int				argv_index;

	input.opts = 0;
	input.args = ft_queue_init();
	argv_index = 2;
	if (md5_get_options(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	if (md5_get_arguments(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	while ((input.args)->first)
	{
		if (handle_argument(&input) == ERROR)
		{
			ft_queue_del(&(input.args), ft_queue_del_content);
			return (ERROR);
		}
		ft_dequeue(input.args);
	}
	ft_queue_del(&(input.args), ft_queue_del_content);
	return (0);
}
