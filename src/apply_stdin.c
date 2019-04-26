#include "ft_ssl.h"

static char        *get_stdin_input(void)
{
    char    line[10];
    char    *rslt;
    char    *tmp;
    
    if (!(rslt = ft_strdup("")))
        exit_malloc_err();
    while (read(0, &line, 10) > 0)
    {
        tmp = rslt;
        if (!(rslt = ft_strjoin(rslt, line)))
        {
            ft_strdel(&tmp);
            exit_malloc_err();
        }
        ft_strdel(&tmp);
        ft_bzero(&line, 10);
    }
    close(0);
    return (rslt);
}

t_ex_ret    apply_stdin(t_state *state)
{
    char    *rslt;
    t_hash  data;

    rslt = get_stdin_input();
    ft_bzero(&data, sizeof(data));
    if (!(data.msg = (t_byte *)ft_strdup(rslt)))
        exit_malloc_err();
    data.msg_len = ft_strlen(rslt);
    ft_strdel(&rslt);
    if (state->hash_algo->f(&data, state->hash_algo->alt_param) == FAILURE)
    {
    	clean_hash_data(&data);
        return FAILURE;
    }
    if (opt_is_activated(state->options, OPTION_P))
        ft_putstr((char *)data.msg);
    hex_display_endl(data.digest, data.digest_len);
	clean_hash_data(&data);
    return SUCCESS;
}