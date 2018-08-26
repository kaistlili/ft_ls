/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/22 15:48:41 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/26 21:41:03 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

void	malloc_exit(void)
{
	ft_printf("ft_ls: malloc: %s", strerror(errno));
	exit(1);
}

t_err_lst	*new_err_lst(char *path, char *errstr)
{
	t_err_lst	*tmp;

	tmp = malloc(sizeof(t_err_lst));
	if (tmp == NULL)
		malloc_exit();
	tmp->error = malloc(ft_strlen(errstr) + 1);
	if (tmp->error == NULL)
		malloc_exit();
	ft_bzero(tmp->full_path, PATH_MAX);
	ft_bzero(tmp->error, ft_strlen(errstr) + 1);
	ft_strncpy(tmp->error, errstr, ft_strlen(errstr));
	ft_strncpy(tmp->full_path, path, ft_strlen(path));
	tmp->next = NULL;
	return (tmp);
}

void	add_err(t_err_lst **head, t_err_lst *to_add)
{
	t_err_lst *tmp;

	if ((*head == NULL)
			|| (ft_strcmp((*head)->full_path, to_add->full_path) > 0))
	{
		to_add->next = *head;
		*head = to_add;
	}
	else
	{
		tmp = *head;
		while ((tmp->next != NULL)
				&& ((ft_strcmp(tmp->next->full_path, to_add->full_path)) < 0))
			tmp = tmp->next;
		to_add->next = tmp->next;
		tmp->next = to_add;
	}
}

void	print_lst(t_err_lst *err_lst)
{
	t_err_lst *tmp;

	tmp = err_lst;
	while (tmp != NULL)
	{
		ft_printf("ft_ls: %s: %s\n", tmp->full_path, tmp->error);
		tmp = tmp->next;
	}
	tmp = err_lst;
	while (err_lst != NULL)
	{
		free(err_lst->error);
		tmp = err_lst->next;
		free(err_lst);
		err_lst = tmp;
	}
}

int	ret_var(int ret)
{
	static	int	var_return = 0;

	if (ret)
		var_return = ret;
	return (var_return);
}

void	arg_errors(char *path)
{
	static	t_err_lst	*err_lst = NULL;
	t_err_lst			*tmp;
	char				*errstr;

	if (path == NULL)
		print_lst(err_lst);
	else
	{
		ret_var(1);
		errstr = strerror(errno);
		tmp = new_err_lst(path, errstr);
		add_err(&err_lst, tmp);
	}
}
