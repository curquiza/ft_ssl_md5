#include "ft_ssl.h"

void		exit_malloc_err(void)
{
	ft_dprintf(2, "Malloc error\n");
	exit(FAILURE);
}