/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rreedy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 10:43:46 by rreedy            #+#    #+#             */
/*   Updated: 2019/10/17 13:19:19 by rreedy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"
#include "ft_str.h"

void	md5_hash(char *hash, char *string)
{
	ft_strncpy(hash, string, MD5_HASH_SIZE);
}