#include "ft_ssl.h"

void		clean_hash_data(t_hash *data)
{
	free(data->msg);
	free(data->digest);
	free(data->padded_msg);
}