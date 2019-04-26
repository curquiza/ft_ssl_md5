#include "ft_ssl.h"

t_bool  opt_is_activated(uint32_t options_state, uint32_t opt_mask)
{
    return ((options_state & opt_mask) == opt_mask);
}

void    activate_opt(t_state *state, uint32_t opt_mask)
{
    state->options |= opt_mask;
}

void    desactivate_opt(t_state *state, uint32_t opt_mask)
{
    state->options ^= opt_mask;
}