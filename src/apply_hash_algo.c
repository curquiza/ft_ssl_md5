#include "ft_ssl.h"

// static void		hex_display(t_byte *s, size_t len)
// {
// 	size_t		i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		ft_printf("%02x", (t_byte)s[i]);
// 		i++;
// 	}
// 	write(1, "\n", 1);
// }

// t_ex_ret	apply_hash_algo(t_hash *data, char *algo)
// {
// 	t_hash_algo		tab[HASH_FUNC_TAB_SIZE];
// 	int 			i;

// 	init_hash_func_tab(tab);
// 	i = 0;
// 	while (i < HASH_FUNC_TAB_SIZE)
// 	{
// 		if (ft_strcmp(tab[i].name, algo) == 0)
// 		{
// 			if (tab[i].f(data, tab[i].alt_param) == FAILURE)
// 				return FAILURE;
// 			else
// 				break ;
// 		}
// 		i++;
// 	}
// 	hex_display(data->digest, data->digest_len);
// 	return (SUCCESS);
// }