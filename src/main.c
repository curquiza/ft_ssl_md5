#include "ft_ssl.h"

static t_ex_ret is_option(char *arg, t_state *state)
{
	return (state->opt_end == FALSE && arg && arg[0] == '-');
}

static t_ex_ret parse_and_execute_arg(char *arg, t_state *state)
{
	if (is_option(arg, state))
		return apply_option(arg, state);
	return apply_file(arg, state);
}

static t_ex_ret		run_ft_ssl(char **argv, t_state *state)
{
	while (*argv)
	{
		if (parse_and_execute_arg(*argv, state) == FAILURE)
			return FAILURE;
		argv++;
	}
	// read on stdin if pas d'arg (-p non inclus)
	return SUCCESS;
}

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