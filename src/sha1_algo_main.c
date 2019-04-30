#include "ft_ssl.h"

static void	rslt_init(t_sha1_incr *rslt)
{
	rslt->a = SHA1_A0_INIT;
	rslt->b = SHA1_B0_INIT;
	rslt->c = SHA1_C0_INIT;
	rslt->d = SHA1_D0_INIT;
	rslt->e = SHA1_E0_INIT;
}

static void	fill_digest(t_hash *data, t_sha1_incr *rslt)
{
	size_t	sizeof_uint32;

	if (!(data->digest = ft_memalloc(SHA1_DIGEST_BYTES)))
		exit_malloc_err_with_clean(data);
	sizeof_uint32 = sizeof(uint32_t);
	ft_memcpy_back(data->digest, &rslt->a, sizeof_uint32);
	ft_memcpy_back(data->digest + sizeof_uint32, &rslt->b, sizeof_uint32);
	ft_memcpy_back(data->digest + 2 * sizeof_uint32, &rslt->c, sizeof_uint32);
	ft_memcpy_back(data->digest + 3 * sizeof_uint32, &rslt->d, sizeof_uint32);
	ft_memcpy_back(data->digest + 4 * sizeof_uint32, &rslt->e, sizeof_uint32);
}

static void	run_sha1_algo(t_hash *data, t_sha1_const *cst)
{
	uint32_t	i;
	uint32_t	words[SHA1_WORD_NB];
	t_sha1_incr	rslt;

	rslt_init(&rslt);
	i = 0;
	while (i < (data->padded_msg_len / (SHA1_CHUNK_BYTES)))
	{
		fill_words_sha1(words, i, data);
		run_one_chunk_sha1(words, &rslt, cst);
		i++;
	}
	fill_digest(data, &rslt);
}

void	fill_sha1_digest(t_hash *data)
{
	t_sha1_const	cst[SHA1_WORD_NB];
	data->digest_len = SHA1_DIGEST_BYTES;
	message_padding_sha1(data);
	fill_algo_constants_sha1(cst);
	run_sha1_algo(data, cst);
}
