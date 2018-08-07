/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:33:44 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/08 00:42:00 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

char	ft_filetype(mode_t st_mode)
{
	if (S_ISREG(st_mode))
		return('-');
	else if (S_ISDIR(st_mode))
		return ('d');
	else if (S_ISCHR(st_mode))
		return('c');
	else if (S_ISBLK(st_mode))
		return ('b');
	else if (S_ISFIFO(st_mode))
		return ('f');
	else if (S_ISLNK(st_mode))
		return ('l');
	else if (S_ISSOCK(st_mode))
		return ('s');
	return (0);
}

t_file_lst	*new_node(char *path)
{
	t_file_lst *tmp;

	tmp = malloc(sizeof(t_file_lst));
	if (tmp == NULL)
		return (NULL);
	tmp->next = NULL;
	tmp->data = malloc(sizeof(struct stat));
	if (tmp->data == NULL)
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}


t_file_lst	*new_file_node(char *path)
{
	t_file_lst	*tmp;
	int			ret;

	tmp = new_node(path);
	if (tmp == NULL)
		return (NULL);
	if (init_struct(tmp, path) == -1)
		ft_printf("path too big\n");
	ret = stat_fn(tmp->full_path, tmp->data);
	if (ret < 0)
	{
		delete_node(tmp);
		perror("");
		return (NULL);
	}
	return (tmp);
}



void	delete_node(t_file_lst *to_delete)
{
	free(to_delete->data);
	free(to_delete);
}

int	cmplex(t_file_lst *chain, t_file_lst *to_add)
{
	char *to_add_name;
	char *chain_name;

	int var;

	to_add_name = ft_strrchr(to_add->full_path, '/');
	chain_name = ft_strrchr(chain->full_path, '/');
	if (to_add_name == NULL)
		to_add_name = to_add->full_path;
	else
		to_add_name++;
	if (chain_name == NULL)
		chain_name = chain->full_path;
	else
		chain_name++;
	if ((var = ft_strcmp(chain_name, to_add_name)) > 0) /*chain_name < add_name */
		return(1); /*insert here */
	return (0); /* keep going */
}

void	append_lst(t_file_lst **append_to, t_file_lst *to_append)
{
	t_file_lst *iter;

	if (*append_to == NULL)
	{
		*append_to = to_append;
		return;
	}
	iter = *append_to;
	while (iter->next != NULL)
	{
		iter = iter->next;
	}
	iter->next = to_append;
}

void	add_node(t_file_lst **head, t_file_lst *to_add)
{
	t_file_lst *tmp;

	if ((!ft_strncmp(to_add->name,".",1)) && 
		(ft_strncmp(to_add->name,"./",2)))
		/*THIS IS WRONG AND WILL CHANGE */
	{/*we have to extract name from path before strcmp otherwise we break -R */
		delete_node(to_add);
		return;
	}
	if ((*head == NULL ) || (sort_fn(*head, to_add)))
	{
		to_add->next = *head;
		*head = to_add;
	}
	else
	{
		tmp = *head;	
		while ((tmp->next != NULL) && (!sort_fn(tmp->next, to_add)))  
		{
			tmp = tmp->next;
		}
		to_add->next = tmp->next;
		tmp->next = to_add;
	}
}

void	add_all(t_file_lst **head, t_file_lst *to_add)
{
	t_file_lst *tmp;
	
	if ((*head == NULL ) || (sort_fn(*head, to_add)))
	{
		to_add->next = *head;
		*head = to_add;
	}
	else
	{
		tmp = *head;	
		while ((tmp->next != NULL) && (!sort_fn(tmp->next, to_add)))  
		{
			tmp = tmp->next;
		}
		to_add->next = tmp->next;
		tmp->next = to_add;	
	}
}
