/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:45:40 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:17:22 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int	cmplex(t_file_lst *chain, t_file_lst *to_add)
{
	if (ft_strcmp(chain->name, to_add->name) > 0)
		return (1);
	return (0);
}

int	cmplex_r(t_file_lst *chain, t_file_lst *to_add)
{
	if (ft_strcmp(chain->name, to_add->name) < 0)
		return (1);
	return (0);
}

int	cmpt(t_file_lst *chain, t_file_lst *to_add)
{
	if (chain->data.st_mtime == to_add->data.st_mtime)
		return (cmplex(chain, to_add));
	if (chain->data.st_mtime < to_add->data.st_mtime)
		return (1);
	return (0);
}

int	cmpt_r(t_file_lst *chain, t_file_lst *to_add)
{
	if (chain->data.st_mtime == to_add->data.st_mtime)
		return (cmplex_r(chain, to_add));
	if (chain->data.st_mtime < to_add->data.st_mtime)
		return (0);
	return (1);
}
