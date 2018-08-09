/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inner_ls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:03:29 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/09 13:56:59 by ktlili           ###   ########.fr       */
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

	ft_bzero(buff, 4096);
	len = ft_strlen(parent);
	if (len > 4096 - 1)
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
/*
void	construct_path(char *parent, char *sub_name, char *buff)
{
	int len;

	ft_bzero(buff, 4096);
	len = ft_strlen(parent);
	ft_strncpy(buff, parent, len);
	if ((!ft_strncmp(parent,"/",1)) && (len == 1))
		len--;
	else
		buff[len] = '/';
	ft_strncpy(&buff[len+1], sub_name, ft_strlen(sub_name));

//	ft_printf("constructing %s| %s|got:%s\n",parent,sub_name,buff);
}*/

t_file_lst	*explore_dir(t_file_lst *to_explore)
{	
	t_file_lst	*file_lst;
	DIR			*dirp;
	struct	dirent	*entry;
	char	path[4096];
	t_file_lst	*tmp;

	file_lst = NULL;
	if (!S_ISDIR(to_explore->data.st_mode))
		return (NULL);
	dirp = opendir(to_explore->full_path);
	if (dirp == NULL)
	{
		ft_printf("cant open dir: %s: %s\n",to_explore->full_path,strerror(errno));
		return (NULL);	
	}
	while ((entry = readdir(dirp)) != NULL)
	{
		construct_path(to_explore->full_path, entry->d_name, path);
		tmp = new_file_node(path);
		if (tmp == NULL)
		{
			/*free all and exit */
			return (NULL);
		}	
		ft_strncpy(tmp->name, entry->d_name, ft_strlen(entry->d_name));
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
	if (!S_ISDIR(current->data.st_mode))
	{
		format_fn(current);
		return (0);
	}
	curr_dir = explore_dir(current); /* open read close dir
											then return sorted linked list*/
	iter = curr_dir;
	while (iter != NULL)
	{
		format_fn(iter);
		iter = iter->next;
	}
	if (Recursive == 1)
	{
		iter = curr_dir;
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
	return (1);
}
