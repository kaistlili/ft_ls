/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_opt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:28:52 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/26 21:19:29 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

static void		init_fnptr(void)
{
	g_stat_fn = stat;
	g_format_fn = reg_format;
	g_add_fn = add_node;
	g_sort_fn = cmplex;
}

static	void	set_fnptr(t_options opts)
{
	if (opts.nosort)
	{
		g_add_fn = add_all;
		g_sort_fn = cmpvoid;
		return ;
	}
	if (opts.size_s)
	{
		if (opts.rev_s)
			g_sort_fn = cmpsize_r;
		else
			g_sort_fn = cmpsize;
		return ;
	}
	if (opts.time_s)
	{
		if (opts.rev_s)
			g_sort_fn = cmpt_r;
		else
			g_sort_fn = cmpt;
		return ;
	}
	else if (opts.rev_s)
		g_sort_fn = cmplex_r;
}

static	void	dispatcher(char chr, int *recursive, t_options *opts)
{
	if (chr == 'R')
		*recursive = 1;
	else if (chr == 'l')
	{
		g_stat_fn = lstat;
		g_format_fn = long_format;
	}
	else if ((chr == 'A') && (g_add_fn != add_all))
		g_add_fn = add_cap_a;
	else if (chr == 'S')
		opts->size_s = 1;
	else if (chr == 'a')
		g_add_fn = add_all;
	else if (chr == 'r')
		opts->rev_s = 1;
	else if (chr == 't')
		opts->time_s = 1;
	else if (chr == 'f')
		opts->nosort = 1;
	else if (chr == '?')
	{
		ft_printf("usage: ft_ls [-lRartfS]\n");
		exit(1);
	}
}

int				ft_parseopt(int ac, char **av, int *recursive)
{
	char		chr;
	t_options	opts;

	ft_bzero(&opts, sizeof(t_options));
	init_fnptr();
	while ((chr = ft_getopt(ac, av, "1RaltrfSA")) != -1)
		dispatcher(chr, recursive, &opts);
	set_fnptr(opts);
	return (1);
}
