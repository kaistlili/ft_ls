/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:49:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/25 22:07:14 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	init_struct(t_file_lst *tmp, char *name)
{	
	ft_strncpy(tmp->full_path, name, ft_strlen(name));
	tmp->path_size = ft_strlen(name);
	tmp->long_format = NULL;
}

void	ft_validate_input(char *arg)
{
	if (ft_strlen(arg) > 10000)
	{
		ft_printf("ft_ls: File name too long\n");
		exit(1);
	}	
}


void	test_linked(t_file_lst *start)
{
	ft_printf("NODES:\n");
	while (start != NULL)
	{
		printf("%s| st_mode %d\n",start->full_path,start->data.st_mode);
		start = start->next;
	}
}

t_file_lst *handle_av(char **av)
{
	t_file_lst	*file_lst;
	t_file_lst	*dir_lst;	
	t_file_lst	*tmp;

	file_lst = NULL;
	dir_lst = NULL;
	while (av[optind] != NULL)
	{	
		ft_validate_input(av[optind]);
		if (new_file_node(av[optind], &tmp) == 0)
		{	
			ft_strncpy(tmp->name, tmp->full_path,ft_strlen(av[optind]));
			if (ft_filetype(tmp->data.st_mode) == 'd')
				add_all(&dir_lst, tmp);
			else
				add_all(&file_lst, tmp) ;	
		}
		else
			arg_errors(av[optind]);
		optind++;
	}	
	if (format_fn == long_format)
		fill_lf_info(file_lst);
	arg_errors(NULL);
	append_lst(&file_lst, dir_lst);
	return (file_lst);
}
