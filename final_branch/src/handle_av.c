/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:49:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 01:21:46 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void		ft_validate_input(char *arg)
{
	if (ft_strlen(arg) > 10000)
	{
		ft_printf("ft_ls: File name too long\n");
		exit(1);
	}
}

void		append_lst(t_file_lst **append_to, t_file_lst *to_append)
{
	t_file_lst *iter;

	arg_errors(NULL);
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

t_file_lst	*handle_av(char **av)
{
	t_file_lst	*file_lst;
	t_file_lst	*dir_lst;
	t_file_lst	*tmp;

	file_lst = NULL;
	dir_lst = NULL;
	while (av[g_optind] != NULL)
	{
		ft_validate_input(av[g_optind]);
		if (new_file_node(av[g_optind], &tmp) == 0)
		{
			ft_strncpy(tmp->name, tmp->full_path, ft_strlen(av[g_optind]));
			if (ft_filetype(tmp->data.st_mode) == 'd')
				add_all(&dir_lst, tmp);
			else
				add_all(&file_lst, tmp);
		}
		else
			arg_errors(av[g_optind]);
		g_optind++;
	}
	if (g_format_fn == long_format)
		fill_lf_info(file_lst);
	append_lst(&file_lst, dir_lst);
	return (file_lst);
}
