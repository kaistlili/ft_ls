/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 00:25:36 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 00:29:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	apply_padding(char dest[32], int padding, int rev)
{
	int len;

	if (rev)
		ft_strrev(dest);
	len = ft_strlen(dest);
	while (len < padding)
	{
		dest[len] = ' ';
		len++;
	}
	dest[len] = 0;
	if (rev)
		ft_strrev(dest);
}

void	fill_padding(t_file_lst *start, t_padd padding)
{
	while (start != NULL)
	{
		apply_padding(start->long_format->links, padding.links_pad, 1);
		apply_padding(start->long_format->user, padding.user_pad, 0);
		apply_padding(start->long_format->group, padding.group_pad, 0);
		apply_padding(start->long_format->size, padding.size_pad, 1);
		start = start->next;
	}
}

void	update_padd(t_padd *padding, t_long_f *long_form)
{
	if (padding->links_pad < (int)ft_strlen(long_form->links))
		padding->links_pad = ft_strlen(long_form->links);
	if (padding->user_pad < (int)ft_strlen(long_form->user))
		padding->user_pad = ft_strlen(long_form->user);
	if (padding->group_pad < (int)ft_strlen(long_form->group))
		padding->group_pad = ft_strlen(long_form->group);
	if (padding->size_pad < (int)ft_strlen(long_form->size))
		padding->size_pad = ft_strlen(long_form->size);
}
