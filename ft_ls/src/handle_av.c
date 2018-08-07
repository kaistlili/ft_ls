/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_av.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:49:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/07 21:35:38 by ktlili           ###   ########.fr       */
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

	if (((ft_strlen(arg) == 2) && (!ft_strncmp(arg,"./",2)))
			|| ((strlen(arg) == 1) && (!ft_strncmp(arg, "/", 1))))
		return;
	last_bslash = ft_strrchr(arg, '/');
	if (last_bslash == NULL)
		return;
	*last_bslash = 0;
}


void	test_linked(t_file_lst *start)
{
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
	int ret;
	mode_t todel;

	file_lst = NULL;
	dir_lst = NULL;
	while (av[optind] != NULL)
	{
		
		ft_validate_input(av[optind]);
		tmp = new_node(av[optind]);
		if (tmp == NULL)
			return (NULL);
		ret = stat_fn(av[optind], tmp->data);
		todel = tmp->data->st_mode;	
		if (ret < 0)
		{
			delete_node(tmp);
			perror("");
		}
		else
		{	
			if (init_struct(tmp, av[optind]) == -1)
				ft_printf("Full Path too big for: %s", av[optind]);
			if (ft_filetype(todel) == 'd')
				add_fn(&dir_lst, tmp);
			else
				add_fn(&file_lst, tmp) ;	
		}
		optind++;
	}
	append_lst(&file_lst, dir_lst);
	test_linked(file_lst);
	return (file_lst);
}
