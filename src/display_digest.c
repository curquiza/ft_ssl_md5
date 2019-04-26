#include "ft_ssl.h"

void    display_digest(char *filename, t_hash *data, t_state *state)
{
    char    *algo_name;

    algo_name = state->hash_algo->name;
    ft_strupper(algo_name);
    ft_printf("%s (%s) = ", algo_name, filename);
    hex_display(data->digest, data->digest_len);    
}