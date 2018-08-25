/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:28:52 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/25 22:08:05 by ktlili           ###   ########.fr       */
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

static	void	set_fnptr(t_options opts)
{
	if (opts.nosort)
	{
		add_fn = add_all;
		sort_fn = cmpvoid;
		return;
	}
	if (opts.size_s)
	{
		if (opts.rev_s)
			sort_fn = cmpsize_r;
		else
			sort_fn = cmpsize;
		return;
	}
	if (opts.time_s)
	{
		if (opts.rev_s)
			sort_fn = cmpt_r;
		else
			sort_fn = cmpt;
		return ;
	}
	else if (opts.rev_s)
		sort_fn = cmplex_r;
}	

int	ft_parseopt(int ac, char **av, int *Recursive)
{
	char	chr;
	t_options opts;

	ft_bzero(&opts, sizeof(t_options));
	init_fnptr();
	while ((chr = ft_getopt(ac, av, "1RaltrfSA")) != -1)
	{
		if (chr == 'R')
			*Recursive = 1;
		else if (chr == 'l')
		{
			stat_fn = lstat;
			format_fn = long_format;
		}
		else if ((chr == 'A') && (add_fn != add_all))
			add_fn = add_A;
		else if (chr == 'S')
			opts.size_s = 1;
		else if (chr == 'a')
			add_fn = add_all;
		else if (chr == 'r')
			opts.rev_s = 1;
		else if (chr == 't')
			opts.time_s = 1;
		else if (chr == 'f')
			opts.nosort = 1;
		else if (chr == '?')
		{
			ft_printf("usage: ft_ls [-lRartfS]\n");
			exit(1);
		}
	}
	set_fnptr(opts);
	return (1);
}
