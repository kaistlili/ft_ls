/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inner_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:03:29 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/08 00:41:33 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"



void	construct_path(char *parent, char *sub_name, char *buff)
{
	int len;

	ft_bzero(buff, 4096);
	len = ft_strlen(parent);
	ft_strncpy(buff, parent, len);
	buff[len] = '/';
	ft_strncpy(&buff[len+1], sub_name, ft_strlen(sub_name));
}

t_file_lst	*explore_dir(t_file_lst *to_explore)
{	
	t_file_lst	*file_lst;
	DIR			*dirp;
	struct	dirent	*entry;
	char	path[4096];
	t_file_lst	*tmp;

	if (!S_ISDIR(to_explore->data->st_mode))
		return (NULL);
	file_lst = NULL;
	dirp = opendir(to_explore->full_path);
	if (dirp == NULL)
		return (NULL);
	while ((entry = readdir(dirp)) != NULL)
	{
		construct_path(to_explore->full_path, entry->d_name, path);
		tmp = new_file_node(path);
		ft_strncpy(tmp->name, entry->d_name, ft_strlen(entry->d_name));
		if (tmp == NULL)
		{
			/*free all and exit */
			return (NULL);
		}
		add_fn(&file_lst, tmp);
	}
	closedir(dirp);
	return (file_lst);
}

int	ft_inner_ls(t_file_lst *current, int Recursive)
{
	t_file_lst *curr_dir;
	t_file_lst *iter;

	curr_dir = NULL;
	if (!S_ISDIR(current->data->st_mode))
	{
		format_fn(current);
		return (0);
	}
	else
	{
		curr_dir = explore_dir(current); /* open read close dir
											then return sorted linked list*/
		iter = curr_dir;
		while (iter != NULL)
		{
			format_fn(iter);
			iter = iter->next;
		}
	}/*
	if (Recursive)
	{
		iter = curr_dir;
		while (iter != NULL)
		{
			if (S_ISDIR(current->data->st_mode))
				ft_inner_ls(iter, Recursive);
			iter = iter->next;
		}
	}*/
	return (1);
}
