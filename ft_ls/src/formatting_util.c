/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:15:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/22 15:56:26 by ktlili           ###   ########.fr       */
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

void	user_perm(mode_t mode, char perm[12])
{
	if (S_IRUSR & mode)
		perm[1] = 'r';
	if (S_IWUSR & mode)
		perm[2] = 'w';
	if (S_IXUSR & mode)
	{
		if (S_ISUID & mode)
			perm[3] = 's';
		else
			perm[3] = 'x';
	}
	else
	{
		if (S_ISUID & mode)
			perm[3] = 'S';
		else
			perm[3] = '-';
	}
}

void	ft_getperm(mode_t mode, char perm[12])
{	
	ft_strncpy(perm,"----------",10);
	perm[0] = ft_filetype(mode);
	user_perm(mode, perm);
	group_perm(mode, perm);
	other_perm(mode, perm);
}
