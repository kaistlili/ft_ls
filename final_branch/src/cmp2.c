/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 00:35:24 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:17:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int	cmpvoid(t_file_lst *chain, t_file_lst *to_add)
{
	(void)chain;
	(void)to_add;
	return (0);
}

int	cmpsize(t_file_lst *chain, t_file_lst *to_add)
{
	if (chain->data.st_size == to_add->data.st_size)
		return (cmplex(chain, to_add));
	if (chain->data.st_size < to_add->data.st_size)
		return (1);
	return (0);
}

int	cmpsize_r(t_file_lst *chain, t_file_lst *to_add)
{
	if (chain->data.st_size == to_add->data.st_size)
		return (cmplex_r(chain, to_add));
	if (chain->data.st_size < to_add->data.st_size)
		return (0);
	return (1);
}
