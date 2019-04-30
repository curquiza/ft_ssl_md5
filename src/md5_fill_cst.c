#include "ft_ssl.h"

static uint32_t		get_radian_const(int i)
{
	return ((uint32_t)floor(abs_double(sin(i + 1)) * POW_2_32));
}

static int			get_word_index(int i)
{
	if (i < 16)
		return (i);
	else if (i < 32)
		return ((5 * i + 1) % 16);
	else if (i < 48)
		return ((3 * i + 5) % 16);
	else
		return ((7 * i) % 16);
}

static void		fill_constants(int start, t_md5_const *cst,
				uint32_t (*func)(uint32_t b, uint32_t c, uint32_t d))
{
	int				i;
	uint32_t		shift[4];

	shift[0] = cst[start].shift;
	shift[1] = cst[start + 1].shift;
	shift[2] = cst[start + 2].shift;
	shift[3] = cst[start + 3].shift;
	i = start;
	while (i <= (start + 15))
	{
		cst[i].shift = shift[i % 4];
		cst[i].radian = get_radian_const(i);
		cst[i].func = func;
		cst[i].word_index = get_word_index(i);
		i++;
	}
}

void		fill_algo_constants_md5(t_md5_const *cst)
{
	cst[0].shift = 7;
	cst[1].shift = 12;
	cst[2].shift = 17;
	cst[3].shift = 22;
	fill_constants(0, cst, &f_function);
	cst[16].shift = 5;
	cst[17].shift = 9;
	cst[18].shift = 14;
	cst[19].shift = 20;
	fill_constants(16, cst, &g_function);
	cst[32].shift = 4;
	cst[33].shift = 11;
	cst[34].shift = 16;
	cst[35].shift = 23;
	fill_constants(32, cst, &h_function);
	cst[48].shift = 6;
	cst[49].shift = 10;
	cst[50].shift = 15;
	cst[51].shift = 21;
	fill_constants(48, cst, &i_function);
}
