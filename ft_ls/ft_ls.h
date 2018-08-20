/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktlili <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 18:23:18 by ktlili            #+#    #+#             */
/*   Updated: 2018/08/20 13:52:32 by ktlili           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <sys/dirent.h>
#include "libft.h"
#include "ft_printf.h"

/*
	every int will contain max strlen for current chain
*/
typedef	struct	s_padd  
{
	int	links_pad;
	int	user_pad;
	int	group_pad;
	int	size_pad;
}				t_padd;

typedef	struct	s_long_f
{	
	char	links[32];	
	char	user[32];
	char 	group[32];
	char	size[32];
	char	datetime[32];
}				t_long_f;

typedef struct s_file_lst
{
	char	full_path[4096];
	char	name[255]; /*for excluding .. . easily | This should be a pointer to name in fullpath */
	size_t	path_size;
	struct	stat data;	
	t_long_f	*long_format;	
	struct	s_file_lst *next;

}				t_file_lst;



typedef	 void	(*format_ptr)(t_file_lst*);
typedef	int		(*sort_ptr)(t_file_lst*, t_file_lst*);
typedef void	(*add_ptr)(t_file_lst**, t_file_lst*);
typedef	int		(*stat_ptr)(const char*,struct stat*);

extern format_ptr	format_fn;
extern	sort_ptr	sort_fn;
extern	add_ptr		add_fn;
extern	stat_ptr	stat_fn;

//
void	reg_format(t_file_lst *to_print);
void	long_format(t_file_lst *to_print);
//
int		cmplex(t_file_lst *chain, t_file_lst *to_add);
int		cmplex_r(t_file_lst *chain, t_file_lst *to_add);
int		cmpt(t_file_lst *chain, t_file_lst *to_add);
int		cmpt_r(t_file_lst *chain, t_file_lst *to_add);
//
void	add_node(t_file_lst **head, t_file_lst *t_add);
void	add_all(t_file_lst **head, t_file_lst *t_add);
//
int		ft_getopt(int argc, char *const argv[], const char *opstring);
int		ft_parseopt(int ac, char **av, int *Recrusive);

t_file_lst	*new_node(char *path);
void		delete_node(t_file_lst *to_delete);
int	init_struct(t_file_lst *tmp, char *name);
char	ft_filetype(mode_t st_mode);
void	append_lst(t_file_lst **apend_to, t_file_lst *to_append);
t_file_lst	*new_file_node(char *path);

//higher level functions
int	ft_inner_ls(t_file_lst *current, int Recursive);
t_file_lst	*handle_av(char **av);
//test functions
void	test_linked(t_file_lst *start);
void	parse_test(void);
void	destroy_lst(t_file_lst *head);
//long_format functions
int	fill_lf_info(t_file_lst	*start);
void	ft_getperm(mode_t mode, char perm[12]);
