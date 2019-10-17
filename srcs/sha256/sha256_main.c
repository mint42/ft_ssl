/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:48:48 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 13:56:59 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg.h"
#include "errors.h"
#include "input.h"
#include "sha256.h"
#include "ft_fd.h"
#include "ft_printf.h"
#include "ft_put.h"
#include "ft_queue.h"
#include "ft_str.h"
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

static void sha256_print_hash(char *hash, char *arg_content, struct s_input *input)
{
	if (ARG(input->args)->type == TYPE_STDIN)
	{
		if (input->opts & SHA256_OP_P)
			ft_putendl(arg_content);
		ft_putendl(hash);
	}
	else if (input->opts & SHA256_OP_Q)
		ft_putendl(hash);
	else if (ARG(input->args)->type == TYPE_FILE)
	{
		if (input->opts & SHA256_OP_R)
			ft_printf("%s %s\n", hash, ARG(input->args)->arg);
		else
			ft_printf("SHA256(%s) = %s\n", ARG(input->args)->arg, hash);
	}
	else
	{
		if (input->opts & SHA256_OP_R)
			ft_printf("%s \"%s\"\n", hash, ARG(input->args)->arg);
		else
			ft_printf("SHA256(\"%s\") = %s\n", ARG(input->args)->arg, hash);
	}
}

static int	get_content_from_fd(struct s_arg *arg, char **arg_content, int *fd)
{
	if (arg->type & TYPE_FILE)
		*fd = open(arg->arg, O_RDONLY);
	else
		*fd = STDIN_FD;
	if (close(*fd) == -1)
		return (ERROR);
	ft_sprintf(arg_content, "this is some argument content\n");
	return (0);
}

static int	handle_argument(struct s_input *input)
{
	static char		hash[SHA256_HASH_SIZE];
	char			*arg_content;
	int				fd;

	fd = 0;
	if (ARG(input->args)->type == TYPE_STRING)
		arg_content = ARG(input->args)->arg;
	else
	{
		if (get_content_from_fd(ARG(input->args), &arg_content, &fd) == ERROR)
		{
			ft_printf("ft_ssl: sha256: %s: %s\n", ARG(input->args)->arg, strerror(errno));
			return (ERROR);
		}
		if (fd == -1)
		{
			ft_printf("ft_ssl: sha256: %s: %s\n", ARG(input->args)->arg, strerror(errno));
			return (0);
		}
	}
	sha256_hash(hash, arg_content);
	sha256_print_hash(hash, arg_content, input);
	if (fd != 0)
		ft_strdel(&arg_content);
	return (0);
}

int		sha256_main(int argc, char **argv)
{
	struct s_input	input;
	int				argv_index;

	input.opts = 0;
	input.args = 0;
	if (sha256_get_options(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	if (sha256_get_arguments(argc, argv, &argv_index, &input) == ERROR)
		return (ERROR);
	while (input.args)
	{
		if (handle_argument(&input) == ERROR)
		{
			ft_queue_del(&(input.args), ft_queue_del_content);
			return (ERROR);
		}
		ft_dequeue(input.args);
	}
	return (0);
}
