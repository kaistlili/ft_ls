/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:45:01 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/08 00:32:50 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	printf("\n-----------------\n");
}
/*
t_file_lst	*init_current(void)
{
	t_file_lst *tmp;
	int ret;

	tmp = new_node("./");
	if (tmp == NULL)
		return (NULL);
	ret = stat_fn("./",tmp->data);
	if (ret < 0)
	{
		delete_node(tmp);
		perror("");
		exit(1); 
	}
	return (tmp);
}
*/
int main(int ac, char **av)
{
	t_file_lst	**args_lst;
	t_file_lst	**head;
	int			Recursive;
	int			i;

	i = 1;
	Recursive = 0;
	ft_parseopt(ac, av, &Recursive);	
	parse_test();
	/*	ft_printf("optind: %d\n", optind);*/
	args_lst = malloc(sizeof(t_file_lst*));
	if (args_lst == NULL)
		return (-1);
	if (av[optind] == NULL)
		*args_lst = new_file_node("./");
	else
		*args_lst = handle_av(av);
	if (*args_lst == NULL)
		ft_printf("FATAL ERROR NULL ARG LST\n");
	test_linked(*args_lst);
	ft_printf("calling inner ls:\n");
	ft_inner_ls(*args_lst, 0);
}
