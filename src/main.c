#include "ft_ssl.h"

static t_ex_ret is_option(char *arg, t_state *state)
{
	return (state->output == FALSE && arg && arg[0] == '-' && arg[1]);
}

static t_bool	is_option_breaker(t_state *state, char *arg)
{
	return (state->breaker == FALSE && ft_strcmp(arg, "--") == 0);
}

static t_ex_ret parse_and_execute_arg(char *arg, t_state *state)
{
	if (is_option_breaker(state, arg) == FALSE)
	{
		if (is_option(arg, state))
			return apply_option(arg, state);
		state->output = TRUE;
		return apply_file(arg, state);
	}
	state->output = TRUE;
	state->breaker = TRUE;
	return SUCCESS;
}

static t_bool		need_last_stdin_reading(t_state *state)
{
	return (state->output == FALSE
		&& (opt_is_activated(state->options, OPTION_R)
			|| opt_is_activated(state->options, OPTION_Q)
			|| !opt_is_activated(state->options, OPTION_P)));
}

static t_ex_ret		run_ft_ssl(char **argv, t_state *state)
{
	t_ex_ret	ret;

	ret = SUCCESS;
	while (*argv)
	{
		if (parse_and_execute_arg(*argv, state) == FAILURE)
			ret = FAILURE;
		argv++;
	}
	if (ret == SUCCESS && need_last_stdin_reading(state))
		return apply_stdin(state);
	return ret;
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