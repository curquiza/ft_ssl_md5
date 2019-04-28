#include "ft_ssl.h"

int				main(int argc, char **argv)
{
	t_hash_algo	algo_tab[HASH_FUNC_TAB_SIZE];
	t_state		state;

	if (argc <= 1)
		return ret_usage_err();
	first_init(algo_tab, &state);
	if (get_hash_algo(argv[1], &state, algo_tab) == FAILURE)
		return FAILURE;
	return run_ft_ssl(argv + 2, &state);
}

// TODO :
// - resoudre pb lenteur read
// - fix pb ouverture dossier
