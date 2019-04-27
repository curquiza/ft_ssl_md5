#include "ft_ssl.h"

void		exit_malloc_err(void)
{
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}

void		exit_malloc_err_with_clean(t_hash *data)
{
	clean_hash_data(data);
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}
