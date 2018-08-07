/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 23:46:22 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/07 23:48:07 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	construct_path(char *parent, char *sub_name, char *buff)
{
	int len;

	ft_bzero(buff, 4096);
	len = ft_strlen(parent);
	ft_strncpy(buff, parent, len);
	buff[len] = '/';
	ft_strncpy(&buff[len+1], sub_name, ft_strlen(sub_name));
}

int main(int ac, char **av)
{
	char path[4096];

	construct_path(av[1], av[2], path);
	ft_printf("%s\n", path);
}
