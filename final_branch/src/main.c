/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:45:01 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/27 00:16:37 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

format_ptr	g_format_fn;
sort_ptr	g_sort_fn;
add_ptr		g_add_fn;
stat_ptr	g_stat_fn;
int			g_optind;

void	init_args_lst(char **av, t_file_lst **args_lst)
{
	if (av[g_optind] == NULL)
		new_file_node(".", args_lst);
	else
		*args_lst = handle_av(av);
	g_stat_fn = lstat;
}

int		main(int ac, char **av)
{
	t_file_lst	**args_lst;
	int			recursive;
	int			onenode;
	t_file_lst	*tmp;

	recursive = 0;
	ft_parseopt(ac, av, &recursive);
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
		ft_inner_ls(tmp, recursive);
		tmp = tmp->next;
	}
	destroy_lst(*args_lst);
	free(args_lst);
	return (ret_var(0));
}
