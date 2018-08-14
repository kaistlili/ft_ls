/* we call this function at the end of handle_av
and after explore dir*/
#include "../ft_ls.h"

int	fill_usergroup(t_file_lst *file)
{
	struct	passwd	*spwd;
	struct	group	*sgrp;

	spwd = getpwuid(file->data.st_uid);
	if (spwd == NULL)
	{
		//check errno exit on memory errors etc
		return (-1);
	}
	ft_strncpy(file->long_format->user, spwd->pw_name, ft_strlen(spwd->pw_name));
	sgrp = getgrgid(file->data.st_gid);
	if (sgrp == NULL)
	{
		return (-1); //same as last if block
	}
	ft_strncpy(file->long_format->group, sgrp->gr_name, ft_strlen(sgrp->gr_name));
	return (0);
}

/*
void	fill_padding(t_file_lst *start, t_padd padding)
{
	while (start != NULL)
	{
		start->long_format->padding.links_pad = padding.links_pad;
		start->long_format->padding.user_pad = padding.user_pad;
		start->long_format->padding.group_pad = padding.group_pad;
		start->long_format->padding.size_pad = padding.size_pad;
		start = start->next;
	}
}
*/
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

void test_padding(t_padd padding)
{
	ft_printf("links %d user %d grp %d size %d\n",
		padding.links_pad, padding.user_pad, padding.group_pad, padding.size_pad);
}

int	fill_lf_info(t_file_lst	*start) 
{
	t_file_lst	*tmp;
	t_padd		padding;	

	tmp = start;
	ft_bzero(&padding, sizeof(t_padd));
	while (start != NULL)
	{
		start->long_format = malloc(sizeof(t_long_f));
		if (start->long_format == NULL)
			return (-1);	
		ft_bzero(start->long_format, sizeof(t_long_f));
		ft_utoa_base(start->data.st_size, 10, start->long_format->size, 1); 
		ft_utoa_base(start->data.st_nlink, 10, start->long_format->links, 1);
		fill_usergroup(start);
		fill_date(start);
		update_padd(&padding, start->long_format);
		start = start->next;
	}
	fill_padding(tmp, padding);
}
