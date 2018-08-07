/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 01:45:01 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/06 20:24:35 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	reg_format(t_file_lst *to_print);
void	long_format(t_file_lst *to_print);

int		cmplex(t_file_lst *to_add, t_file_lst *chain);
int		cmplex_r(t_file_lst *to_add, t_file_lst *chain);
int		cmpt(t_file_lst *to_add, t_file_lst *chain);
int		cmpt_r(t_file_lst *to_add, t_file_lst *chain);

void	add_node(t_file_lst *add, t_file_lst **chain);
void	add_all(t_file_lst *add, t_file_lst **chain);

extern	format_pt	format_fn;
extern	sort_pt		sort_fn;
extern	sort_pt		add_fn;
extern	stat_pt		stat_fn;

int ft_ls(t_file_lst *arg_list, int Rec)
{
	t_file_lst *current_dir;
	t_file_lst *tmp;

	if (!IS_DIR(arg_list->data->st_mode))
		/* long_f or regular then return*/
	else
		current_dir = explore_dir(arg_list); /*get s_stat list for current dir */	
	tmp = current_dir;
	ft_printf("total %d\n", total_blocks)
	while (tmp != NULL) /* lst_iter on list with &format*/
	{
		long_format(tmp);
		tmp = tmp->next;
	}
	tmp = current_dir;
	while( tmp  != NULL)
	{
		ft_inner_ls(current_dir, Rec);
		tmp = tmp->next;
	}
	delete_lst(current_dir);
}

int main(int ac, char **av)
{
	t_file_lst **args_list;
	t_file_ls **head;
	int recursive;
	int i;

	i = 1;
	Recrusive = 0;
	if (ac > 1)
	{
		i = ft_get_opt(av[1], &recrusive);/*2 if ok, 1 if no valid input */
		if (av[i] != NULL)
			args_list = handle_params(av);
		else
			arg_list = NULL;
	}
	if (arg_list == NULL)
		init_current(&arg_list);
	head = arg_list;
	while (arg_list != NULL)
	{
		ft_ls(arg_list, Recrusive)
		arg_list = arg_list->next;
	}
	delete_lst(head);
}
