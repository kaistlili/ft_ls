/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:45:01 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/20 14:54:52 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*

	to do:
	1- add readlink to init struct when stat is specified. | done
	2- verify buffer overflows on path and name. | not
	3- verify error handling.
*/



#include "../ft_ls.h"

format_ptr	format_fn;
sort_ptr	sort_fn;
add_ptr		add_fn;
stat_ptr	stat_fn;

void	parse_test(void)
{
	if (stat_fn == stat)
		ft_printf("stat is set\n");
	else if (stat_fn == lstat)
		ft_printf("lstat is set\n");
	if (format_fn == reg_format)
		ft_printf("reg format is set\n");
	else if (format_fn == long_format)
		ft_printf("long format is set\n");
	if (add_fn == add_node)
		ft_printf("excluding . ..\n");
	else if (add_fn == add_all)
		ft_printf("including. ..\n");
	if (sort_fn == cmplex)
		ft_printf("sorting lexico normal\n");
	else
		ft_printf("other sort function\n");
	ft_printf("\n-----------------\n");
}

int main(int ac, char **av)
{
	t_file_lst	**args_lst;
/*	t_file_lst	**head;
*/	int			Recursive;
	int			onenode;
	t_file_lst *tmp;

	Recursive = 0;
	ft_parseopt(ac, av, &Recursive);	
	parse_test();
	/*	ft_printf("optind: %d\n", optind);*/
	args_lst = malloc(sizeof(t_file_lst*));
	if (args_lst == NULL)
		return (-1);
	if (av[optind] == NULL)
		*args_lst = new_file_node(".");
	else
		*args_lst = handle_av(av);
	if (*args_lst == NULL)
		ft_printf("FATAL ERROR NULL ARG LST\n");
/*	test_linked(*args_lst);
*/	ft_printf("calling inner ls:\n********************\n");
	stat_fn = lstat;	
	tmp = *args_lst;
	onenode = 0;
	if ((tmp->next == NULL) && (S_ISDIR(tmp->data.st_mode)))
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
}
