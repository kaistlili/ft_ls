#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

typedef struct s_file_list
{
	char path[4096];
	size_t path_size;
	char type;
	struct stat *data;
	struct s_file_list *next;
}				t_file_list;

typedef struct s_opt
{
	int long_f;
	int Recursive;
	int show_all;
	int rev;
	int time_sort;
}				t_opt;

void	ft_putchar(char c);
void	ft_putstr(char *str);
