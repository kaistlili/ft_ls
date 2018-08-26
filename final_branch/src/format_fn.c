/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 00:31:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:02:04 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	reg_format(t_file_lst *to_print)
{
	ft_printf("%s\n", to_print->name);
}

void	long_format(t_file_lst *to_print)
{
	char perm[12];
	char link[PATH_MAX];

	ft_bzero(perm, 12);
	ft_bzero(link, PATH_MAX);
	ft_getperm(to_print->data.st_mode, perm);
	acl_xattr(to_print, perm + 10);
	ft_printf("%s ", perm);
	ft_printf("%s %s  %s  %s %s %s", to_print->long_format->links,
		to_print->long_format->user, to_print->long_format->group,
			to_print->long_format->size, to_print->long_format->datetime,
				to_print->name);
	if (S_ISLNK(to_print->data.st_mode))
	{
		if (readlink(to_print->full_path, link, PATH_MAX) != -1)
			ft_printf(" -> %s", link);
	}
	write(1, "\n", 1);
}

void	formatfn_dir(t_file_lst *iter)
{
	if (g_format_fn == long_format)
		print_totblk(iter);
	while (iter != NULL)
	{
		g_format_fn(iter);
		iter = iter->next;
	}
}
