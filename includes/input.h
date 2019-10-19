/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 13:09:48 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/19 10:06:57 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <stdint.h>

typedef struct s_queue	t_queue;

struct			s_input
{
	uint8_t		opts;
	t_queue		*args;
};

#endif
