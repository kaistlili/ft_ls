#include "ft_ls.h"
#include <stdio.h>
#include <stdlib.h>

void	init_opt(t_opt *options)
{
	options->long_f = 1;
	options->Recursive = 1;
	options->show_all = 1;
	options->rev = 1;
	options->time_sort = 1;
}

int	new_element(t_file_list *ptr)
{
	ptr = malloc(sizeof(t_file_list));
	if (ptr == NULL)
		return (-1);
	ptr->next = NULL;
	ptr->data = malloc(sizeof(struct stat));
	if (ptr->data == NULL)
	{
		free(ptr);
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

int handle_params(char **av, t_file_list **file_list, t_file_list **dir_list)
{
	int 		i;
	int			ret;
	t_file_list *tmp;

	i = 1;
	printf("getting params..");
	write(1,"II",2);
	while (av[i] != NULL)
	{
		if (new_element(tmp) == -1)
			return (-1);	
		ret = lstat(av[i], tmp->data);
		if (ret == -1)
		{
			printf("bad lstat return!");
			delete_node(tmp);
		}
		else
		{
			ft_addtochain(file_list, dir_list, tmp);	
		}
		i++;
	}
}

int main(int ac, char **av)
{
	t_file_list **file_list;
	t_file_list **dir_list;
	t_file_list *tmp;
	t_opt options;
	int ret;
	int i;
	
	i = 1;
	init_opt(&options);
	*file_list = NULL;
	*dir_list = NULL;
	if (ac > 1)
	{
		handle_params(av, file_list, dir_list);
	}
/*	while (av[i] != NULL)
	{
		printf("filename: %s return %d\n", av[i], ret);
		i++;	
	}*/
}
