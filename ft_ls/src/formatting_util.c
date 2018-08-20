/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:15:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/20 15:48:52 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	group_perm(mode_t mode, char perm[12])
{
	if (S_IRGRP & mode)
		perm[4] = 'r';
	if (S_IWGRP & mode)
		perm[5] = 'w';
	if (S_IXGRP & mode)
	{
		if (S_ISGID & mode)
			perm[6] = 's';
		else
			perm[6] = 'x';
	}
	else
	{
		if (S_ISGID & mode)
			perm[6] = 'S';
	}
}

void	other_perm(mode_t mode, char perm[12])
{
	if (S_IROTH & mode)
		perm[7] = 'r';
	if (S_IWOTH & mode)
		perm[8] = 'w';
	if (S_IXOTH & mode)
	{
		if (S_ISVTX & mode)
			perm[9] = 't';
		else
			perm[9] = 'x';
	}
	else
	{
		if (S_ISVTX & mode)
			perm[9] = 'T';
	}
}
