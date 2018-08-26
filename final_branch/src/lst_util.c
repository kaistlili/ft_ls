/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:33:44 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/26 21:22:54 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void		init_struct(t_file_lst *tmp, char *name)
{
	ft_strncpy(tmp->full_path, name, ft_strlen(name));
	tmp->path_size = ft_strlen(name);
	tmp->long_format = NULL;
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

int		new_file_node(char *path, t_file_lst **new)
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

void	delete_node(t_file_lst *to_delete)
{
	if (to_delete->long_format != NULL)
		free(to_delete->long_format);
	free(to_delete);
}

void	append_lst(t_file_lst **append_to, t_file_lst *to_append)
{
	t_file_lst *iter;

	if (*append_to == NULL)
	{
		*append_to = to_append;
		return ;
	}
	iter = *append_to;
	while (iter->next != NULL)
	{
		iter = iter->next;
	}
	iter->next = to_append;
}

void	add_cap_a(t_file_lst **head, t_file_lst *to_add)
{
	t_file_lst *tmp;

	if (((!ft_strncmp(to_add->name, ".", 1)) && (ft_strlen(to_add->name) == 1))
			|| ((!ft_strncmp(to_add->name, "..", 2))
					&& (ft_strlen(to_add->name) == 2)))
	{
		delete_node(to_add);
		return ;
	}
	if ((*head == NULL) || (g_sort_fn(*head, to_add)))
	{
		to_add->next = *head;
		*head = to_add;
	}
	else
	{
		tmp = *head;
		while ((tmp->next != NULL) && (!g_sort_fn(tmp->next, to_add)))
		{
			tmp = tmp->next;
		}
		to_add->next = tmp->next;
		tmp->next = to_add;
	}
}

void	add_node(t_file_lst **head, t_file_lst *to_add)
{
	t_file_lst *tmp;

	if ((!ft_strncmp(to_add->name, ".", 1)) &&
			(ft_strncmp(to_add->name, "./", 2)) &&
				(ft_strncmp(to_add->name, "../", 3)))
	{
		delete_node(to_add);
		return ;
	}
	if ((*head == NULL) || (g_sort_fn(*head, to_add)))
	{
		to_add->next = *head;
		*head = to_add;
	}
	else
	{
		tmp = *head;
		while ((tmp->next != NULL) && (!g_sort_fn(tmp->next, to_add)))
		{
			tmp = tmp->next;
		}
		to_add->next = tmp->next;
		tmp->next = to_add;
	}
}

void	add_all(t_file_lst **head, t_file_lst *to_add)
{
	t_file_lst *tmp;

	if ((*head == NULL) || (g_sort_fn(*head, to_add)))
	{
		to_add->next = *head;
		*head = to_add;
	}
	else
	{
		tmp = *head;
		while ((tmp->next != NULL) && (!g_sort_fn(tmp->next, to_add)))
		{
			tmp = tmp->next;
		}
		to_add->next = tmp->next;
		tmp->next = to_add;
	}
}

void	destroy_lst(t_file_lst *head)
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
