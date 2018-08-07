/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inner_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:03:29 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/07 23:30:42 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


t_file_lst	*explore_dir(t_file_lst *to_explore)
{	
	t_file_lst	*file_lst;
	DIR			*dirp;
	struct	dirent	*entry;
	
	ft_printf("exploring dir %s\n.... data on %p\n", to_explore->full_path,to_explore->data);/*
	if (!S_ISDIR(to_explore->data->st_mode))
		return (NULL);*/
	ft_printf("\nISDIR TRUE\n");
	file_lst = NULL;
	dirp = opendir(to_explore->full_path);
	if (dirp == NULL)
		return (NULL);
	while ((entry = readdir(dirp)) != NULL)
	{
		ft_printf("%s", entry->d_name);
	}
}
/*
int	ft_inner_ls(t_file_lst *source, int Recursive)
{
	t_file_lst *curr_dir;
	t_file_lst *iter;

	curr_dir = NULL;
	if (!S_ISDIR(source->data->st_mode))
	{
		format_fn(source);
		return (0);
	}
	else
	{
		curr_dir = explore_dir(source);
		iter = curr_dir;
		while (iter != NULL)
		{
			format_fn(iter);
			iter = iter->next;
		}
	}
	if (Recursive)
	{
		iter = curr_dir;
		while (iter != NULL)
		{
			if (S_ISDIR(iter->data->st_mode))
				ft_inner_ls(iter, Recursive);
			iter = iter->next;
		}
	}
	return (1);
}*/
