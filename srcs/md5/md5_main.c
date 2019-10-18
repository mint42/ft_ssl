/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 15:49:52 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 17:57:14 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "errors.h"
#include "input.h"
#include "md5.h"
#include "ft_fd.h"
#include "ft_printf.h"
#include "ft_queue.h"
#include "ft_str.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void print_hash(char *hash, char *content, int content_size, struct s_input *input)
{
	if (ARG(input->args)->type == TYPE_STDIN)
	{
		if (input->opts & MD5_OP_P)
			write(STDOUT_FD, content, content_size);
		write(STDOUT_FD, hash, MD5_HASH_SIZE);
	}
	else if (input->opts & MD5_OP_Q)
		write(STDOUT_FD, hash, MD5_HASH_SIZE);
	else if (ARG(input->args)->type == TYPE_FILE)
	{
		if (input->opts & MD5_OP_R)
			ft_printf("%s %s\n", hash, ARG(input->args)->arg);
		else
			ft_printf("MD5(%s) = %s\n", ARG(input->args)->arg, hash);
	}
	else
	{
		if (input->opts & MD5_OP_R)
			ft_printf("%s \"%s\"\n", hash, ARG(input->args)->arg);
		else
			ft_printf("MD5(\"%s\") = %s\n", ARG(input->args)->arg, hash);
	}
}

static int	read_file(int fd, char **content, int *content_size)
{
	int		max_content_size;
	int		red;

	max_content_size = 80;
	*content = ft_strnew(max_content_size);
	if (!*content)
	{
		write(STDOUT_FD, "failed to allocate\n", 19);
		return (ERROR);
	}
	*content_size = 0;
	red = 1;
	while (red > 0)
	{
		red = read(fd, *content + *content_size, 80);
		*content_size = *content_size + red;
		if (*content_size == max_content_size)
		{
			max_content_size = max_content_size * 2;
			ft_stresize(content, 0, max_content_size);
		}
	}
	return (red);
}

static int	get_content_from_fd(struct s_arg *arg, char **content, int *content_size)
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
	if (read_file(fd, content, content_size) == -1)
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
	static char		hash[MD5_HASH_SIZE];
	char			*content;
	int				content_size;

	content = 0;
	content_size = 0;
	if (ARG(input->args)->type == TYPE_STRING)
		content = ARG(input->args)->arg;
	else
	{
		if (get_content_from_fd(ARG(input->args), &content, &content_size) == ERROR)
			return (ERROR);
	}
	md5_hash(hash, content, content_size);
	print_hash(hash, content, content_size, input);
	if (ARG(input->args)->type != TYPE_STRING)
		ft_strdel(&content);
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
