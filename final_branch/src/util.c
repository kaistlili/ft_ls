/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 01:13:54 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:16:55 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	malloc_exit(void)
{
	ft_printf("ft_ls: malloc: %s", strerror(errno));
	exit(1);
}

char	ft_filetype(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return ('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return ('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('p');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return (0);
}
