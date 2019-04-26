#include "ft_ssl.h"

t_ex_ret    apply_option(char *arg, t_state *state)
{
    arg++;
    while (*arg)
    {
        if (*arg == OPTION_P_CHAR)
        {
            activate_opt(state, OPTION_P);
            if (apply_stdin(state) == FAILURE)
                return FAILURE;
        }
        else if (*arg == OPTION_Q_CHAR)
            activate_opt(state, OPTION_Q);
        else if (*arg == OPTION_R_CHAR)
            activate_opt(state, OPTION_R);
        else if (*arg == OPTION_S_CHAR)
            ft_putendl("OPTION S"); // DEBUG
        else
        {
            ft_dprintf(2, "Error: %c: illegal option\n", *arg);
            exit(FAILURE);
        }
        arg++;
    }
    return SUCCESS;
}