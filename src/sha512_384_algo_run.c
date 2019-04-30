#include "ft_ssl.h"

static void	rslt_init(t_sha512_incr *rslt, int alt)
{
	if (alt == 0)
	{
		rslt->a = SHA512_A0_INIT;
		rslt->b = SHA512_B0_INIT;
		rslt->c = SHA512_C0_INIT;
		rslt->d = SHA512_D0_INIT;
		rslt->e = SHA512_E0_INIT;
		rslt->f = SHA512_F0_INIT;
		rslt->g = SHA512_G0_INIT;
		rslt->h = SHA512_H0_INIT;
	}
	else
	{
		rslt->a = SHA384_A0_INIT;
		rslt->b = SHA384_B0_INIT;
		rslt->c = SHA384_C0_INIT;
		rslt->d = SHA384_D0_INIT;
		rslt->e = SHA384_E0_INIT;
		rslt->f = SHA384_F0_INIT;
		rslt->g = SHA384_G0_INIT;
		rslt->h = SHA384_H0_INIT;
	}
}

static void	fill_digest(t_hash *data, t_sha512_incr *rslt, int alt)
{
	size_t	sizeof_uint64;

	if (!(data->digest = ft_memalloc(data->digest_len)))
		exit_malloc_err_with_clean(data);
	sizeof_uint64 = sizeof(uint64_t);
	ft_memcpy_back(data->digest, &rslt->a, sizeof_uint64);
	ft_memcpy_back(data->digest + sizeof_uint64, &rslt->b, sizeof_uint64);
	ft_memcpy_back(data->digest + 2 * sizeof_uint64, &rslt->c, sizeof_uint64);
	ft_memcpy_back(data->digest + 3 * sizeof_uint64, &rslt->d, sizeof_uint64);
	ft_memcpy_back(data->digest + 4 * sizeof_uint64, &rslt->e, sizeof_uint64);
	ft_memcpy_back(data->digest + 5 * sizeof_uint64, &rslt->f, sizeof_uint64);
	if (alt == 0)
	{
		ft_memcpy_back(data->digest + 6 * sizeof_uint64, &rslt->g,
			sizeof_uint64);
		ft_memcpy_back(data->digest + 7 * sizeof_uint64, &rslt->h,
			sizeof_uint64);
	}
}

void	run_sha512_384_algo(t_hash *data, int alt)
{
	int				i;
	uint64_t		words[SHA512_WORD_NB];
	t_sha512_incr	rslt;

	rslt_init(&rslt, alt);
	i = 0;
	while ((uint64_t)i < (data->padded_msg_len / (SHA512_CHUNK_BYTES)))
	{
		fill_words_sha512_384(words, i, data);
		run_one_chunk_sha512_384(words, &rslt);
		i++;
	}
	fill_digest(data, &rslt, alt);
}
