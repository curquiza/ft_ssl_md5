/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_384_algo_tasks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: curquiza <curquiza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:32:41 by curquiza          #+#    #+#             */
/*   Updated: 2019/04/30 18:50:29 by curquiza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** The 64 bits of the fractional parts of the cube roots of the
** 80 prime numbers
*/
uint64_t g_k_sha512[SHA512_CHUNK_BYTES] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f,
	0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242,
	0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275,
	0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f,
	0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc,
	0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6,
	0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99,
	0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc,
	0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915,
	0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba,
	0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static uint64_t	get_word(uint64_t words[SHA512_WORD_NB], int incr_word)
{
	uint64_t	s0;
	uint64_t	s1;

	s0 = (uint64_right_rotate(words[incr_word - 15], 1))
		^ (uint64_right_rotate(words[incr_word - 15], 8))
		^ (uint64_right_shift(words[incr_word - 15], 7));
	s1 = (uint64_right_rotate(words[incr_word - 2], 19))
		^ (uint64_right_rotate(words[incr_word - 2], 61))
		^ (uint64_right_shift(words[incr_word - 2], 6));
	return (words[incr_word - 16] + s0 + words[incr_word - 7] + s1);
}

void			fill_words_sha512_384(uint64_t words[SHA512_WORD_NB], int i,
					t_hash *data)
{
	int	incr_msg;
	int	incr_word;

	incr_msg = i * SHA512_CHUNK_BYTES;
	incr_word = 0;
	while (incr_word < SHA512_WORD_NB_FROM_CHUNK)
	{
		words[incr_word] = ptr_to_uint64(data->padded_msg + incr_msg);
		incr_msg += sizeof(uint64_t);
		incr_word++;
	}
	while (incr_word < SHA512_WORD_NB)
	{
		words[incr_word] = get_word(words, incr_word);
		incr_word++;
	}
}

static void		fill_tmp_var(int i, t_sha512_incr *var,
					uint64_t words[SHA512_WORD_NB])
{
	uint64_t		big_s1;
	uint64_t		big_s0;
	uint64_t		ch;
	uint64_t		temp1;
	uint64_t		temp2;

	big_s1 = uint64_right_rotate(var->e, 14) ^ uint64_right_rotate(var->e, 18)
		^ uint64_right_rotate(var->e, 41);
	ch = (var->e & var->f) ^ (~var->e & var->g);
	temp1 = var->h + big_s1 + ch + g_k_sha512[i] + words[i];
	big_s0 = uint64_right_rotate(var->a, 28) ^ uint64_right_rotate(var->a, 34)
		^ uint64_right_rotate(var->a, 39);
	temp2 = big_s0
		+ (uint64_t)((var->a & var->b) ^ (var->a & var->c) ^ (var->b & var->c));
	var->h = var->g;
	var->g = var->f;
	var->f = var->e;
	var->e = var->d + temp1;
	var->d = var->c;
	var->c = var->b;
	var->b = var->a;
	var->a = temp1 + temp2;
}

void			run_one_chunk_sha512_384(uint64_t words[SHA512_WORD_NB],
					t_sha512_incr *rslt)
{
	int				i;
	t_sha512_incr	var;

	var.a = rslt->a;
	var.b = rslt->b;
	var.c = rslt->c;
	var.d = rslt->d;
	var.e = rslt->e;
	var.f = rslt->f;
	var.g = rslt->g;
	var.h = rslt->h;
	i = 0;
	while (i < SHA512_ROUNDS)
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
