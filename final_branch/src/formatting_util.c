/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 15:15:14 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:20:50 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

static void	group_perm(mode_t mode, char perm[12])
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

static void	other_perm(mode_t mode, char perm[12])
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

static void	user_perm(mode_t mode, char perm[12])
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

void		acl_xattr(t_file_lst *to_print, char *perm)
{
	ssize_t ret;
	acl_t	acl;

	acl = acl_get_file(to_print->full_path, ACL_TYPE_EXTENDED);
	if (acl != NULL)
	{
		acl_free(acl);
		*perm = '+';
	}
	ret = listxattr(to_print->full_path, NULL, 0, XATTR_NOFOLLOW);
	if (ret > 0)
		*perm = '@';
}

void		ft_getperm(mode_t mode, char perm[12])
{
	ft_strncpy(perm, "---------- ", 11);
	perm[0] = ft_filetype(mode);
	user_perm(mode, perm);
	group_perm(mode, perm);
	other_perm(mode, perm);
}
