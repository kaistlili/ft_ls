#include "ft_ls.h"
#include <stdio.h>

void	init_opt(t_opt *options)
{
	options->long_f = 1;
	options->Recursive = 1;
	options->show_all = 1;
	options->rev = 1;
	options->time_sort = 1;
}

int	new_element(t_file_list **ptr)
{
	*ptr = malloc(sizeof(t_file_list));
	if (*ptr == NULL)
		return (-1);
	(*ptr)->next = NULL;
	(*ptr)->data = malloc(sizeof(struct stat));
	if ((*ptr)->data == NULL)
	{
		free(*ptr);
		return (-1);
	}
}

void	delete_node(t_file_list *ptr)
{
	free(ptr->data);
	free(ptr);
	ptr = NULL;	
}

void	add_node(t_file_list **chain, t_file_list *to_add)
{
	t_file_list *tmp;
	
	if (*chain == NULL )
		*chain = to_add;
	else
	{
		tmp = *chain;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = to_add;
	}
}

void ft_addtochain(t_file_list **file_list, t_file_list **dir_list,
			 t_file_list *to_add)
{
	t_file_list *tmp;

	if (S_ISDIR(to_add->data->st_mode))
	{
		printf("dir added!\n");
		add_node(dir_list, to_add);
	}
	else
	{
		printf("file added!\n");
		add_node(file_list, to_add);	
	}
	return ;
}

char	ft_type(mode_t st_mode)
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
	return (0)
}

void	ft_fill_struct(char *filename, t_file_list *element)
{
	ft_strncpy(element->path, filename, strlen(filename));
	element->type = ft_type(element->data->st_mode);
}

int handle_params(char **av, t_file_list **file_list, t_file_list **dir_list)
{
	int 		i;
	int			ret;
	t_file_list *tmp;

	i = 1;
	ft_putstr("getting params\n");
	while (av[i] != NULL)
	{
		if (new_element(&tmp) == -1)
			return (-1);	
		ret = lstat(av[i], tmp->data);
		if (ret == -1)
		{
			printf("bad lstat return!\n");
			delete_node(tmp);
		}
		else
		{
			ft_putstr("adding to chain\n");
			ft_fill_struct(av[i],tmp);
			ft_addtochain(file_list, dir_list, tmp);	
		}
		i++;
	}
}

int init_lists(t_file_list **file_list, t_file_list **dir_list)
{
	file_list = malloc(sizeof(t_file_list*));
	if (file_list == NULL)
		return (-1);
	dir_list = malloc(sizeof(t_file_list*));
	if (dir_list == NULL)
	{
		free(file_list);
		return (-1);
	}
	return (0);
}

int main(int ac, char **av)
{
	t_file_list *file_list;
	t_file_list *dir_list;
	t_opt options;
	int ret;
	int i;
	
	i = 1;
	init_opt(&options);
	file_list = NULL;
	dir_list = NULL;
	if (ac > 1)
	{
		handle_params(av, &file_list, &dir_list);
	}
	t_file_list *tmp;
	tmp = file_list;
	while (tmp != NULL)
	{
		printf("element! size: %d\n", tmp->data->st_size);
		tmp = tmp->next;
	}
/*	while (av[i] != NULL)
	{
		printf("filename: %s return %d\n", av[i], ret);
		i++;	
	}*/
}
