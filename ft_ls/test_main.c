/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 22:42:09 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/07 23:36:09 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

format_ptr	format_fn;
sort_ptr	sort_fn;
add_ptr		add_fn;
stat_ptr	stat_fn;



t_file_lst	*explore_dir(t_file_lst *to_explore);

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
		exit(1); /* PANIC EXIT */
	}
	ft_strncpy(tmp->full_path, "./", 2);
	tmp->path_size = ft_strlen("./");
	return (tmp);
}

int main(int ac, char **av)
{
	t_file_lst *test;

	stat_fn = lstat;

	test = init_current();

	ft_printf("init dir success %s %p\n", test->full_path,test->next);
	ft_printf("mode is: %d data on %p\n", test->data->st_mode, test->data);
	explore_dir(test);
}
