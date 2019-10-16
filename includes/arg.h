/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:58:00 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/16 16:15:58 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARG_H
# define ARG_H

# define TYPE_STDIN 1
# define TYPE_STRING 2
# define TYPE_FILE 3

struct s_arg	arg
{
	char	*arg;
	int		type;
};

#endif
