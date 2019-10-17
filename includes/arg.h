/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:58:00 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 13:34:09 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# define TYPE_STDIN 1
# define TYPE_STRING 2
# define TYPE_FILE 3

# define ARG(args) ((struct s_arg *)((args)->first->content))

struct			s_arg
{
	char		*arg;
	int			type;
};

int		init_arg(struct s_arg **arg, char *string, int type);

#endif
