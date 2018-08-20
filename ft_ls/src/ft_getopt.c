/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:03:23 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/20 13:45:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

extern int optind;

static int	ft_char_cmp(char c, const char *str)
{
	while (*str != 0)
	{
		if (c == *str)
			return (1);
		str++;
	}
	return (0);
}

static int next_arg(char **nextchar, char *const argv[])
{
	if (argv[optind] == NULL)
		return (-1);
	*nextchar = argv[optind];
	if ((**nextchar != '-') || (!ft_strncmp(*nextchar, "--", 2)))
	{
		if (!ft_strncmp(*nextchar, "--", 2))
			optind++;
		return (-1);
	}
	*nextchar = *nextchar + 1;
	if (**nextchar == 0)
		return (-1);
	return (0);
}

static void	handle_invalid(char *const name, char c)
{
	ft_printf("%s: illegal option -- %c\n", name, c);
}

int	ft_getopt(int argc, char *const argv[], const char *optstring)
{
	static char *nextchar = NULL;
	static int	init = 1;
	int ret;

	(void)argc;
	if (init)
	{
		optind = 1;
		if (next_arg(&nextchar, argv) == -1)
			return (-1);	
		init = 0;
	}
	if (*nextchar == 0)
	{
		optind++;
		if (next_arg(&nextchar, argv) == -1)
			return (-1);
	}
	ret = 63;
	if (ft_char_cmp(*nextchar, optstring) == 1)
		ret = (int)*nextchar;
	else
		handle_invalid(argv[0], *nextchar);
	nextchar++;
	return (ret);	
}
