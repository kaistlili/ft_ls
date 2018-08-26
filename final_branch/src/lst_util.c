/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:33:44 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:21:27 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void		init_struct(t_file_lst *tmp, char *name)
{
	ft_strncpy(tmp->full_path, name, ft_strlen(name));
	tmp->path_size = ft_strlen(name);
	tmp->long_format = NULL;
}

t_file_lst	*new_node(void)
{
	t_file_lst *tmp;

	tmp = malloc(sizeof(t_file_lst));
	if (tmp == NULL)
		malloc_exit();
	tmp->next = NULL;
	ft_bzero(tmp, sizeof(t_file_lst));
	return (tmp);
}

int			new_file_node(char *path, t_file_lst **new)
{
	int			ret;

	*new = new_node();
	if (*new == NULL)
		return (errno);
	ret = g_stat_fn(path, &((*new)->data));
	if ((ret < 0) && (errno == 62))
		ret = lstat(path, &(*new)->data);
	if (ret < 0)
	{
		delete_node(*new);
		return (errno);
	}
	init_struct(*new, path);
	return (0);
}

void		delete_node(t_file_lst *to_delete)
{
	if (to_delete->long_format != NULL)
		free(to_delete->long_format);
	free(to_delete);
}

void		destroy_lst(t_file_lst *head)
{
	t_file_lst *tmp;

	tmp = head;
	while (head != NULL)
	{
		if (head->long_format != NULL)
			free(head->long_format);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}
