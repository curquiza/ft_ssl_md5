#include "ft_ssl.h"

void    display_digest(char *filename, t_hash *data, t_state *state)
{
    char    *algo_name;

    if (opt_is_activated(state->options, OPTION_Q))
        hex_display_endl(data->digest, data->digest_len);
    else if (opt_is_activated(state->options, OPTION_R))
    {
        hex_display(data->digest, data->digest_len);
        ft_printf(" %s\n", filename);
    }
    else
    {
        algo_name = state->hash_algo->name;
        ft_strupper(algo_name);
        ft_printf("%s (%s) = ", algo_name, filename);
        hex_display_endl(data->digest, data->digest_len);
    }
}