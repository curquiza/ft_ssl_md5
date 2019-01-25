#include "ft_ssl.h"

void		hex_display_details(t_byte *s, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		if (i % 4 == 0)
			ft_printf("%03d - %03d\t", i, i + 3);
		ft_printf("%02x", (t_byte)s[i]);
		i++;
		if (i % 4 == 0)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
	}
	write(1, "\n", 1);
}

void		hex_display(t_byte *s, size_t len)
{
	size_t		i;

	i = 0;
	while (i < len)
	{
		ft_printf("%02x", (t_byte)s[i]);
		i++;
	}
	write(1, "\n", 1);
}

/* static void	set_msg_size(t_byte *s, int64_t n) */
/* { */
/* 	int		i; */
/*  */
/* 	i = 0; */
/* 	while (i < MSG_LEN_BYTES) */
/* 	{ */
/* 		s[i] = (t_byte)(n >> ((MSG_LEN_BYTES - 1 - i) * 8)); */
/* 		i++; */
/* 	} */
/* } */

/* static uint64_t	pow(uint32_t v, uint32_t n) */
/* { */
/* 	if (n == 0) */
/* 		return 1; */
/* 	return (v * pow(v, n - 1)); */
/* } */

/* static int	get_size_in_bytes(uint64_t n) */
/* { */
/* 	if (n < pow(2, 8)) */
/* 		return (1); */
/* 	else if (n < pow(2, 16)) */
/* 		return (2); */
/* 	else if (n < pow(2, 24)) */
/* 		return (3); */
/* 	else if (n < pow(2, 32)) */
/* 		return (4); */
/* 	else if (n < pow(2, 40)) */
/* 		return (5); */
/* 	else if (n < pow(2, 48)) */
/* 		return (6); */
/* 	else if (n < pow(2, 56)) */
/* 		return (7); */
/* 	else */
/* 		return (8); */
/* } */

static void	set_msg_size(t_byte *s, uint64_t *n)
{
	int		i;

	i = 0;
	while (i < (MSG_LEN_BYTES))
	{
		/* ft_printf("---------\ni = %d\n", i); //DEBUG */
		/* ft_printf("n_nb_bytes - 1 - i = %d\n", n_nb_bytes - 1 - i); //DEBUG */
		s[i] = ((t_byte *)n)[i];
		i++;
	}
}

static t_byte	*message_padding(char *message)
{
	size_t		tmp_len;
	size_t		final_len;
	uint64_t	msg_len_bits;
	t_byte		*padded_msg;

	tmp_len = (ft_strlen(message) + 1 + MSG_LEN_BYTES);
	if (tmp_len % (MD5_DIGEST_CHUNK_BYTES) == 0)
		final_len = tmp_len;
	else
		final_len = (tmp_len / (MD5_DIGEST_CHUNK_BYTES) + 1)
					* (MD5_DIGEST_CHUNK_BYTES);
	if (!(padded_msg = (t_byte *)ft_memalloc(final_len)))
		return (NULL);
	ft_printf("padded_msg len = %d = 0x%x\n", final_len, final_len); //DEBUG
	ft_memcpy(padded_msg, message, ft_strlen(message));
	padded_msg[ft_strlen(message)] = (t_byte)(1 << 7);
	msg_len_bits = 8 * ft_strlen(message);
	set_msg_size(padded_msg + final_len - MSG_LEN_BYTES, &msg_len_bits);
	/* hex_display_details(padded_msg, final_len); //DEBUG */
	hex_display(padded_msg, final_len); //DEBUG
	return (padded_msg);
}

t_ex_ret	fill_md5_digest(char *message, t_byte *digest)
{
	t_byte	*padded_message;

	(void)digest; //DEBUG
	ft_printf("message = \"%s\"\n", message); // DEBUG
	ft_printf("message bits = %d = 0x%x\n", ft_strlen(message) * 8, 8 * ft_strlen(message)); // DEBUG
	if (!(padded_message = message_padding(message)))
		return (FAILURE);
	return (SUCCESS);
}
