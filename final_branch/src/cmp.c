/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:45:40 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/26 20:16:05 by ktlili           ###   ########.fr       */
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
int	cmplex(t_file_lst *chain, t_file_lst *to_add)
{
	if (ft_strcmp(chain->name, to_add->name) > 0) /*chain_name < add_name */
		return(1); /*insert here */
	return (0); /* keep going */
}

int		cmplex_r(t_file_lst *chain, t_file_lst *to_add)
{
	if (ft_strcmp(chain->name, to_add->name) < 0) /*chain_name < add_name */
		return(1); /*insert here */
	return (0);
}

int		cmpt(t_file_lst *chain, t_file_lst *to_add)
{
	if (chain->data.st_mtime
		   	== to_add->data.st_mtime)
		return (cmplex(chain, to_add));
	if (chain->data.st_mtime
		   	< to_add->data.st_mtime)
		return (1);
	return (0);
}

int		cmpt_r(t_file_lst *chain, t_file_lst *to_add)
{
	if (chain->data.st_mtime
		   	== to_add->data.st_mtime)
		return (cmplex_r(chain, to_add));
	if (chain->data.st_mtime
		   	< to_add->data.st_mtime)
		return (0);
	return (1);
}

void	reg_format(t_file_lst *to_print)
{
	ft_printf("%s\n",to_print->name);
}
void	long_format(t_file_lst *to_print)
{
	char perm[12];
	char link[4096];

	ft_bzero(perm, 12);
	ft_bzero(link, 4096);
	ft_getperm(to_print->data.st_mode, perm);
	ft_printf("%s  ", perm);	
	ft_printf("%s %s  %s  %s %s %s", to_print->long_format->links,
		 to_print->long_format->user, to_print->long_format->group, 
			to_print->long_format->size, to_print->long_format->datetime,
		   		to_print->name);
	if (S_ISLNK(to_print->data.st_mode))
	{
		if (readlink(to_print->full_path, link, 4096) != -1)
			ft_printf(" -> %s", link);
	}
	write(1,"\n",1);
}

