#include "ft_ssl.h"

t_ex_ret    apply_hash_algo_for_arg(char *arg, t_hash *data, t_state *state)
{
    if (state->hash_algo->f(data, state->hash_algo->alt_param) == FAILURE)
	{
		clean_hash_data(data);
        return FAILURE;
	}
    display_digest(arg, data, state);
	clean_hash_data(data);
    return SUCCESS;
}