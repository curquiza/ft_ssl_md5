#include "ft_ssl.h"

char        *get_stdin_input(void)
{
    int     ret;
    char    *line;
    char    *rslt;
    char    *tmp;
    
    if (!(rslt = ft_strdup("")))
        exit_malloc_err();
    line = NULL;
    while ((ret = get_next_line(0, &line)) == 1)
    {
        tmp = rslt;
        if (!(rslt = ft_strjoin3(rslt, line, "\n")))
        {
            ft_strdel(&tmp);
            ft_strdel(&line);
            exit_malloc_err();
        }
        ft_strdel(&tmp);
        ft_strdel(&line);
    }
    if (ret == -1)
        return NULL;
    return (rslt);
}

t_ex_ret    apply_stdin(t_state *state)
{
    char    *rslt;
    t_hash  data;

    if (!(rslt = get_stdin_input()))
        return ft_ret_err(STDIN_READ_ERR);
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
    hex_display_endl(data.digest, data.digest_len);
	clean_hash_data(&data);
    return SUCCESS;
}