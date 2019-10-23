/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_arg.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 16:41:36 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/22 16:41:57 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_ARG_H
# define STRUCT_ARG_H

# include <stdint.h>

# define TYPE_STDIN 1
# define TYPE_STRING 2
# define TYPE_FILE 3

# define ARG(args) ((struct s_arg *)((args)->first->content))

struct			s_arg
{
	char		*arg;
	uint8_t		type;
};

int				init_arg(struct s_arg **arg, char *string, int type);

#endif
