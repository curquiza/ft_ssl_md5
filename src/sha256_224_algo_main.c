#include "ft_ssl.h"

static void	fill_sha256_224_digest(t_hash *data, int alt)
{
	if (alt == 0)
		data->digest_len = SHA256_DIGEST_BYTES;
	else
		data->digest_len = SHA224_DIGEST_BYTES;
	message_padding_sha256_224(data);
	run_sha256_224_algo(data, alt);
}

void	fill_sha256_digest(t_hash *data)
{
	fill_sha256_224_digest(data, 0);
}

void	fill_sha224_digest(t_hash *data)
{
	fill_sha256_224_digest(data, 1);
}
