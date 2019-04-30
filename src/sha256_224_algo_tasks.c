#include "ft_ssl.h"

/*
** The 32 bits of the fractional parts of the cube roots of the
** 64 prime numbers
*/
uint32_t g_k_sha256[SHA256_CHUNK_BYTES] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static uint32_t	get_word(uint32_t words[SHA256_WORD_NB], uint32_t incr_word)
{
	uint32_t	s0;
	uint32_t	s1;

	s0 = (uint32_right_rotate(words[incr_word - 15], 7))
		^ (uint32_right_rotate(words[incr_word - 15], 18))
		^ (uint32_right_shift(words[incr_word - 15], 3));
	s1 = (uint32_right_rotate(words[incr_word - 2], 17))
		^ (uint32_right_rotate(words[incr_word - 2], 19))
		^ (uint32_right_shift(words[incr_word - 2], 10));
	return (words[incr_word - 16] + s0 + words[incr_word - 7] + s1);
}

void	fill_words_sha256_224(uint32_t words[SHA256_WORD_NB], uint32_t i, t_hash *data)
{
	uint32_t	incr_msg;
	uint32_t	incr_word;

	incr_msg = i * SHA256_CHUNK_BYTES;
	incr_word = 0;
	while (incr_word < SHA256_WORD_NB_FROM_CHUNK)
	{
		words[incr_word] = ptr_to_uint32(data->padded_msg + incr_msg);
		incr_msg += sizeof(uint32_t);
		incr_word++;
	}
	while (incr_word < SHA256_WORD_NB)
	{
		words[incr_word] = get_word(words, incr_word);
		incr_word++;
	}
}

static void	fill_tmp_var(int i, t_sha256_incr *var, uint32_t words[SHA256_WORD_NB])
{
	uint32_t		big_s1;
	uint32_t		big_s0;
	uint32_t		ch;
	uint32_t		temp1;
	uint32_t		temp2;

	big_s1 = uint32_right_rotate(var->e, 6) ^ uint32_right_rotate(var->e, 11)
		^ uint32_right_rotate(var->e, 25);
	ch = (var->e & var->f) ^ (~var->e & var->g);
	temp1 = var->h + big_s1 + ch + g_k_sha256[i] + words[i];
	big_s0 = uint32_right_rotate(var->a, 2) ^ uint32_right_rotate(var->a, 13)
		^ uint32_right_rotate(var->a, 22);
	temp2 = big_s0 + (uint32_t)((var->a & var->b) ^ (var->a & var->c) ^ (var->b & var->c));
	var->h = var->g;
	var->g = var->f;
	var->f = var->e;
	var->e = var->d + temp1;
	var->d = var->c;
	var->c = var->b;
	var->b = var->a;
	var->a = temp1 + temp2;
}

void	run_one_chunk_sha256_224(uint32_t words[SHA256_WORD_NB], t_sha256_incr *rslt)
{
	int				i;
	t_sha256_incr	var;

	var.a = rslt->a;
	var.b = rslt->b;
	var.c = rslt->c;
	var.d = rslt->d;
	var.e = rslt->e;
	var.f = rslt->f;
	var.g = rslt->g;
	var.h = rslt->h;
	i = 0;
	while (i < SHA256_ROUNDS)
	{
		fill_tmp_var(i, &var, words);
		i++;
	}
	rslt->a += var.a;
	rslt->b += var.b;
	rslt->c += var.c;
	rslt->d += var.d;
	rslt->e += var.e;
	rslt->f += var.f;
	rslt->g += var.g;
	rslt->h += var.h;
}
