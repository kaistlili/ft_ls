/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formatting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 14:04:24 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:20:12 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	print_totblk(t_file_lst *curr_dir)
{
	blkcnt_t blocks;

	blocks = 0;
	if (curr_dir == NULL)
	{
		ft_printf("total %lu\n", blocks);
		return ;
	}
	while (curr_dir != NULL)
	{
		blocks = curr_dir->data.st_blocks + blocks;
		curr_dir = curr_dir->next;
	}
	ft_printf("total %lu\n", blocks);
}

int		fill_usergroup(t_file_lst *file)
{
	struct passwd	*spwd;
	struct group	*sgrp;

	spwd = getpwuid(file->data.st_uid);
	if (spwd == NULL)
		ft_utoa_base(file->data.st_uid, 10, file->long_format->user, 1);
	else
		ft_strncpy(file->long_format->user,
			spwd->pw_name, ft_strlen(spwd->pw_name));
	sgrp = getgrgid(file->data.st_gid);
	if (sgrp == NULL)
		ft_utoa_base(file->data.st_gid, 10, file->long_format->group, 1);
	else
		ft_strncpy(file->long_format->group,
			sgrp->gr_name, ft_strlen(sgrp->gr_name));
	return (0);
}

void	fill_date(t_file_lst *file)
{
	char *time_str;

	time_str = ctime(&(file->data.st_mtime));
	ft_strncpy(file->long_format->datetime, time_str + 4, 12);
	if (((time(NULL) - file->data.st_mtime) < 0)
			|| ((time(NULL) - file->data.st_mtime) > 15778800))
	{
		file->long_format->datetime[7] = ' ';
		ft_strncpy(file->long_format->datetime + 8, time_str + 20, 4);
	}
}

void	major_minor(dev_t dev, char size[32])
{
	int wrote;

	wrote = ft_utoa_base(major(dev), 10, size, 1);
	size[wrote] = ',';
	wrote++;
	size[wrote] = ' ';
	wrote++;
	ft_utoa_base(minor(dev), 10, &size[wrote], 1);
}

int		fill_lf_info(t_file_lst *start)
{
	t_file_lst	*tmp;
	t_padd		padding;

	tmp = start;
	ft_bzero(&padding, sizeof(t_padd));
	while (start != NULL)
	{
		start->long_format = malloc(sizeof(t_long_f));
		if (start->long_format == NULL)
			malloc_exit();
		ft_bzero(start->long_format, sizeof(t_long_f));
		ft_utoa_base(start->data.st_nlink, 10, start->long_format->links, 1);
		if ((S_ISBLK(start->data.st_mode))
			|| (S_ISCHR(start->data.st_mode)))
			major_minor(start->data.st_rdev, start->long_format->size);
		else
			ft_utoa_base(start->data.st_size, 10, start->long_format->size, 1);
		fill_usergroup(start);
		fill_date(start);
		update_padd(&padding, start->long_format);
		start = start->next;
	}
	fill_padding(tmp, padding);
	return (0);
}
