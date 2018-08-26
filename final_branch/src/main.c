/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:45:01 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/26 20:24:44 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

format_ptr	format_fn;
sort_ptr	sort_fn;
add_ptr		add_fn;
stat_ptr	stat_fn;

void	init_args_lst(char **av, t_file_lst **args_lst)
{
	if (av[optind] == NULL)
		new_file_node(".", args_lst);
	else
		*args_lst = handle_av(av);
	stat_fn = lstat;
}

int		main(int ac, char **av)
{
	t_file_lst	**args_lst;
	int			Recursive;
	int			onenode;
	t_file_lst	*tmp;

	Recursive = 0;
	ft_parseopt(ac, av, &Recursive);
	args_lst = malloc(sizeof(t_file_lst*));
	if (args_lst == NULL)
		return (-1);
	init_args_lst(av, args_lst);
	tmp = *args_lst;
	onenode = 0;
	if ((tmp != NULL) && (tmp->next == NULL) && (S_ISDIR(tmp->data.st_mode)))
		onenode = 1;
	while (tmp != NULL)
	{
		if ((!onenode) && (S_ISDIR(tmp->data.st_mode)))
			ft_printf("\n%s:\n", tmp->name);
		ft_inner_ls(tmp, Recursive);
		tmp = tmp->next;
	}
	destroy_lst(*args_lst);
	free(args_lst);
	return (ret_var(0));
}
