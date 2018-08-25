/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inner_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:03:29 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/25 22:05:06 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

/*
	return 0 on !dir or . .. else return 1;
	maybe add infninite link check here ?

*/
int	is_explorable(t_file_lst *node) 
{
	if (!S_ISDIR(node->data.st_mode))
		return (0);
	if (((strlen(node->name) == 1) && (!ft_strncmp(node->name, ".", 1))) ||
			((strlen(node->name) == 2) && (!ft_strncmp(node->name, "..", 2)))) 
		return (0);
	return (1);
}

/*
	our validate input will clean any / from end of string.
	only case we have a / at end of string is ./ or ../
*/
void	construct_path(char *parent, char *sub_name, char *buff)
{
	int len;

	ft_bzero(buff, PATH_MAX);
	len = ft_strlen(parent);
	if (len > PATH_MAX - 1)
		return; /* handle errors here*/
	ft_strncpy(buff, parent, len);
	if (buff[len - 1] == '/')
		ft_strncpy(&buff[len], sub_name, ft_strlen(sub_name));
	else
	{
		buff[len] = '/';		
		ft_strncpy(&buff[len+1], sub_name, ft_strlen(sub_name));
	}
}

void	readdirloop(DIR *dirp, t_file_lst *to_explore, t_file_lst **file_lst)
{
	t_file_lst *tmp;
	char	path[PATH_MAX];
	struct	dirent	*entry;

	while ((entry = readdir(dirp)) != NULL)
	{
		construct_path(to_explore->full_path, entry->d_name, path);
		if (new_file_node(path, &tmp) != 0)
			ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
		else
		{
			ft_strncpy(tmp->name, entry->d_name, ft_strlen(entry->d_name));
			add_fn(file_lst, tmp);
		}
	}	
}
t_file_lst	*explore_dir(t_file_lst *to_explore)
{	
	t_file_lst	*file_lst;
	DIR			*dirp;

	file_lst = NULL;
	if ((!S_ISDIR(to_explore->data.st_mode)) 
			|| (!(S_IXUSR & to_explore->data.st_mode)))
		return (NULL);
	dirp = opendir(to_explore->full_path);
	if (dirp == NULL)
	{
		ft_printf("ft_ls: %s: %s\n",to_explore->full_path,strerror(errno));
		return (NULL);	
	}
	readdirloop(dirp, to_explore, &file_lst);
	closedir(dirp);
	if (format_fn == long_format)
		fill_lf_info(file_lst);
	return (file_lst);
}

void	print_totblk(t_file_lst *curr_dir)
{
	blkcnt_t blocks;

	blocks = 0;
	while (curr_dir != NULL)
	{
		blocks = curr_dir->data.st_blocks + blocks;
		curr_dir = curr_dir->next;
	}
	ft_printf("total %lu\n", blocks);
}

static	void	formatfn_dir(t_file_lst *iter)
{
	if ((format_fn == long_format) && (iter != NULL))
		print_totblk(iter);
	while (iter != NULL)
	{
		format_fn(iter);
		iter = iter->next;
	}
}

int	ft_inner_ls(t_file_lst *current, int Recursive)
{
	t_file_lst *curr_dir;
	t_file_lst *iter;

	if (!S_ISDIR(current->data.st_mode))
	{
		format_fn(current);
		return (0);
	}
	curr_dir = explore_dir(current);
	iter = curr_dir;
	formatfn_dir(iter);
	if (Recursive == 1)
	{
		while (iter != NULL)
		{
			if (is_explorable(iter))
			{
				ft_printf("\n%s:\n", iter->full_path);
				ft_inner_ls(iter, Recursive);
			}
			iter = iter->next;
		}
	}
	destroy_lst(curr_dir);
	return (0);
}
