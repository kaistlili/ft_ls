/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 00:45:40 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/09 13:28:13 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int	cmplex(t_file_lst *chain, t_file_lst *to_add)
{
	if (ft_strcmp(chain->name, to_add->name) > 0) /*chain_name < add_name */
		return(1); /*insert here */
	return (0); /* keep going */
}

int		cmplex_r(t_file_lst *chain, t_file_lst *to_add)
{
	if (ft_strcmp(chain->name, to_add->name) < 0) /*chain_name < add_name */
		return(1); /*insert here */
	return (0);
}
int		cmpt(t_file_lst *chain, t_file_lst *to_add)
{
	return (1);
}
int		cmpt_r(t_file_lst *chain, t_file_lst *to_add)
{
	return (1);
}

void	reg_format(t_file_lst *to_print)
{
	ft_printf("%s\n",to_print->name);
}

void	long_format(t_file_lst *to_print)
{

}
