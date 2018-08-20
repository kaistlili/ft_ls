/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:28:52 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/20 12:48:47 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

static void	init_fnptr(void)
{
	stat_fn = stat;
	format_fn = reg_format;
	add_fn = add_node;
	sort_fn = cmplex;
}

static	void	set_fnptr(int time_s, int rev_s)
{
	if (time_s)
	{
		if (rev_s)
			sort_fn = cmpt_r;
		else
			sort_fn = cmpt;
		return ;
	}
	else if (rev_s)
		sort_fn = cmplex_r;
}	

int	ft_parseopt(int ac, char **av, int *Recursive)
{
	char chr;
	int rev_s;
	int time_s;
	
	init_fnptr();
	rev_s = 0;
	time_s = 0;
	while ((chr = ft_getopt(ac, av, "Raltr")) != -1)
	{
		if (chr == 'R')
			*Recursive = 1;
		else if (chr == 'l')
		{
			stat_fn = lstat;
			format_fn = long_format;
		}
		else if (chr == 'a')
			add_fn = add_all;
		else if (chr == 'r')
			rev_s = 1;
		else if (chr == 't')
			time_s = 1;
		else if (chr == '?')
			exit(1);
	}
	set_fnptr(time_s,rev_s);
	return (1);
}
