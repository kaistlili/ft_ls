/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:49:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/08 00:38:59 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int	init_struct(t_file_lst *tmp, char *name)
{
	
	if (ft_strlen(name) > 4096)
		return (-1);

	ft_strncpy(tmp->full_path, name, ft_strlen(name));
	tmp->path_size = ft_strlen(name);
	return (1);
}

void	ft_validate_input(char *arg)
{
	char *last_bslash;

	if ((((strlen(arg) == 1) && (!ft_strncmp(arg, "/", 1))) ||
			 (strlen(arg) == 2) && (!ft_strncmp(arg, "./", 2))) ||
				 (strlen(arg) == 3) && (!ft_strncmp(arg, "../", 3))) 
		return;
	if (*arg == '/')
		arg++;
	last_bslash = ft_strrchr(arg, '/');
	if (last_bslash == NULL)
		return;
	*last_bslash = 0;
	ft_printf("arg is: %s\n", arg);
}


void	test_linked(t_file_lst *start)
{
	ft_printf("NODES:\n");
	while (start != NULL)
	{
		printf("%s| st_mode %d\n",start->full_path,start->data->st_mode);
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
		tmp = new_file_node(av[optind]);
		if (tmp == NULL)
			return (NULL);
		else
		{	
			ft_strncpy(tmp->name, av[optind],ft_strlen(av[optind]));
			if (ft_filetype(tmp->data->st_mode) == 'd')
				add_fn(&dir_lst, tmp);
			else
				add_fn(&file_lst, tmp) ;	
		}
		optind++;
	}
	append_lst(&file_lst, dir_lst);
	return (file_lst);
}
