#include "ft_ssl.h"

uint32_t	f_function(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & c) | ((~b) & d));
}

uint32_t	g_function(uint32_t b, uint32_t c, uint32_t d)
{
	return ((b & d) | (c & ~d));
}

uint32_t	h_function(uint32_t b, uint32_t c, uint32_t d)
{
	return (b ^ c ^ d);
}

uint32_t	i_function(uint32_t b, uint32_t c, uint32_t d)
{
	return (c ^ (b | ~d));
}
