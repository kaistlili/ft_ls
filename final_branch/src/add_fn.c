/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 01:03:17 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:12:51 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

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
